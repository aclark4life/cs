# CS 466 - Operating Systems

Principles of OS design: process management, file I/O, and network programming.

## Projects

### shell/
A custom Unix-like shell with I/O redirection and piping support (`handle_pipe.c`, `handle_greater_than.c`, `handle_less_than.c`, `handle_bg.c`) and its own tokenizer (`tokenize.c`, `dump_tokens.c`). See `shell/README.md` for details.

### tok/
A token-ring election protocol implementation (`tok.c`) using UDP sockets (`socket.c`, `gethostbyaddr.c`) — processes pass a token and hold elections when it's lost.
```bash
cd tok && make
```

### sort/
An external sort using a forked child process to read/merge buffered input (`main.c`, `fread_long.c`, `read_long.c`).

### dir/
A minimal directory-listing/file-reading exercise (`main.c`).

### cs-slip/
Archived SLIP/PPP dial-up networking tools used for off-campus access: `mgetty+sendfax`, `minicom`, and `ppp` source tarballs, plus configuration templates (`options.tpl`) and setup docs (`Docs/`).

## Building

Most C projects compile with a plain `gcc` invocation or an included `Makefile` (`shell/`, `tok/`).
