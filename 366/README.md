# CS 366 - Systems Level Programming

16-bit x86 Assembly (TASM/MASM syntax) for DOS: device drivers, BIOS/DOS interrupt programming, and a "Missile Command"-style game.

## Highlights

### rocks.asm
The "Missile Command" style game — cities to defend, incoming "rocks," and player-fired counter-missiles, driven directly through BIOS video/keyboard interrupts. Supporting modules: `cities.asm`/`cities.h`, `image.asm`/`image.h`, `screen.asm`/`screen.h`, `shield.asm`/`shield.h`, `random.asm`/`random.h`.

### blkdrv.asm / dummy-block-driver.asm / binkdrv.asm
DOS block device driver exercises (device driver header, strategy/interrupt routines). `blkdrv.asm` and `binkdrv.asm` are archived as email submissions to the professor.

### fixkb.asm / kbon.asm / scankb.asm / trapint.asm
Keyboard scan-code handling and interrupt-vector trapping.

### add.asm / div.asm / swapab.asm / dollar.asm / 64bit.asm
Small arithmetic and register-manipulation exercises.

### dumpdisk.asm / writprot.asm / echo.asm / exec.asm / rename.asm / myname.asm / hello.asm
DOS interrupt (`INT 21h`) exercises: disk sector dumping, write protection, echoing input, executing programs, and file renaming.

### com3.asm / timebomb.asm / jen.asm / point.h / macros.h / dos.h
Miscellaneous serial-port, timer, and shared header/macro files used by the above programs.

## Building

Requires a DOS environment (or emulator). `bin/tasm.exe` and `bin/tlink.exe` are the original Turbo Assembler/Linker; `dosbox-build.sh` and `link.bat` automate assembling/linking under DOSBox.
```bash
./dosbox-build.sh rocks.asm
```
