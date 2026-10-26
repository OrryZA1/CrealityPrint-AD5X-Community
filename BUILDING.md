# Building CrealityPrint AD5X Offline Community

## Current build status

The public RC1 source tree is derived from the verified project source checkpoint used for the RC1 application, with only internal project-control files omitted.

A fresh Windows x64 build of this public worktree was independently verified on **2026-10-26**. CMake configure/generate completed successfully and Ninja built the `CrealityPrint.exe` target through **838 / 838** steps with exit code `0`, including successful links of `CrealityPrint_Slicer.dll` and `CrealityPrint.exe`.

Verified toolchain for that check:

- MSVC 14.44.35207;
- CMake 3.31.12;
- Ninja from Visual Studio Build Tools 2022;
- Windows SDK 10.0.26100.0.

The build reused the already-built upstream dependency prefix from the project's known-good Windows build environment. It did **not** rebuild dependencies, install the application, run the GUI, or perform a physical print.

## Windows x64 prerequisites

The source contains upstream build support for Visual Studio 2022.

Typical requirements include:

- Visual Studio 2022 with Desktop development with C++;
- MSVC x64 toolchain;
- Windows 10/11 SDK;
- CMake;
- Git;
- the dependency set expected by the CrealityPrint build scripts.

The repository contains the upstream script:

`build_release_vs2022.bat`

It uses the Visual Studio 17 2022 generator for x64 builds.

## Upstream build flow

The script first prepares/builds dependencies and then configures and builds the slicer application.

The relevant upstream commands are equivalent to:

```bat
cmake ../ -G "Visual Studio 17 2022" -A x64 ...
cmake --build . --config Release --target deps
```

followed by application configuration/build/install.

The exact dependency prefix and SDK paths vary by environment.

## Important dependency caveat

The upstream source tree contains precompiled Creality libraries used by the slicer:

- `cr_FillTensor_library`
- `cr_tpms_library`

Some upstream helper scripts and documentation reference Creality-internal network services. Those references are preserved because they are upstream provenance/build information, but normal external users should not expect those private servers to be reachable.

See [THIRD_PARTY.md](THIRD_PARTY.md).

## Safety / reproducibility note

Do not run destructive dependency-clean/build scripts against an existing known-good development tree without reviewing them first. Use a separate build directory or disposable clone.

This repository will be updated with the exact public-tree build command and result once that build has been independently verified.
