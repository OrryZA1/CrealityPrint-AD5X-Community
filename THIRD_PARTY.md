# Third-party and upstream components

This repository is an unofficial fork of CrealityPrint and retains upstream code, resources, licences and dependencies.

## Main project licence

CrealityPrint identifies the main project as GNU Affero General Public License v3.0. This fork retains that licence.

See:

- `LICENSE.txt`
- `UPSTREAM_README.md`

## Project lineage

CrealityPrint is derived from OrcaSlicer, which is derived from Bambu Studio, PrusaSlicer and Slic3r. Their upstream attribution remains applicable.

## Creality precompiled dependencies

Two relevant dependency groups are present in the upstream CrealityPrint source tree.

### CR_FILLTENSOR

Path:

`deps/CR_CLOSED/CR_FILLTENSOR`

The upstream repository supplies headers plus precompiled Windows/Linux/macOS libraries and links the library into `libslic3r`.

The upstream README records the library as originating from a Creality internal build named `CR_Close_library` and includes binary hashes/provenance information.

The implementation source for the precompiled library is not present in this public source tree.

### CR_TPMS

Path:

`deps/CR_TPMS`

The upstream repository supplies a header plus precompiled platform libraries. CrealityPrint links this component into the slicer for TPMS-related functionality.

An upstream build helper references a Creality-internal source repository for `cr_tpms_library`, but that implementation source is not present in the public CrealityPrint repository.

## Fork position

This fork:

- did not create these two libraries;
- does not claim authorship of them;
- does not claim to relicense them separately;
- preserves the upstream copies unmodified;
- preserves upstream provenance/private-network references rather than rewriting their history.

Anyone redistributing this fork should review the current upstream CrealityPrint licensing position for these components.

Upstream repository:

https://github.com/CrealityOfficial/CrealityPrint
