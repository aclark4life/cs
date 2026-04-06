# Shell Implementations

Multiple iterations of a Unix shell implementation, demonstrating progressive feature additions.

## Versions

### Version 1 (`1/`)
Basic shell with:
- Command execution via fork/exec
- Simple tokenization
- Exit command

**Files:**
- `main.c` - Main loop
- `do_fork.c` - Process creation
- `tokenize.c` - Input parsing
- `prompt.c` - User prompt
- `read_long.c` - Input reading

### Version 2 (`2/`)
Adds:
- Improved token handling
- Better error checking

### Version 3 (`3/`)
Adds:
- Background job support
- More robust parsing

### Version 4 (`4/`)
Adds:
- Memory management improvements
- Token cleanup

### Dave's Shell (`dave-s-shell/`)
Full-featured shell with:
- **Background jobs** - Run commands with `&`
- **I/O redirection** - Use `<` and `>`
- **Pipes** - Chain commands with `|`
- **Job control** - `jobs` and `kill` commands
- **Proper memory management** - No leaks

**Usage:**
```bash
cd dave-s-shell
make
./shell

# Examples:
command: ls -la
command: cat file.txt | grep pattern
command: sleep 10 &
command: jobs
command: kill 0
```

**Features:**
- Handles multiple redirections
- Supports nested pipes
- Background process tracking
- Proper signal handling
- Memory leak prevention

## Building

Each version can be compiled separately. For dave-s-shell:
```bash
cd dave-s-shell
gcc -Wall -Wextra *.c -o shell
```

## Known Limitations

- No support for multiple redirections to same stream
- No command history
- No tab completion
- Limited error messages for complex syntax errors

## Architecture

All versions follow similar architecture:
1. **Read** - Get input from user
2. **Parse** - Tokenize input
3. **Execute** - Fork and exec command
4. **Wait** - Wait for completion (unless background)

Dave's shell adds:
- Job table for background processes
- Redirection handling before exec
- Pipe creation and management
