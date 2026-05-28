# WebCore Module

The WebCore module provides web-related functionality, primarily HTTP client capabilities via CURL.

## File Structure

```
modules/include/WebCore/
└── set.h           # Empty file (0 bytes) — stub entry point

modules/include/Addons/webserver/
└── set.h           # Web server addon entry — includes webserver.h
    └── webserver.h # Web server implementation (TODO: "from REG")
```

## Dependencies

- **CURL 8.8.0** — HTTP client library (WIP)

## Web Server Addon

The `webserver` addon provides HTTP server functionality. The implementation is marked with a TODO note "from REG" (likely meaning it needs to be ported from a previous codebase called REG).

## Current State

- `modules/include/WebCore/set.h` is **empty** (0 bytes)
- The webserver addon code exists but is incomplete
- No compiled library is produced for WebCore
