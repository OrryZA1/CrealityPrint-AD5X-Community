#pragma once
// AD5X Native Status Panel v0.1 (2026-10-12)
// Local-only and read-only. No WebView2, FlashForge cloud or printer commands.
// Optional local Moonraker status panel. Target address must be supplied explicitly.

#include "slic3r/Utils/Http.hpp"

#include <wx/app.h>
#include <wx/colour.h>
#include <wx/gauge.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/timer.h>
#include <wx/window.h>

#include <nlohmann/json.hpp>
#include <atomic>
#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <utility>

namespace Slic3r {
namespace GUI {

class NativeAD5XStatusPanel final : public wxPanel
{
public:
    explicit NativeAD5XStatusPanel(wxWindow* parent, std::string address)
        : wxPanel(parent, wxID_ANY), m_timer(this),
          m_alive(std::make_shared<std::atomic_bool>(true)),
          m_address(std::move(address))
    {
        SetBackgroundColour(wxColour(39, 40, 44));

        auto* outer = new wxBoxSizer(wxVERTICAL);
        auto* title = new wxStaticText(this, wxID_ANY, "FlashForge AD5X  |  Native LAN status");
        wxFont font = title->GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        font.SetPointSize(font.GetPointSize() + 2);
        title->SetFont(font);
        title->SetForegroundColour(wxColour(230, 234, 240));
        outer->Add(title, 0, wxBOTTOM, 7);

        auto* line1 = new wxBoxSizer(wxHORIZONTAL);
        m_connection = add_value(line1, "Connection", "Waiting for Moonraker...");
        m_state = add_value(line1, "Printer", "--");
        outer->Add(line1, 0, wxEXPAND | wxBOTTOM, 8);

        auto* line2 = new wxBoxSizer(wxHORIZONTAL);
        m_nozzle = add_value(line2, "Nozzle", "-- C");
        m_bed = add_value(line2, "Bed", "-- C");
        m_progress_text = add_value(line2, "Progress", "--");
        outer->Add(line2, 0, wxEXPAND | wxBOTTOM, 7);

        m_gauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(-1, 5));
        m_gauge->SetValue(0);
        outer->Add(m_gauge, 0, wxEXPAND | wxBOTTOM, 5);

        auto* note = new wxStaticText(this, wxID_ANY,
            "Read-only | Local Moonraker " + wxString::FromUTF8(m_address.c_str()) +
            ":7125 | IFS settings unchanged");
        note->SetForegroundColour(wxColour(154, 159, 169));
        outer->Add(note, 0, wxTOP, 3);

        SetSizer(outer);
        Bind(wxEVT_TIMER, [this](wxTimerEvent&) { poll(); }, m_timer.GetId());
        m_timer.Start(4000);
        poll();
    }

    ~NativeAD5XStatusPanel() override
    {
        m_timer.Stop();
        m_alive->store(false, std::memory_order_release);
        if (m_worker.joinable())
            m_worker.join();
    }

private:
    struct Reading {
        bool connected = false;
        std::string state = "--";
        double nozzle = 0.0;
        double bed = 0.0;
        int progress = 0;
    };

    wxStaticText* add_value(wxBoxSizer* row, const wxString& label, const wxString& initial)
    {
        auto* column = new wxBoxSizer(wxVERTICAL);
        auto* title = new wxStaticText(this, wxID_ANY, label);
        title->SetForegroundColour(wxColour(158, 166, 176));
        column->Add(title, 0, wxBOTTOM, 2);
        auto* value = new wxStaticText(this, wxID_ANY, initial);
        value->SetForegroundColour(wxColour(235, 239, 245));
        column->Add(value, 0);
        row->Add(column, 1, wxEXPAND | wxRIGHT, 12);
        return value;
    }

    static nlohmann::json object_field(const nlohmann::json& item, const char* key)
    {
        auto it = item.find(key);
        return (it != item.end() && it->is_object()) ? *it : nlohmann::json::object();
    }

    static double number_field(const nlohmann::json& item, const char* key)
    {
        auto it = item.find(key);
        return (it != item.end() && it->is_number()) ? it->get<double>() : 0.0;
    }

    static Reading decode(const std::string& body)
    {
        Reading data;
        auto root = nlohmann::json::parse(body, nullptr, false);
        if (root.is_discarded() || !root.is_object())
            return data;
        const auto result = object_field(root, "result");
        const auto status = object_field(result, "status");
        if (status.empty())
            return data;

        const auto print_stats = object_field(status, "print_stats");
        const auto extruder = object_field(status, "extruder");
        const auto heater_bed = object_field(status, "heater_bed");
        const auto sd = object_field(status, "virtual_sdcard");

        data.connected = true;
        auto it = print_stats.find("state");
        if (it != print_stats.end() && it->is_string())
            data.state = it->get<std::string>();
        data.nozzle = number_field(extruder, "temperature");
        data.bed = number_field(heater_bed, "temperature");
        const double progress = std::max(0.0, std::min(1.0, number_field(sd, "progress")));
        data.progress = static_cast<int>(std::round(progress * 100.0));
        return data;
    }

    void poll()
    {
        if (m_busy.exchange(true))
            return;

        if (m_worker.joinable())
            m_worker.join();

        const auto alive = m_alive;
        m_worker = std::thread([this, alive]() {
            Reading reading;
            try {
                Slic3r::Http::get(
                    "http://" + m_address + ":7125/printer/objects/query?"
                    "print_stats&virtual_sdcard&extruder&heater_bed")
                    .timeout_max(3)
                    .noproxy("*")
                    .on_complete([&reading](std::string body, unsigned status) {
                        if (status >= 200 && status < 300)
                            reading = decode(body);
                    })
                    .on_error([](std::string, std::string, unsigned) {})
                    .perform_sync();
            } catch (...) {
                // Failed or unreachable LAN target remains disconnected.
            }
            m_busy.store(false);
            if (wxTheApp && alive->load(std::memory_order_acquire)) {
                wxTheApp->CallAfter([this, alive, reading]() {
                    if (!alive->load(std::memory_order_acquire))
                        return;
                    update_ui(reading);
                });
            }
        });
    }

    void update_ui(const Reading& reading)
    {
        if (!reading.connected) {
            m_connection->SetLabel("Disconnected");
            m_state->SetLabel("--");
            m_nozzle->SetLabel("-- C");
            m_bed->SetLabel("-- C");
            m_progress_text->SetLabel("--");
            m_gauge->SetValue(0);
            return;
        }
        m_connection->SetLabel("Moonraker LAN");
        m_state->SetLabel(wxString::FromUTF8(reading.state.c_str()));
        m_nozzle->SetLabel(wxString::Format("%.1f C", reading.nozzle));
        m_bed->SetLabel(wxString::Format("%.1f C", reading.bed));
        m_progress_text->SetLabel(wxString::Format("%d %%", reading.progress));
        m_gauge->SetValue(reading.progress);
        Layout();
    }

    wxTimer m_timer;
    std::shared_ptr<std::atomic_bool> m_alive;
    std::string m_address;
    std::atomic_bool m_busy {false};
    std::thread m_worker;
    wxStaticText* m_connection {nullptr};
    wxStaticText* m_state {nullptr};
    wxStaticText* m_nozzle {nullptr};
    wxStaticText* m_bed {nullptr};
    wxStaticText* m_progress_text {nullptr};
    wxGauge* m_gauge {nullptr};
};

} // namespace GUI
} // namespace Slic3r
