# Audio Module

The Audio module provides audio playback capabilities using OpenAL Soft.

## File Structure

```
modules/include/Audio/
└── set.h           # Empty file (0 bytes) — stub entry point

modules/include/Addons/sound/
├── set.h           # Sound addon entry
├── defined.h       # Sound-specific definitions
├── audiodata.h     # Audio data structures
└── sound.h         # Main sound API
```

## Dependencies

- **OpenAL Soft 1.23.1** — Cross-platform 3D audio (WIP)

The OpenAL include (`AL/al.h`) is currently commented out in the sound addon.

## Sound Addon Structure

```cpp
// Addons/sound/set.h includes:
#include "defined.h"
#include "audiodata.h"
#include "sound.h"
// #include <AL/al.h>  // Currently commented out
```

### audiodata.h

Contains audio data structures for loaded sound buffers.

### sound.h

Main sound API — loading, playback, 3D positioning.

## Current State

- `modules/include/Audio/set.h` is **empty** (0 bytes)
- The sound addon code exists but the OpenAL dependency is not yet linked
- No compiled library is produced for Audio
