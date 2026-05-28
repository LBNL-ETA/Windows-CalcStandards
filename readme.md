# Windows-CalcStandards

A C++20 library providing **window calculation standards** (NFRC, ISO 15099, CEN, etc.) for LBNL window thermal and optical analysis tools. Defines spectra, wavelength sets, integration rules, and method/boundary conditions read from on-disk standard files. Exposes the `window_standards` library target.

## Requirements

- C++20 compatible compiler (`g++` 11+, `clang++` 14+, MSVC 19.30+)
- CMake 3.8+ (3.21+ if you want to use the shipped CMake presets)

## Consuming Windows-CalcStandards

### Using FetchContent in CMake (recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
    window_standards
    GIT_REPOSITORY https://github.com/LBNL-ETA/Windows-CalcStandards.git
    GIT_TAG v1.2.3
)
FetchContent_MakeAvailable(window_standards)

target_link_libraries(MyTarget PRIVATE window_standards)
```

Update `GIT_TAG` to the desired release tag. Note: the library target is `window_standards` (snake_case) even though the repository is `Windows-CalcStandards`.

## Building (developers)

This is a leaf repository: it has no external library dependencies beyond GoogleTest for tests. GoogleTest is downloaded automatically via the legacy pre-FetchContent mechanism in `test/CMakeLists.txt` when configuring as the top-level project. Tests build by default (`-DBUILD_Windows_CalcStandards_tests=OFF` to disable).

### Presets

`CMakePresets.json` ships four visible configure presets, plus two hidden inheritance bases:

| Preset | When to use it |
|---|---|
| `default-debug` / `default-release` | Standard configure on any platform; CI. Picks the system default compiler (MSVC on Windows, system `cc`/`c++` on Linux/macOS). |
| `local-debug` / `local-release` | Provided for convention only; identical to `default-*` here because this repo has no LBNL siblings to override. Use as the inheritance base for personal compiler presets. |

Examples:

```
cmake --preset default-release
cmake --build build/default-release --parallel
ctest --test-dir build/default-release -C Release --output-on-failure
```

#### Per-machine compiler presets (`CMakeUserPresets.json`)

To use a specific compiler (`vs2022-release`, `gcc-13-debug`, `clang-18-release`, etc.), each developer maintains their own `CMakeUserPresets.json` next to `CMakePresets.json`. It is gitignored, read automatically by CMake (and CLion, VS Code, etc.), and stays on the developer's machine.

Personal presets `inherit` from one of the shipped presets (usually `local`) and override whatever they want. A complete realistic example -- building with WSL Clang on a Windows machine, with CLion 2023.2+ routed through the WSL toolchain automatically:

```json
{
    "version": 6,
    "configurePresets": [
        {
            "name": "clang-release",
            "displayName": "clang (Release)",
            "inherits": "local",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build/clang-release",
            "cacheVariables": {
                "CMAKE_C_COMPILER":   "clang",
                "CMAKE_CXX_COMPILER": "clang++",
                "CMAKE_BUILD_TYPE":   "Release"
            },
            "vendor": {
                "jetbrains.com/clion": {
                    "toolchain": "WSL"
                }
            }
        }
    ]
}
```

### Manual configure (without presets)

```
cmake -B build
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

### Clean rebuild

Delete the `build/` directory and re-run the configure and build commands above.

## License

See the [LICENSE](LICENSE) file.

Berkeley Lab WINDOW Calc Engine (CalcEngine) Copyright (c) 2016 - 2019, The Regents of the University of California, through Lawrence Berkeley National Laboratory (subject to receipt of any required approvals from the U.S. Dept. of Energy). All rights reserved.

If you have questions about your rights to use or distribute this software, please contact Berkeley Lab's Innovation & Partnerships Office at IPO@lbl.gov.

NOTICE.  This Software was developed under funding from the U.S. Department of Energy and the U.S. Government consequently retains certain rights.  As such, the U.S. Government has been granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable, worldwide license in the Software to reproduce, distribute copies to the public, prepare derivative works, and perform publicly and display publicly, and to permit other to do so.
