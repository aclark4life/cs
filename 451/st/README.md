# Hash Table and Symbol Table Implementation

Implementation of a scoped symbol table using hash tables for compiler/interpreter use.

## Components

### Symbol Table (`st.c`, `st.h`, `stP.h`)
Scoped symbol table with nested scope support.

**Features:**
- Multiple nested scopes (up to 10 levels)
- Proper shadowing semantics
- Efficient lookup (searches from current scope upward)
- Hash table backing for each scope

**API:**
```c
tSymbolTable st_initialize(int size,
                          int (*compare_fn)(void*, void*),
                          int (*hash_fn)(void*));
int st_open_scope(tSymbolTable st);
int st_close_scope(tSymbolTable st);
void st_add(tSymbolTable st, void *symbol);
int st_lookup(tSymbolTable st, const void *symbol);
void st_dump(tSymbolTable st, void (*print_fn)(void*));
void st_free(tSymbolTable st);
```

**Example Usage:**
```c
// Create symbol table
tSymbolTable st = st_initialize(100, symbol_compare, symbol_hash);

// Open global scope
st_open_scope(st);
st_add(st, create_symbol("x", VAR_TYPE));

// Open nested scope
st_open_scope(st);
st_add(st, create_symbol("x", VAR_TYPE));  // Shadows outer x
st_add(st, create_symbol("y", VAR_TYPE));

// Lookup finds innermost
int scope = st_lookup(st, "x");  // Returns 1 (inner scope)

// Close inner scope
st_close_scope(st);

// Now lookup finds outer
scope = st_lookup(st, "x");  // Returns 0 (global scope)
scope = st_lookup(st, "y");  // Returns -1 (not found)

st_free(st);
```

### Symbol (`symbol.c`, `symbol.h`, `symbolP.h`)
Symbol table entries.

**API:**
```c
tSymbol symbol_initialize(char *text, int kind);
int symbol_compare(tSymbol s1, tSymbol s2);
int symbol_hash(tSymbol s);
void symbol_print(tSymbol s);
void symbol_free(tSymbol s);
```

## Design

### Scope Management
- Scopes stored as array of hash tables
- `current_scope` tracks active scope level
- Lookup searches from current scope to scope 0
- Sentinel value (-1) marks end of scope array

### Hash Function
Simple hash using first character of symbol name.
Can be replaced with better hash function via function pointer.

### Memory Management
- Symbol names are copied (not referenced)
- All memory properly freed on scope close
- No memory leaks

## Building

```bash
gcc -Wall -Wextra -c st.c symbol.c
# Link with your hash table implementation
```

## Dependencies

Requires:
- `ht.h` - Hash table interface (from `../assignment.1/`)
- `util.h` - Utility functions (check_malloc, string_copy)

## Testing

See test files for usage examples.

## Notes

- Maximum 10 scopes (configurable via MAX_SCOPES)
- Hash table size configurable per symbol table
- Thread-unsafe (not designed for concurrent access)
