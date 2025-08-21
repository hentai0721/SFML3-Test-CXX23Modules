[![windows](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/windows.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/windows.yml)
[![ubuntu](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/ubuntu.yml)
[![macos](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/macos.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/macos.yml)
[![archlinux](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/archlinux.yml/badge.svg)](https://github.com/hentai0721/SFML3-Test-CXX23Modules/actions/workflows/archlinux.yml)
# HENTAI - SFML C++23 Modules Demo

## Requirements

- **CMake** 4.1.0 or newer (for C++23 modules support)
- **C++23 compiler**
  - **MSVC** 14.44
  - **Clang** 20
- **SFML3**
- **Ninja** 1.13.0
- **Make** 4.4.1

### Install Dependencies

> #### ***MSYS2/Clang64***

```sh
pacman -Syu
```

```sh
pacman -S --noconfirm --needed mingw-w64-clang-x86_64-{toolchain,cmake,ninja} base-devel git
```

```sh
git clone --branch 3.0.1 --depth 1 https://github.com/SFML/SFML.git
```

```sh
cd SFML
```

```sh
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/clang64 -DSFML_USE_STATIC_STD_LIBS=ON
```

```sh
cmake --build build --config Release
```

```sh
cmake --build build --config Release --target install
```

## Getting Started

```sh
git clone https://github.com/hentai0721/SFML3-Test-CXX23Modules.git
```

```sh
cd SFML3-Test-CXX23Modules
```

### 1. Build

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

#### ***Makefile (MSYS2/Clang64)***

```sh
make release -j$(nproc)
```

```sh
make run
```

## Notes

- C++23 modules are still experimental in many toolchains. If you encounter build issues, try updating your compiler and CMake.
- For MSYS2/Clang64, ensure all build commands are executed within the `clang64` MSYS2 shell to use the correct compiler and environment.
- The line `set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")` in the CMakeLists.txt enables experimental support for importing the C++ standard library as a module.  
  This UUID is specific to the CMake version and may change in future releases.  
  For more details, see the [CMake experimental features documentation](https://github.com/Kitware/CMake/blob/v4.0.3/Help/dev/experimental.rst).  
  If you encounter errors related to this setting, check the documentation or update the UUID as needed.