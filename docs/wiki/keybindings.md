# Keybindings

Bindings are layered over Vim-like defaults and support key chords.

```toml
[[manager.bind]]
keys = ["g", "d"]
action = "cd"
arg = "~/Downloads"
description = "Go to Downloads"
```

Common actions include `down`, `up`, `parent`, `open`, `copy`, `cut`, `paste`, `trash`, `delete`, `rename`, `create_file`, `create_directory`, `select`, `visual`, `find`, `new_tab`, `close_tab`, `back`, `forward`, `home`, `cd`, and `reload`.

The `?` overlay is generated from the active keymap rather than hardcoded text.
