# CS 474 - Assembly Programming

Motorola 68000 assembly homework exercises, targeting a bare-metal/embedded environment (register-based I/O via `TRAP #14` and memory-mapped PIT peripherals).

## Contents

### hw4_1.asm - hw4_7.asm
Homework set 4: string/buffer manipulation exercises (reversing/printing a name, buffer operations) using direct memory addressing (`ORG $1000`/`$2000`).

### hw5_1.asm / hw5_2.asm
Homework set 5: modular I/O routines (`GETCH`, `OUTCH`, `CRLF`, `CLEAR`, `OUTSTR`), split into a reusable library (`hw5_1.asm`, mirrored in `stdio.asm`) and a driver program (`hw5_2.asm`) that links against it via `EXTERNAL`.

### hw6-1.asm / hw6-2.asm
Homework set 6: programming the Parallel Interface & Timer (PIT) — port configuration registers (`PGCR`, `PACR`, `PADDR`) and timer control registers (`TCR`, `TIVR`, `CNTR`).

### stdio.asm / huh.asm
Shared low-level I/O routine library (character/string output, screen clear) used by the homework programs above.

## Building

Assembles with a Motorola 68000 assembler (e.g. the course's cross-assembler); each `hwN_x.asm` typically links against `stdio.asm` for the I/O routines it calls via `EXTERNAL`.
