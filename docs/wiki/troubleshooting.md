# Troubleshooting

## Garbled interface

Use a UTF-8 locale and ensure `$TERM` accurately identifies the terminal.

## Curses is missing

On Debian or Ubuntu, install `libncursesw5-dev`. On Arch Linux, install `ncurses`.

## Configuration warning

Correct the indicated line and press `R`. Invalid values fall back safely.

## Files do not open

Ensure `xdg-open` is installed and a desktop application is registered for the file type.
