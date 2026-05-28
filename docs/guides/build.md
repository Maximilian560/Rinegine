# Build Guide

This guide covers building Rinegine with the `rgcmd` build tool.

## Prerequisites

### Linux

- GCC or Clang with C++23 support
- Standard development headers (`build-essential` or equivalent)
- `mmap` support (standard on Linux)

### Windows (cross-compilation from Linux)

- MinGW-w64 13.2.0
- Windows vendor libraries in `vendor/linux/`

## The rgcmd Tool

Located in `bin/`:

| File | Platform | Architecture |
|------|----------|-------------|
| `rgcmd` | Linux | Native |
| `rgcmd.exe` | Windows | x64 |
| `rgcmd32.exe` | Windows | x86 |

### How It Works

1. `rgcmd` scans the current directory for `.rgset` files
2. If exactly one `.rgset` file is found, it uses it
3. If none are found, it prompts: "enter config name"
4. User types the config name (without `.rgset` extension)
5. `rgcmd` reads `<name>.rgset` and executes the build

### Basic Usage

```bash
# Navigate to project root (where .rgset files are)
cd /path/to/Rinegine

# Build using existing config
rgcmd
# When prompted: kernel

# If kernel.rgset is the only config, it may auto-select
```

## Build Configuration Format (.rgset)

The `.rgset` format uses a custom DSL (domain-specific language):

```
set {
  mode {
    clear,       // Clean output directory before building
    static,      // Produce a static library (.a)
    createlib,   // Create a library file
    llvm,        // Use LLVM/Clang toolchain
    console,     // Build as console application
    debug        // Include debug symbols (-g) and define RG_DEBUG
  },
  var {
    source = "modules/src/Kernel.cpp",   // Source file(s)
    bit = "64",                           // Target architecture (32/64)
    run = false,                          // Run the output after build
    name = "rg-kernel",                   // Output library name (lib<name>.a)
    flags = "-g -DRGLOCK_DEBUG -DRG_DEBUG -std=c++23 ..."  // Compiler flags
  }
}
```

### Mode Flags

| Flag | Effect |
|------|--------|
| `clear` | Delete previous build artifacts before compiling |
| `static` | Link as static library (`ar rcs`) |
| `createlib` | Output a `.a` (Linux) or `.lib` (Windows) file |
| `llvm` | Use `clang++` instead of `g++` |
| `console` | Build as executable console application (not a library) |
| `debug` | Add `-g` for debug symbols, define `RG_DEBUG` preprocessor macro |

### Variables

| Variable | Description |
|----------|-------------|
| `source` | Path to the source file to compile |
| `bit` | Target architecture: `32` or `64` |
| `run` | Whether to execute the output binary after building |
| `name` | Name of the output library (without `lib` prefix and `.a` suffix) |
| `flags` | Compiler flags (C++ standard, warnings, preprocessor defines) |

## Existing Configurations

### kernel.rgset

Builds the Kernel library:

```
set {
  mode { clear, static, createlib, llvm, console, debug },
  var {
    source = "modules/src/Kernel.cpp",
    bit = "64",
    run = false,
    name = "rg-kernel",
    flags = "-g -DRGLOCK_DEBUG -DRG_DEBUG -std=c++23 -Wall -Wextra -Wpedantic -Wreturn-type -Wuninitialized -Wunused -Wconversion -Wshadow -Wnon-virtual-dtor -Wdelete-non-virtual-dtor -g"
  }
}
```

### kernel-win32.rgset

Builds the Kernel library for Windows (cross-compilation).

### Example Configurations

`example.rgset` — example build configuration for user applications.

## Creating a New Build Configuration

Create a `.rgset` file in the project root:

```
// mymodule.rgset
set {
  mode {
    clear,
    static,
    createlib,
    debug
  },
  var {
    source = "modules/src/MyModule.cpp",
    bit = "64",
    run = false,
    name = "rg-mymodule",
    flags = "-std=c++23 -Wall -Wextra -Wpedantic"
  }
}
```

Build:

```bash
rgcmd
# Enter: mymodule
```

## Compiler Flags Reference

### Warning Flags (used in kernel.rgset)

| Flag | Purpose |
|------|---------|
| `-Wall` | Enable most warnings |
| `-Wextra` | Enable extra warnings |
| `-Wpedantic` | Strict ISO C++ compliance warnings |
| `-Wreturn-type` | Warn on missing return statements |
| `-Wuninitialized` | Warn on use of uninitialized variables |
| `-Wunused` | Warn on unused variables/parameters |
| `-Wconversion` | Warn on implicit type conversions |
| `-Wshadow` | Warn on variable shadowing |
| `-Wnon-virtual-dtor` | Warn on classes with non-virtual destructors |
| `-Wdelete-non-virtual-dtor` | Warn on delete through base pointer |

### Preprocessor Defines

| Define | Effect |
|--------|--------|
| `RG_DEBUG` | Enables logging macros (`RG_LOG_*`) |
| `RGLOCK_DEBUG` | Enables lock logging with `RG_HERE_FILE_NAME` |
| `RG_UTF` | Enable wide-character mode |
| `RinegineLib` | Prevent `main()` generation in interPoint.h |
| `RinegineKernel` | Mark as Kernel compilation |
| `RinegineLibWIP` | Mark as WIP compilation |
| `RG_MEM_LIMIT` | Set memory allocation limit (bytes) |

## Output Artifacts

After a successful build, library files appear in the project root:

| File | Config | Platform |
|------|--------|----------|
| `librg-kernel.a` | kernel.rgset | Linux |
| `librg-kernel-win32.a` | kernel-win32.rgset | Windows |
| `librg-tokenize.a` | Tokenize build | Linux |
| `librg-wip.a` | WIP build | Linux |

## Linking Against Rinegine

When building your application, link against the appropriate library:

```bash
g++ -std=c++23 main.cpp -lrg-kernel -o myapp
# Add -lrg-wip if using WIP features
# Add -lrg-tokenize if using Tokenize
```

On Linux, you may also need to link system libraries:
```bash
g++ -std=c++23 main.cpp -lrg-kernel -lm -lrt -o myapp
```

## Troubleshooting

### "rgset file not found"

Ensure you are running `rgcmd` from the directory containing the `.rgset` file, or provide the correct path.

### Compilation fails with type errors

- Ensure your compiler supports C++23
- Check that `RinegineLib` is defined when building the library (prevents `main()` collision)
- On Windows cross-compilation, ensure MinGW-w64 13.2.0 is installed

### Windows build fails on non-NTFS disk

This was a known issue fixed in version 0.3.0. Ensure you have the latest code.

### Ambiguous function call errors (itos/itows)

This was fixed in version 0.3.0. The `itos` and `itows` overloads were made unambiguous.

### Linking fails with undefined references

- Ensure you are linking against the correct library (`-lrg-kernel`, `-lrg-wip`, etc.)
- Check that the library file exists in the expected location
- For WIP features, ensure `-lrg-wip` is included

### Runtime crashes

- Check log files for error messages (Kernel creates logs by default)
- Enable `Debug::open_log_after_error(true)` for more details
- Use `RG_LOG_DEBUG()` throughout initialization to narrow down the issue

## Build Matrix

| Target | Config | Modes | Output |
|--------|--------|-------|--------|
| Kernel (Linux) | `kernel.rgset` | static, createlib, debug | `librg-kernel.a` |
| Kernel (Windows) | `kernel-win32.rgset` | static, createlib | `librg-kernel-win32.a` |
| Tokenize | (tokenize config) | static, createlib | `librg-tokenize.a` |
| WIP | (WIP config) | static, createlib | `librg-wip.a` |
| User application | `example.rgset` | console | Custom binary |
