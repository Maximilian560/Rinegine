# Graphics Module

The Graphics module provides GPU-accelerated 2D/3D rendering. Unlike the Kernel module, Graphics is not a compiled library — it exists entirely as an addon tree under `modules/include/Addons/graphics/`.

## File Structure

```
modules/include/Graphics/
└── set.h           # Empty file (0 bytes) — stub entry point

modules/include/Addons/graphics/
├── set.h           # Graphics addon entry — includes low/, med/, high/
├── defined.h       # Graphics-specific definitions
├── encoding.h      # Graphics encoding utilities
├── rinegine.h      # Graphics namespace setup
├── scenes.h        # Scene management
├── start.h         # Graphics startup/init
├── rg_main.h       # Graphics main loop (commented out)
├── otherFeatures.h # Miscellaneous features
│
├── low/            # Low-level OpenGL
│   ├── set.h
│   ├── init/       # OpenGL initialization
│   ├── types/      # Raw type wrappers
│   │   ├── buffer/
│   │   ├── shader/
│   │   └── window/
│   └── defined/
│       ├── res/    # Resource definitions
│       └── set.h
│
├── med/            # Mid-level abstractions
│   ├── set.h
│   ├── context/    # Rendering context
│   ├── defined/    # Mid-level definitions
│   ├── events/     # Event system
│   ├── types/      # Type definitions
│   └── texture/
│       ├── set.h
│       └── font/   # Font texture handling
│
├── high/           # High-level features
│   ├── set.h
│   ├── init/       # High-level init
│   ├── batch/      # Batched rendering
│   ├── entitys/    # Entity system
│   ├── features/   # Feature modules
│   ├── objects/    # Object management
│   └── physics/    # Physics integration
│
├── main/           # Primary graphics API
│   ├── set.h
│   ├── shader/     # Shader management
│   └── window/     # Window management
│
├── buffer/         # Buffer utilities
├── context/        # Context management
├── draw/           # Drawing primitives
│   ├── set.h
│   ├── entity/     # Entity drawing
│   ├── player/     # Player rendering
│   └── world/      # World/terrain rendering
│
├── entitys/        # Entity definitions
├── events/         # Graphics events
├── generations/    # Procedural generation
├── material/       # Material system
├── objects/        # Object types
├── physics/        # Physics utilities
├── res/            # Resource management
└── texture/        # Texture utilities
    └── font/       # Font rendering
```

## Three-Tier Architecture

Graphics is organised into three abstraction levels:

### Low Level (`low/`)

Direct OpenGL wrappers and raw type management:
- **Buffer** — VBO, VAO, EBO management
- **Shader** — GLSL shader compilation and uniform handling
- **Window** — GLFW window context

This layer is closest to the hardware. Code here deals with raw OpenGL calls, GLAD function loading, and GLFW context management.

### Mid Level (`med/`)

Abstractions over the low-level primitives:
- **Context** — Rendering context that groups shaders, buffers, and state
- **Events** — Window and input event handling
- **Texture** — Texture loading, filtering, and font texture atlases
- **Types** — Higher-level type definitions (e.g. `RG_Texture`, `RG_Shader`)

### High Level (`high/`)

Game-oriented features built on top of mid and low levels:
- **Batch** — Batched rendering for performance (reduces draw calls)
- **Entitys** — Entity-component-like system
- **Features** — Additional capabilities (lighting, particles, etc.)
- **Objects** — Scene objects with transforms and materials
- **Physics** — Collision detection and response

## Main API (`main/`)

The `main/` directory provides the primary user-facing API:
- **Shader** — Shader program management (compile, link, use)
- **Window** — Window creation, resize, event polling

## Dependencies

- **GLFW 3.4.0** — Window and input
- **GLAD 3.3.0** — OpenGL loader
- **FreeType 2.13.2** — Font rasterization
- **STB** — Image loading

## Enabling Graphics

```cpp
#define RG_GRAPH
#include <Rinegine/Addons>
```

Or indirectly through addons that auto-enable it:
```cpp
#define RG_FPS_CAM   // auto-enables RG_GRAPH
#define RG_GUI       // auto-enables RG_GRAPH
#define RG_JOYSTICK  // auto-enables RG_GRAPH
```

## Current State

The `modules/include/Graphics/set.h` file is **empty** (0 bytes). All graphics code lives in the addon tree. The `Addons/set.h` file currently only includes `meta_parse` — the graphics addon includes are commented out in the main set.h.

The graphics addon is functional when its headers are included directly, but it is not yet integrated into the main module system.
