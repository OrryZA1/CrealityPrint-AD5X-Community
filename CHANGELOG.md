# Changelog

## GitHub source/presentation update — 2026-10-26

- Published the accepted built-in AD5X Design workspace source under `design/`.
- Added portable regression fixtures so a clean public Design source tree can run its test suite without the historical development-directory layout.
- Verified the public Design copy: 87 / 87 test files and 635 / 635 tests passed; TypeScript/Vite/PWA production build passed.
- Added Design screenshots and a 42-second Design → Prepare → Preview demonstration.
- Reworked the project front page to explain the Design workflow before the lower-level AD5X/offline changes.
- Added Sculpo/Design and Manifold provenance/licence notes.
- The Windows RC1 installer binary is unchanged by this source/documentation update.

## v7.3.0-ad5x-rc1

Initial public RC1 source release based on the preserved Creality Print 7.3 source baseline.

### AD5X integration

- Added FlashForge AD5X machine definition.
- Added AD5X 0.4 mm nozzle profile.
- Added AD5X build-plate artwork/resources.
- Added generic AD5X PLA, PLA+, PETG, ABS, ASA and TPU filament presets.
- Added 0.20 mm Standard AD5X process preset.
- Restored/preserved AD5X device UI resources and native status integration.
- Preserved the project's Send Print / Klipper / Fluidd workflow.

### Offline-focused changes

- Preserved the tested in-app update freeze.
- Removed or disabled active Creality cloud background paths used by the fork.
- Disabled cloud home by default.
- Hardened offline preset/update behavior.
- Reduced sensitive runtime logging.
- Hardened device exception handling and retry behavior.
- Removed dead update UI action and related warning-producing code.

### Release packaging

The RC1 installer was built separately from the source repository and verified by release manifests.

Installer SHA-256:

`F11686C0904A7D07BF0F89EC5845913765B3D2903203FD3B5E873ACB61ACD05E`

See [RELEASE_NOTES_RC1.md](RELEASE_NOTES_RC1.md).