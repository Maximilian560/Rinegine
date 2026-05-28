# Rinegine

Version: 0.3.0
Edition: Beginning

## Overview

Rinegine — lightweight modular engine for 2D/3D graphics applications and games written in C++23. The engine provides custom memory management, GPU-accelerated rendering, logging, containers, and an addon system.

## Architecture

The engine is organised in layers:

```
Application (user code — rg_main())
    |
    +-- Rinegine headers  (<Rinegine/Kernel>, <Rinegine/Graphics>, ...)
            |
            +-- modules/include/        — public module headers
            +-- modules/src/            — compiled translation units
            +-- vendor/linux/           — third-party submodules (GLFW, FreeType)
```

### Directory Structure

```
Rinegine/
├── Rinegine.h                          # Master header — pulls in modules/set.h
├── Rinegine/                           # Public include paths (e.g. #include <Rinegine/Kernel>)
│   ├── Kernel
│   ├── Graphics
│   ├── Tokenize
│   ├── Net
│   ├── Neural
│   ├── WebCore
│   ├── Addons
│   ├── WIP
│   └── Old
├── modules/
│   ├── include/                        # Module headers
│   │   ├── Kernel/                     # version.h, define.h, typedef.h, kernel.h, ...
│   │   ├── Graphics/                   # set.h (stub)
│   │   ├── Tokenize/                   # tokenizer.h
│   │   ├── Audio/                      # set.h (stub)
│   │   ├── Net/                        # set.h (stub)
│   │   ├── Neural/                     # set.h (stub)
│   │   ├── WebCore/                    # set.h (stub)
│   │   ├── WIP/                        # WIP.h, allocator/
│   │   ├── Addons/                     # graphics/, gui/, sound/, network/, ...
│   │   └── *.h                         # Per-module entry-point headers
│   └── src/                            # Compiled translation units
│       ├── Kernel.cpp
│       ├── Tokenize.cpp
│       ├── WIP.cpp
│       └── */set.h                     # Internal include files
├── vendor/linux/                       # Git submodules
│   ├── glfw-src/
│   ├── freetype-src/
│   └── static/                         # Prebuilt static libraries
├── bin/
│   ├── rgcmd                           # Linux build tool
│   ├── rgcmd.exe                       # Windows (x64)
│   └── rgcmd32.exe                     # Windows (x86)
├── kernel.rgset                        # Build configuration for librg-kernel.a
├── main.cpp                            # Example user entry point
├── Doxyfile                            # Doxygen configuration
├── CHANGELOG.md
└── README.md
```

### Header Inclusion Chain

Including a module from user code follows this chain:

```
#include <Rinegine/Kernel>
  → Rinegine/Kernel (file in Rinegine/ directory)
    → modules/include/Kernel.h
      → modules/src/Kernel/set.h  (includes all Kernel sub-headers)
```

Each `Rinegine/<Module>` file in the `Rinegine/` directory is a single-line header
that points to `modules/include/<Module>.h`, which in turn includes
`modules/src/<Module>/set.h`.

## Module Status

| Module | Status | Compiled | Description |
|--------|--------|----------|-------------|
| [Kernel](modules/kernel.md) | **Stable** | `Kernel.cpp` → `librg-kernel.a` | Core: memory management, logging, strings, containers, types, platform abstraction |
| [WIP](modules/wip.md) | **Experimental** | `WIP.cpp` → `librg-wip.a` | Allocator, RawMap, experimental features |
| [Tokenize](modules/tokenize.md) | **Stub** | `Tokenize.cpp` → `librg-tokenize.a` | Source code tokenizer (implementation commented out) |
| [Graphics](modules/graphics.md) | **Stub** | — | GPU rendering addon tree (low/med/high architecture), no compiled core yet |
| [Audio](modules/audio.md) | **Stub** | — | Audio (OpenAL-based) |
| [Net](modules/net.md) | **Stub** | — | Networking |
| [Neural](modules/neural.md) | **Stub** | — | Neural networks |
| [WebCore](modules/webcore.md) | **Stub** | — | Web functionality (CURL-based) |

## Addons

Addons live under `modules/include/Addons/` and are enabled by preprocessor macros.
See [Addons Documentation](addons/README.md) for the full list.

### Addon Dependency Graph

```
RG_ALL_ADDONS
  ├── RG_Useless_addon
  ├── RG_POV_CAM
  ├── RG_WEB_SERVER ────→ RG_NETWORK (auto)
  ├── RG_JOYSTICK ──────→ RG_GRAPH (auto)
  ├── RG_LANG
  ├── RG_PLAYER
  ├── RG_META_PARSE
  ├── RG_MOD_MANAGER ────→ RG_META_PARSE (auto)
  ├── RG_TESTS
  └── RG_GUI ────────────→ RG_GRAPH (auto)

RG_FPS_CAM ──────────────→ RG_GRAPH (auto)
```

### Currently Active Addons

Only `RG_META_PARSE` is enabled in `Addons/set.h`. Most other addon includes are commented out.

## Build System

### rgcmd

Custom build tool located at `bin/rgcmd`.

**How it works:**

1. Searches the current directory for a `.rgset` file
2. If not found, prompts the user for a config name (without `.rgset` extension)
3. Reads `<name>.rgset` and executes the build

**Building the kernel library:**

```bash
cd /path/to/Rinegine   # must be in project root
rgcmd
# When prompted, type: kernel
```

This compiles `modules/src/Kernel.cpp` using settings from `kernel.rgset`.

### Build Configuration Format (.rgset)

```
set {
  mode {
    clear,       // Clean output directory before build
    static,      // Produce static library (.a)
    createlib,   // Create library file
    llvm,        // Use LLVM/Clang toolchain
    console,     // Console application
    debug        // Debug symbols + RG_DEBUG define
  },
  var {
    source = "modules/src/Kernel.cpp",
    bit = "64",
    run = false,
    name = "rg-kernel",
    flags = "-g -DRGLOCK_DEBUG -DRG_DEBUG -std=c++23 -Wall -Wextra -Wpedantic ..."
  }
}
```

### Compiler Flags

The kernel is compiled with strict warnings:
```
-std=c++23
-Wall -Wextra -Wpedantic
-Wreturn-type -Wuninitialized -Wunused -Wconversion
-Wshadow -Wnon-virtual-dtor -Wdelete-non-virtual-dtor
-g
```

### Output Artifacts

| File | Platform | Source |
|------|----------|--------|
| `librg-kernel.a` | Linux | `kernel.rgset` |
| `librg-kernel-win32.a` | Windows | `kernel-win32.rgset` |
| `librg-tokenize.a` | Linux | Tokenize build |
| `librg-wip.a` | Linux | WIP build |

### Cross-Compilation

Windows builds on Linux use MinGW-w64 13.2.0. The toolchain binaries are referenced via vendor submodules.

## Dependencies

| Library | Version | Status | Purpose |
|---------|---------|--------|---------|
| GLFW | 3.4.0 | Ready | Window creation, input handling |
| FreeType | 2.13.2 | Ready | Font rasterization |
| GLAD | 3.3.0 | Ready | OpenGL function loading |
| OpenAL Soft | 1.23.1 | WIP | Audio playback |
| STB | 1.0.0 | Ready | Image loading (single-header) |
| CURL | 8.8.0 | WIP | HTTP client |
| MinGW-w64 | 13.2.0 | Ready | Windows cross-compilation |

Dependencies are stored as git submodules in `vendor/linux/`.

## Getting Started

### Minimal Program

```cpp
// main.cpp
#include <Rinegine/Kernel>

int rg_main() {
    rg_cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Entry Point Mechanism

The engine intercepts the standard `main()` function through `interPoint.h`:

- On Linux without `RG_UTF`: generates `int main(int argc, char* argv[])` → calls `Kernel::InterPoint()`
- On Windows or with `RG_UTF`: generates `int wmain(int argc, wchar_t* argv[])` → calls `Kernel::InterPoint()`

The user defines `rg_main()` which is called by `InterPoint()` after initialisation.

When building the library itself (`RinegineLib` defined), no `main()` is generated.

### Unicode Mode

Define `RG_UTF` (or `UNICODE` on Windows) to switch to wide-character mode:

| Identifier | Without RG_UTF | With RG_UTF |
|------------|---------------|-------------|
| `rg_string` | `std::string` | `std::wstring` |
| `rg_char` | `char` | `wchar_t` |
| `rg_cout` | `std::cout` | `std::wcout` |
| `rg_cin` | `std::cin` | `std::wcin` |
| `rg_to_string_()` | `std::to_string()` | `std::to_wstring()` |
| `RG_L` | (empty) | `L` |

On Linux, `RG_UTF` is disabled by default with a `#warning`.

## Documentation Structure

| Document | Content |
|----------|---------|
| [Kernel Module](modules/kernel.md) | Memory management, logging, strings, containers, types, macros, platform API |
| [WIP Module](modules/wip.md) | Custom allocator, RawMap, thread-local pools |
| [Tokenize Module](modules/tokenize.md) | Tokenizer (planned API) |
| [Graphics Module](modules/graphics.md) | Rendering architecture (low/med/high) |
| [Audio Module](modules/audio.md) | Audio subsystem |
| [Net Module](modules/net.md) | Networking |
| [Neural Module](modules/neural.md) | Neural networks |
| [WebCore Module](modules/webcore.md) | Web utilities |
| [Addons](addons/README.md) | All optional addons, dependency graph, enabling macros |
| [Build Guide](guides/build.md) | rgcmd usage, .rgset format, troubleshooting |
