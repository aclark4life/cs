#!/usr/bin/env bash
# Assembles and links one or more 366/*.asm files using the original
# Turbo Assembler/Linker (tasm.exe/tlink.exe) via DOSBox Staging.
#
# Usage: dosbox-build.sh [--watch] <output-name> <file1.asm> [file2.asm ...]
#
# By default the build runs headless (fast, output logged and printed
# after the fact) - the DOSBox window flashes open and closes on its
# own. Pass --watch as the first argument to instead keep the DOSBox
# window open and show tasm/tlink running live on-screen; it pauses at
# the end so you can read the output before closing the window.
#
# Multiple input files are linked together in the given order (mirrors
# the "+"-joined tlink syntax used by the original 366/link.bat, e.g.
# for the multi-module "rocks" game).
#
# Requires: DOSBox Staging (brew install --cask dosbox-staging)
set -euo pipefail

DOSBOX="/Applications/DOSBox Staging.app/Contents/MacOS/dosbox"
DIR="$(cd "$(dirname "$0")" && pwd)"
WORK="$DIR/bin"

watch=0
if [ "${1:-}" = "--watch" ]; then
    watch=1
    shift
fi

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 [--watch] <output-name> <file1.asm> [file2.asm ...]" >&2
    exit 1
fi

if [ ! -x "$DOSBOX" ]; then
    echo "DOSBox Staging not found at: $DOSBOX" >&2
    echo "Install it with: brew install --cask dosbox-staging" >&2
    exit 1
fi

OUT="$1"
shift

mkdir -p "$WORK"
rm -f "$WORK"/*

# DOS 8.3 filenames: copy each source into bin/ under an 8-char-safe
# name so tasm/tlink never choke on long filenames or ~1-mangling.
names=()
for f in "$@"; do
    src="$DIR/$f"
    [ -f "$src" ] || { echo "Not found: $src" >&2; exit 1; }
    base="$(basename "$f" .asm)"
    short="$(echo "$base" | cut -c1-8)"
    cp "$src" "$WORK/$short.asm"
    names+=("$short")
done

conf="$(mktemp /tmp/dosbox-build-XXXX.conf)"
if [ "$watch" -eq 1 ]; then
    {
        echo "[autoexec]"
        echo "mount c \"$DIR\""
        echo "c:"
        echo "set path=%path%;c:\\"
        echo "cd bin"
        for n in "${names[@]}"; do
            echo "tasm $n.asm"
        done
        joined="$(IFS=+; echo "${names[*]}")"
        echo "tlink $joined;"
        echo "pause"
    } > "$conf"
    "$DOSBOX" -conf "$conf"
else
    {
        echo "[autoexec]"
        echo "mount c \"$DIR\""
        echo "c:"
        echo "set path=%path%;c:\\"
        echo "cd bin"
        for n in "${names[@]}"; do
            echo "tasm $n.asm >> build.log"
        done
        joined="$(IFS=+; echo "${names[*]}")"
        echo "tlink $joined; >> build.log"
        echo "exit"
    } > "$conf"
    rm -f "$WORK/build.log"
    "$DOSBOX" -conf "$conf" -fastlaunch >/dev/null 2>&1
    cat "$WORK/build.log" 2>/dev/null || true
fi
rm -f "$conf"

first="${names[0]}"
result="$(find "$WORK" -maxdepth 1 -iname "${first}.exe" | head -1)"
if [ -n "$result" ]; then
    cp "$result" "$DIR/$OUT.exe"
    echo "Built: $DIR/$OUT.exe"
    status=0
else
    echo "Build failed: no .exe produced for '$first'" >&2
    status=1
fi

# Clean up intermediate DOS build artifacts; tasm.exe/tlink.exe live
# directly under 366/, not bin/, so the whole scratch dir can be emptied.
rm -f "$WORK"/*

exit "$status"
