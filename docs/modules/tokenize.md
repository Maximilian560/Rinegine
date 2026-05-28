# Tokenize Module

The Tokenize module provides source code tokenization. It is currently a stub — the implementation is entirely commented out.

## File Structure

```
modules/include/Tokenize/
├── set.h           # Entry point — includes tokenizer.h
└── tokenizer.h     # Tokenizer class (commented out)

modules/src/Tokenize/
├── set.h           # Empty namespace Rinegine::Tokenize
└── (Tokenize.cpp — translation unit)
```

## Planned API

The `Tokenizer` class is defined in `tokenizer.h` but fully commented out:

```cpp
namespace Rinegine::Tokenize {
    class Tokenizer {
        Kernel::Array<uchar> lexes;                    // Lexeme type arrays
        size_t pos = 0;                                // Current parse position
        size_t _main_size_of_chunk = 8192;             // 8 KiB default buffer
        std::string buffer;                            // Input buffer
        Kernel::Array<Kernel::RG_Map<int>> tokens;     // Token storage

    public:
        void init() {                                  // Must call before use
            tokens.resize(_main_size_of_chunk);
        }

        void set_size_chunk(size_t size) {
            if (pos == 0)
                _main_size_of_chunk = size;
            else
                RG_LOG_LOCK_ERROR("Cannot change chunk size after starting parsing");
        }
    };
}
```

### Design Notes

- **Chunk-based allocation**: Tokens are stored in pre-allocated chunks of `_main_size_of_chunk` elements. This avoids frequent reallocations during parsing.
- **`set_size_chunk()`**: Can only be called before `init()` or before any parsing has occurred. Once `pos > 0`, changing chunk size is an error.
- **`lexes`**: Planned to store different lexeme categories (operators, keywords, literals, etc.) as `uchar` type codes.
- **`tokens`**: Will use `RG_Map<int>` (not yet implemented) to map token positions to token data.

## Current State

- `modules/include/Tokenize/tokenizer.h` — class definition is **entirely commented out**
- `modules/src/Tokenize/set.h` — contains only an empty `namespace Rinegine::Tokenize {}`
- `modules/src/Tokenize.cpp` — translation unit that includes headers but has no implementation

## Build Output

The Tokenize module is compiled into `librg-tokenize.a` via its own `.rgset` configuration, but the resulting library is essentially empty (no symbols).
