# Changelog

## Privacy-clean installer repack — 2026-10-26

- Withdrew the original public RC1 installer after discovering it seeded personal/user filament and process presets.
- Removed all user filament presets, including the experimental Tgood profile.
- Removed all user process/slicer presets.
- Removed personal preset selections/references from the initial `Creality.conf` seed.
- Switched the initial selection to generic system presets: `Flashforge AD5X Generic PLA` and `0.20mm Standard @FF AD5X`.
- Public seed reduced from 211 files to 204 files.
- Privacy-clean package verification passed; a new install/uninstall smoke was not rerun so the existing local RC1 installation/data remained untouched.
- Replacement installer SHA-256: `DD2A81FBB2DD5D3A9C083A684882E4F521A8C777248FEF51D9F41F3876F467FB`.

## GitHub source/presentation update — 2026-10-26

- Published the accepted built-in AD5X Design workspace source under `design/`.
- Added portable regression fixtures so a clean public Design source tree can run its test suite without the historical development-directory layout.
- Verified the public Design copy: 87 / 87 test files and 635 / 635 tests passed; TypeScript/Vite/PWA production build passed.
- Added Design screenshots and a 42-second Design → Prepare → Preview demonstration.
- Reworked the project front page to explain the Design workflow before the lower-level AD5X/offline changes.
- Added Sculpo/Design and Manifold provenance/licence notes.
- At this source/documentation step the Windows RC1 installer was unchanged; it was subsequently replaced by the privacy-clean repack documented above.

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

`DD2A81FBB2DD5D3A9C083A684882E4F521A8C777248FEF51D9F41F3876F467FB`

See [RELEASE_NOTES_RC1.md](RELEASE_NOTES_RC1.md).