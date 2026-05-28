# Addons

Addons are optional extensions to the Rinegine engine. They extend core functionality with graphics, input, networking, and other capabilities.

## Addon Management

Addons are controlled via preprocessor macros defined before including `<Rinegine/Addons>`.

### Central Control: `Addons/modules.h`

This file maps high-level addon macros to their implementations and manages dependencies:

```cpp
// When RG_ALL_ADDONS is defined, enable everything:
#define RG_ALL_ADDONS
// Results in:
#define RG_Useless_addon
#define RG_POV_CAM
#define RG_WEB_SERVER
#define RG_JOYSTICK
#define RG_LANG
#define RG_PLAYER
#define RG_META_PARSE
#define RG_MOD_MANAGER
#define RG_TESTS
#define RG_GUI
// SL_ContestSilhouette is commented out
```

### Automatic Dependencies

Some addons automatically enable others:

| If defined | Also enables |
|------------|-------------|
| `RG_FPS_CAM` | `RG_GRAPH` |
| `RG_WEB_SERVER` | `RG_NETWORK` |
| `RG_JOYSTICK` | `RG_GRAPH` |
| `RG_GUI` | `RG_GRAPH` |
| `RG_MOD_MANAGER` | `RG_META_PARSE` |

### Central Entry: `Addons/set.h`

The main `Addons/set.h` file sits in namespace `Rinegine::Addons` and conditionally includes addon `set.h` files. Currently, **only `RG_META_PARSE` is active** — all other includes are commented out:

```cpp
namespace Rinegine::Addons {
#ifdef RG_META_PARSE
#include "meta_parse/set.h"
#endif
// All others are commented out
}
```

---

## Addon Reference

### Graphics Addons

The largest addon group with a three-tier architecture (low/med/high).

| Addon | Path | Description |
|-------|------|-------------|
| Graphics main | `Addons/graphics/` | Entry — includes low, med, high |
| Low-level | `Addons/graphics/low/` | Raw OpenGL, buffers, shaders, windows |
| Mid-level | `Addons/graphics/med/` | Context, events, textures, fonts |
| High-level | `Addons/graphics/high/` | Batch rendering, entities, physics |
| Main API | `Addons/graphics/main/` | User-facing shader and window API |
| Drawing | `Addons/graphics/draw/` | Entity, player, world drawing |
| Buffers | `Addons/graphics/buffer/` | VBO/VAO management |
| Context | `Addons/graphics/context/` | Rendering context |
| Textures | `Addons/graphics/texture/` | Texture loading and management |
| Fonts | `Addons/graphics/texture/font/` | Font rendering via FreeType |
| Materials | `Addons/graphics/material/` | Material/shader combinations |
| Objects | `Addons/graphics/objects/` | Scene objects |
| Physics | `Addons/graphics/physics/` | Collision detection |
| Events | `Addons/graphics/events/` | Graphics event handling |
| Generations | `Addons/graphics/generations/` | Procedural generation |
| Entities | `Addons/graphics/entitys/` | Entity definitions |
| Resources | `Addons/graphics/res/` | Resource management |

### Input Addons

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| Joystick | `RG_JOYSTICK` | `Addons/joystick/` | Gamepad/joystick input. Auto-enables `RG_GRAPH`. |
| FPS Camera | `RG_FPS_CAM` | `Addons/fpscam/` | First-person camera control. Auto-enables `RG_GRAPH`. |
| POV Camera | `RG_POV_CAM` | `Addons/povcam/` | Point-of-view camera. |

### GUI

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| GUI | `RG_GUI` | `Addons/gui/` | Graphical user interface. Auto-enables `RG_GRAPH`. |

The GUI addon currently only contains:
- `button.h` — Button widget (empty implementation)

### Audio

| Addon | Path | Description |
|-------|------|-------------|
| Sound | `Addons/sound/` | Audio playback via OpenAL. Includes `defined.h`, `audiodata.h`, `sound.h`. |

### Networking

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| Network | `RG_NETWORK` | `Addons/network/` | Client/server networking. `main.h`, `client.h`, `server.h`. Has `RG_NETWORK_IS_INIT` flag. |
| Web Server | `RG_WEB_SERVER` | `Addons/webserver/` | HTTP server. Auto-enables `RG_NETWORK`. |

### Media

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| Player | `RG_PLAYER` | `Addons/player/` | Media player. All includes commented out. |

### Localization

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| Language | `RG_LANG` | `Addons/lang/` | Localization/internationalization support. |

### Mod Support

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| Meta Parse | `RG_META_PARSE` | `Addons/meta_parse/` | Metadata parsing. Required by Mod Manager. **Currently the only active addon.** |
| Mod Manager | `RG_MOD_MANAGER` | `Addons/mod_manager/` | Mod management. Includes `Mod_Meta.h`, `Resources_Meta.h`, `Resources.h`, `Mods.h`. Auto-enables `RG_META_PARSE`. |

### Performance

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| SIMD Operations | `RG_SIMD` | `Addons/SIMD_operations/` | SIMD-optimized math operations. Includes `<immintrin.h>`, `<intrin.h>`, `multiply.h`, `addition.h`, `checking.h`. Requires `-mavx2 -mfma` compiler flags. |

### Testing / Utility

| Addon | Macro | Path | Description |
|-------|-------|------|-------------|
| Tests | `RG_TESTS` | `Addons/tests/` | Test utilities. Empty (`#pragma only`). |
| Useless Addon | `RG_Useless_addon` | `Addons/useless_addon/` | Example/demo addon. Includes `main.h`. |
| Contest Silhouette | `SL_ContestSilhouette` | `Addons/contestSilhouette/` | Contest-specific silhouette rendering. Commented out in `modules.h`. |

### Experimental

| Addon | Path | Description |
|-------|------|-------------|
| Experimental | `Addons/experimental/` | Experimental features. |
| Experemental | `Addons/experemental/` | (Alternate spelling) Experimental features. |

### Neural

| Addon | Path | Description |
|-------|------|-------------|
| Neural | `Addons/neural/` | Neural network addon. Empty (`#pragma only`). |

### Defined (Shared Definitions)

The `Addons/defined/` directory contains foundational definitions shared across addons:

| Submodule | Description |
|-----------|-------------|
| `allocator/` | Memory allocator definitions |
| `convert/` | Type conversion utilities |
| `debug/` | Debugging support |
| `defined/` | Core addon definitions |
| `files/` | File I/O utilities |
| `init/` | Initialization helpers |
| `main/` | Main addon definitions |
| `types/` | Common addon types |

---

## Addon Dependency Graph

```
Application
    │
    ├── RG_FPS_CAM ──────────→ RG_GRAPH
    ├── RG_JOYSTICK ─────────→ RG_GRAPH
    ├── RG_GUI ──────────────→ RG_GRAPH
    ├── RG_WEB_SERVER ───────→ RG_NETWORK
    ├── RG_MOD_MANAGER ──────→ RG_META_PARSE ✓ (only active one)
    │
    └── RG_ALL_ADDONS (enables all except ContestSilhouette)
```

## Enabling Addons

### Single addon

```cpp
#define RG_FPS_CAM
#define RG_JOYSTICK
#include <Rinegine/Addons>
```

### All addons

```cpp
#define RG_ALL_ADDONS
#include <Rinegine/Addons>
```

### Direct include (bypass management)

```cpp
#include "modules/include/Addons/graphics/set.h"
```

## Current State

The addon system is **partially implemented**:
- `Addons/set.h` only includes `meta_parse` — all other addons are commented out
- Many addon directories exist but contain only empty `set.h` files or stubs
- The graphics addon is the most developed, with a full low/med/high architecture
- SIMD operations require explicit compiler flags (`-mavx2 -mfma`)
