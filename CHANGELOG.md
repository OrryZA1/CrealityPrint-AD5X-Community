# Changelog

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
