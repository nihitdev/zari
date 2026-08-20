# Configuration

Zari reads `$ZARI_CONFIG_HOME`, `$XDG_CONFIG_HOME/zari`, or `~/.config/zari`, in that order. The directory may contain `zari.toml`, `keymap.toml`, and `theme.toml`. Missing files use built-in defaults.

```toml
[manager]
show_hidden = false
sort_by = "natural"
directories_first = true
layout = [1, 3, 2]

[preview]
enabled = true
max_file_size = 10485760
tab_size = 4
```

Press `R` to reload. A malformed main configuration is rejected while the last working configuration stays active.
