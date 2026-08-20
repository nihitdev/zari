# Themes

Built-in themes are `default`, `catppuccin-mocha`, `gruvbox-dark`, `dracula`, `nord`, and `tokyo-night`.

```toml
# zari.toml
[theme]
name = "nord"

# theme.toml
[manager]
directory = { fg = "#81a1c1", bold = true }
selected = { fg = "#2e3440", bg = "#88c0d0", bold = true }
```

Colors accept `#RRGGBB` or ANSI names. Styles support bold, italic, underline, and dim.
