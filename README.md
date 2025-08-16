# And Goodbye — College Game Re-release (SDL2)

A small top‑down game originally built for college coursework, now re-released using SDL2 for portability.

- Rendering, input, and windowing are implemented with SDL2 and SDL2_image.
- Maps are plain-text grids validated at load time.
- Assets are simple XPM bitmaps.

## Repository Layout

- [Makefile](Makefile) — cross‑platform build (Windows/Linux/macOS)
- [src/](src/) — game sources
  - Core: [src/and_goodbye.c](src/and_goodbye.c), [src/config.c](src/config.c)
  - Map I/O: [src/render.c](src/render.c), [src/read_fd.c](src/read_fd.c), [src/split_string.c](src/split_string.c)
  - Gameplay: [src/movement.c](src/movement.c), [src/validator.c](src/validator.c), [src/infected_map.c](src/infected_map.c), [src/image.c](src/image.c), [src/utils.c](src/utils.c)
- [include/](include/) — project headers and vendored SDL headers
  - Project API: [include/and_goodbye.h](include/and_goodbye.h)
- [img/](img/) — XPM sprites
- [maps/](maps/) — sample maps (*.ber)
- [lib/](lib/) and [bin/](bin/) — Windows SDL2 binaries

## Build

Prerequisites:
- Linux/macOS: SDL2 + SDL2_image development packages
  - Debian/Ubuntu: `sudo apt install libsdl2-dev libsdl2-image-dev`
  - Fedora: `sudo dnf install SDL2-devel SDL2_image-devel`
  - macOS (Homebrew): `brew install sdl2 sdl2_image`
- Windows: MinGW-w64 (or MSYS2/mingw), uses bundled DLLs in [lib/](lib/) and [bin/](bin/)

Commands:
- Build (release): `make`
- Build (debug): `make debug`
- Clean objects: `make clean`

The output binary is `and_goodbye` (Linux/macOS) or `and_goodbye.exe` (Windows).

## Run

- Linux/macOS:
  - `./and_goodbye maps/map.ber`
- Windows:
  - `and_goodbye.exe maps\map.ber`
  - Ensure `SDL2.dll` and `SDL2_image.dll` are on PATH or next to the executable (see [bin/](bin/)).

## Usage

- The game expects a `.ber` map file path as the first argument.
- Close the window or use the platform’s standard close action to quit.
- Keyboard handling is implemented in [src/movement.c](src/movement.c).

## Maps

- Sample maps are in [maps/](maps/).
- Maps must be:
  - Non-empty and rectangular — enforced in [src/validator.c](src/validator.c)
  - Fully surrounded by walls (`1`) — see walls checks in [src/validator.c](src/validator.c)
- Loading flow:
  - [`render_map`](src/render.c) reads the file, accumulates text, and splits lines via [`split_string`](src/split_string.c), using buffered reads from [`keep_reading_fd`](src/read_fd.c).
- Tile size is defined by [`IMG_SIZE`](include/and_goodbye.h) (currently 32).

## Troubleshooting

- "ERROR: FILE NOT FOUND" — the provided map path is wrong or unreadable.
- "ERROR: EMPTY MAP" — the file has no content.
- "Error\nMAP SHOULD BE A RECTANGLE" — inconsistent line lengths.
- "Error\nMAP MUST BE SURROUNDED BY WALLS 1" — outer border is not walls.

On Linux/macOS, missing libraries at link/runtime usually means SDL2/SDL2_image dev/runtime packages aren’t installed.

## Notes

- Assets are XPM files referenced in [include/and_goodbye.h](include/and_goodbye.h) (e.g., character and environment sprites under [img/](img/)).
- Windows build uses `-I\include\SDL2 -L\lib` from the [Makefile](Makefile) and links `-lmingw32 -lSDL2main -lSDL2 -lSDL2_image`.

## License

This project depends on SDL2 and SDL2_image; see their respective licenses in the SDL distributions. Project source and assets are provided for educational