# Net Module

The Net module provides networking capabilities. It is currently a stub.

## File Structure

```
modules/include/Net/
└── set.h           # Empty file (0 bytes) — stub entry point

modules/include/Addons/network/
├── set.h           # Network addon entry
├── main.h          # Main network initialization
├── client.h        # Client-side networking
├── server.h        # Server-side networking
└── other.h         # Other utilities (commented out)
```

## Network Addon

```cpp
// Addons/network/set.h includes:
#include "main.h"
#include "client.h"
#include "server.h"
// #include "other.h"  // Commented out

static bool RG_NETWORK_IS_INIT = false;  // Init flag
```

### client.h

Client-side connection management, sending/receiving data.

### server.h

Server-side socket management, accepting connections, broadcasting.

### main.h

Network subsystem initialization. The `RG_NETWORK_IS_INIT` flag guards against double-initialization.

## Auto-Enable

The network addon is automatically enabled when `RG_WEB_SERVER` is defined:

```cpp
#ifdef RG_WEB_SERVER
#define RG_NETWORK
#endif
```

## Current State

- `modules/include/Net/set.h` is **empty** (0 bytes)
- The network addon code exists but is not integrated into the main module
- No compiled library is produced for Net
