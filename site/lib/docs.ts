export type DocSection = { title: string; paragraphs?: string[]; code?: string; bullets?: string[] };
export type Doc = { slug: string; title: string; summary: string; sections: DocSection[] };

export const docs: Doc[] = [
  { slug:"getting-started", title:"Getting started", summary:"Install dependencies, build Zari, and learn the essential controls.", sections:[
    {title:"Requirements",bullets:["Linux with a UTF-8 locale","CMake 3.20 or newer","A C++20 compiler such as GCC or Clang","ncursesw development headers"]},
    {title:"Install a release",paragraphs:["The installer downloads the correct Linux archive, verifies its SHA-256 checksum, and installs into ~/.local without sudo."],code:"curl -fsSL https://raw.githubusercontent.com/nihitdev/zari/main/install.sh | sh"},
    {title:"Debian and Ubuntu",paragraphs:["Download the package for your architecture from GitHub Releases, then let APT install its runtime dependencies."],code:"sudo apt install ./zari_0.1.0_amd64.deb"},
    {title:"Arch Linux",paragraphs:["Once the submitted AUR package is available, install it with your preferred AUR helper."],code:"yay -S zari"},
    {title:"Build from source",code:"git clone https://github.com/nihitdev/zari.git\ncd zari\ncmake -S . -B build -DCMAKE_BUILD_TYPE=Release\ncmake --build build\nctest --test-dir build --output-on-failure\n./build/zari"},
    {title:"Open a location",paragraphs:["Run Zari without an argument to open the current working directory, or pass a path directly."],code:"zari\nzari .\nzari ~/Projects\nzari /mnt/storage"},
    {title:"First five keys",bullets:["j / k — move down and up","h / l — leave or enter a directory","Space — select an item","? — show the live keybinding reference","q — quit and restore the terminal"]}
  ]},
  { slug:"configuration", title:"Configuration", summary:"Understand configuration paths, validation, layering, and runtime reload.", sections:[
    {title:"Where files live",paragraphs:["Zari checks ZARI_CONFIG_HOME first, then $XDG_CONFIG_HOME/zari, then ~/.config/zari. Every file is optional; built-in defaults are always available."],code:"~/.config/zari/\n├── zari.toml\n├── keymap.toml\n└── theme.toml"},
    {title:"Manager and preview",code:"[manager]\nshow_hidden = false\nsort_by = \"natural\"\nsort_reverse = false\ndirectories_first = true\nlayout = [1, 3, 2]\n\n[preview]\nenabled = true\nmax_file_size = 10485760\ntab_size = 4\nline_numbers = true"},
    {title:"Safe reload",paragraphs:["Press R to reload all three files. If the main configuration is malformed, Zari keeps the last working configuration and shows a warning instead of leaving the application in a partial state."]}
  ]},
  { slug:"keybindings", title:"Keybindings", summary:"Remap actions, define multi-key chords, and create directory bookmarks.", sections:[
    {title:"Binding format",code:"[[manager.bind]]\nkeys = [\"g\", \"d\"]\naction = \"cd\"\narg = \"~/Downloads\"\ndescription = \"Go to Downloads\""},
    {title:"Core actions",bullets:["Movement: down, up, parent, open, top, bottom, half_up, half_down","Files: copy, cut, paste, trash, delete, rename, create_file, create_directory","State: select, visual, hidden, find, reload","Tabs: new_tab, close_tab, previous_tab, next_tab, tab","Navigation: home, back, forward, cd"]},
    {title:"How overrides work",paragraphs:["A custom binding replaces the default binding with the same key sequence. All other defaults remain active. The help overlay is generated from the resulting keymap."]}
  ]},
  { slug:"themes", title:"Themes", summary:"Choose a preset or customize individual interface elements.", sections:[
    {title:"Built-in presets",bullets:["default","catppuccin-mocha","gruvbox-dark","dracula","nord","tokyo-night"]},
    {title:"Select and override",code:"# zari.toml\n[theme]\nname = \"catppuccin-mocha\"\n\n# theme.toml\n[manager]\ndirectory = { fg = \"#89b4fa\", bold = true }\nselected = { fg = \"#11111b\", bg = \"#cba6f7\", bold = true }"},
    {title:"Style properties",paragraphs:["Colors accept #RRGGBB values or ANSI names. Styles can independently enable bold, italic, underline, and dim. Terminals may approximate RGB colors depending on their capabilities."]}
  ]},
  { slug:"file-operations", title:"File operations", summary:"Copy, move, rename, trash, and delete files deliberately and safely.", sections:[
    {title:"Selection and clipboard",paragraphs:["Press Space to toggle individual items or v to enter visual selection. Operations apply to the current selection, falling back to the cursor item when nothing is selected."],bullets:["y — stage paths for copying","x — stage paths for moving","p — paste into the current directory","r — rename the current item"]},
    {title:"Collision behavior",paragraphs:["Paste never silently overwrites a destination. If a name already exists, Zari creates a numbered sibling name. Symlinks are copied as symlinks rather than followed recursively."]},
    {title:"Trash and deletion",paragraphs:["d moves items to ~/.local/share/Trash and writes freedesktop trash metadata. D permanently removes selected paths after confirmation. Permanent deletion cannot be undone."]}
  ]},
  { slug:"architecture", title:"Architecture", summary:"A tour of the focused C++ modules and their ownership boundaries.", sections:[
    {title:"Core model",bullets:["App — CLI state, input loop, modes, and action dispatch","Ui and Terminal — ncurses rendering and RAII terminal lifecycle","Manager — tabs, clipboard, configuration, and task coordination","Tab — directory listing, cursor, selection, and navigation history"]},
    {title:"Focused services",bullets:["filesystem — metadata, sorting, copy/move/remove, and trash","config, keymap, theme — validated user customization","preview — safe text, directory, binary, and metadata previews","search — fuzzy matching and recursive filename traversal","task — owned worker threads with progress and cancellation state"]},
    {title:"Design constraints",paragraphs:["Zari uses no global mutable application state, raw owning pointers, plugin runtime, or shell interpolation for filesystem operations. The project deliberately favors direct C++ and POSIX APIs."]}
  ]},
  { slug:"troubleshooting", title:"Troubleshooting", summary:"Fix common terminal, build, configuration, and opener problems.", sections:[
    {title:"The interface looks garbled",paragraphs:["Confirm that the locale is UTF-8 and TERM identifies the terminal correctly. Zari uses ncursesw for wide-character rendering."]},
    {title:"CMake cannot find curses",code:"# Debian / Ubuntu\nsudo apt install libncursesw5-dev\n\n# Arch Linux\nsudo pacman -S ncurses"},
    {title:"A configuration warning appears",paragraphs:["Read the line number in the status message, correct that file, and press R. Unknown or invalid values fall back safely rather than crashing."]},
    {title:"A file will not open",paragraphs:["Zari invokes xdg-open as an argument vector. Ensure it is installed and that your desktop has a default application registered for the file type."]}
  ]}
];

export const getDoc = (slug: string) => docs.find((doc) => doc.slug === slug);
