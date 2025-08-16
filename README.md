[![windows](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/windows.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/windows.yml)
[![ubuntu](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/ubuntu.yml)
[![macos](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/macos.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/macos.yml)
[![archlinux](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/archlinux.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/archlinux.yml)
# HENTAI - SFML C++23 Modules Demo

This project demonstrates using C++23 modules with [SFML 3.x](https://www.sfml-dev.org/) in a modern C++ application.


## Requirements

- **CMake** 4.1.0 or newer (for C++23 modules support)
- **C++23 compiler**
  - MSVC 14.44
  - Clang 20
- **SFML 3.x** (prebuilt or built from source)
- **Ninja** (recommended for fast builds)

## Building

### Install Dependencies

- **SFML 3.x**  
  Download from [SFML releases](https://www.sfml-dev.org/download.php) or build from source.
- **CMake**  
  Download from [cmake.org](https://cmake.org/download/) or build from source.
- **Ninja**  
  Download from [ninja-build.org](https://ninja-build.org/) or use your package manager.


## Getting Started

```sh
git clone https://github.com/hentai0721/SFML3-Test-CXX23Modules.git
```

```sh
cd SFML3-Test-CXX23Modules
```

### 1. Build

> #### ***Windows (MSVC)***

```sh
cmake -B build -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="/path/to/SFML-3.0.1"
```

```sh
cmake --build build --config Release
```

> #### ***MSYS2/Clang64***

```sh
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

```sh
cmake --build build --config Release
```

### 2. Run

```sh
cmake --build build --config Release --target run
```

> #### ***Makefile (MSYS2/Clang64)***

```sh
make release -j$(nproc)
```

```sh
make run
```

## Notes

- C++23 modules are still experimental in many toolchains. If you encounter build issues, try updating your compiler and CMake.
- If you use a custom SFML install location, be sure to set `CMAKE_PREFIX_PATH` accordingly (especially for MSVC builds) so that CMake can locate the SFML libraries and configuration files.
- For MSVC builds, make sure to run all commands in the "x64 Native Tools Command Prompt for VS 2022" environment to ensure all required compiler and linker tools are available in your PATH.
- For MSYS2/Clang64, ensure all build commands are executed within the `clang64` MSYS2 shell to use the correct compiler and environment.
- The line `set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")` in the CMakeLists.txt enables experimental support for importing the C++ standard library as a module.  
  This UUID is specific to the CMake version and may change in future releases.  
  For more details, see the [CMake experimental features documentation](https://github.com/Kitware/CMake/blob/v4.0.3/Help/dev/experimental.rst).  
  If you encounter errors related to this setting, check the documentation or update the UUID as needed.