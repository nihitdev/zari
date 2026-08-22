export type DocSection = { title: string; paragraphs?: string[]; code?: string; bullets?: string[] };
export type Doc = { slug: string; title: string; summary: string; sections: DocSection[] };

export const docs: Doc[] = [
  { slug:"getting-started", title:"Getting started", summary:"Launch Zari, understand the interface, and learn the essential controls.", sections:[
    {title:"Before you begin",paragraphs:["Zari targets Linux and requires a UTF-8 locale and a terminal supported by ncursesw. Version 0.1 is under active development, so test destructive operations on non-critical data when evaluating a release."]},
    {title:"Create your configuration",paragraphs:["Run zari init once to create zari.toml, keymap.toml, and theme.toml in the active config directory. Existing files are kept unchanged."],code:"zari init"},
    {title:"Open a location",paragraphs:["Run Zari without an argument to open the current working directory, or pass a path directly."],code:"zari\nzari .\nzari ~/Projects\nzari /mnt/storage"},
    {title:"The three panes",bullets:["Parent — context from the directory above","Current — the active directory and cursor","Preview — text, directory contents, symlink details, or file metadata"]},
    {title:"Going back",paragraphs:["Press h to move to the parent directory. Press b to return to the previous directory in navigation history, and B to move forward again. If a regular file opened in another terminal application, quit that application first to return to Zari."],code:"h       parent directory\nb       back in history\nB       forward in history"},
    {title:"First five keys",bullets:["j / k — move down and up","h / l — leave or enter a directory","Space — select an item","? — show the live keybinding reference","q — quit and restore the terminal"]},
    {title:"Command-line options",code:"zari --help\nzari --version\nzari --config /path/to/zari.toml\nzari --theme catppuccin-mocha\nzari --debug"}
  ]},
  { slug:"installation", title:"Installation", summary:"Install a verified release, distribution package, or source build.", sections:[
    {title:"Release installer",paragraphs:["The installer selects the current architecture, downloads a GitHub release, verifies its SHA-256 checksum, and installs into ~/.local without sudo."],code:"curl -fsSL https://raw.githubusercontent.com/nihitdev/zari/main/install.sh | sh"},
    {title:"Debian and Ubuntu",paragraphs:["Download the .deb matching your architecture from GitHub Releases, then use APT so runtime dependencies are resolved."],code:"sudo apt install ./zari_0.1.1_amd64.deb"},
    {title:"Arch signed binary repository — trust key",paragraphs:["Verify the fingerprint before locally trusting the repository key: B387 DD74 A008 7C2D 0C96 F7C5 0FF0 CC0A C49F 9149."],code:"curl -fsSL https://raw.githubusercontent.com/nihitdev/zari-arch-repo/main/zari.gpg | sudo pacman-key --add -\nsudo pacman-key --lsign-key B387DD74A0087C2D0C96F7C50FF0CC0AC49F9149"},
    {title:"Arch signed binary repository — configure",paragraphs:["Add the repository block to /etc/pacman.conf, then synchronize and install."],code:"[zari]\nSigLevel = Required DatabaseOptional\nServer = https://raw.githubusercontent.com/nihitdev/zari-arch-repo/main/$arch\n\nsudo pacman -Syu zari"},
    {title:"Arch User Repository",paragraphs:["The zari package is also available from AUR."],code:"yay -S zari\n# or\nparu -S zari"},
    {title:"Build requirements",bullets:["Linux with a UTF-8 locale","CMake 3.20 or newer","A C++20 compiler such as GCC or Clang","ncursesw development headers"]},
    {title:"Build from source",code:"git clone https://github.com/nihitdev/zari.git\ncd zari\ncmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON\ncmake --build build\nctest --test-dir build --output-on-failure\n./build/zari"}
  ]},
  { slug:"configuration", title:"Configuration", summary:"Understand configuration paths, validation, layering, and runtime reload.", sections:[
    {title:"Where files live",paragraphs:["Zari checks ZARI_CONFIG_HOME first, then $XDG_CONFIG_HOME/zari, then ~/.config/zari. Every file is optional; built-in defaults are always available."],code:"~/.config/zari/\n├── zari.toml\n├── keymap.toml\n└── theme.toml"},
    {title:"Generate starter files",paragraphs:["zari init creates the config directory and all three starter files. It is safe to run again: files that already exist are reported and left untouched. ZARI_CONFIG_HOME and XDG_CONFIG_HOME are respected."],code:"zari init\n\n# Generate files somewhere else\nZARI_CONFIG_HOME=/some/path zari init"},
    {title:"Manager and preview",code:"[manager]\nshow_hidden = false\nsort_by = \"natural\"\nsort_reverse = false\ndirectories_first = true\nlayout = [1, 3, 2]\n\n[preview]\nenabled = true\nmax_file_size = 10485760\ntab_size = 4\nline_numbers = true"},
    {title:"Safe reload",paragraphs:["Press R to reload all three files. If the main configuration is malformed, Zari keeps the last working configuration and shows a warning instead of leaving the application in a partial state."]}
  ]},
  { slug:"keybindings", title:"Keybindings", summary:"Remap actions, define multi-key chords, and create directory bookmarks.", sections:[
    {title:"Default navigation",bullets:["j / k or arrows — move down / up","h / l — parent directory / enter or open","gg / G — jump to top / bottom","Ctrl-u / Ctrl-d — half-page up / down","b / B — back / forward history","~ — home directory"]},
    {title:"Default file actions",bullets:["Space / v — toggle selection / visual mode","y / x / p — copy / cut / paste","d / D — trash / permanent deletion","r — rename","a / A — create file / directory",". — toggle hidden files"]},
    {title:"Optional-tool actions",bullets:["z — choose a descendant directory with fzf (fd accelerates collection)","Z — choose a historical directory with zoxide and fzf","cp — copy selected absolute paths with wl-clipboard, xclip, or xsel","S — search file contents with rg"]},
    {title:"Tabs and application",bullets:["tt — create tab","[ / ] — previous / next tab","1–9 — switch directly to a tab","Ctrl-w — close tab","R — reload configuration","? / q — help / quit"]},
    {title:"Binding format",code:"[[manager.bind]]\nkeys = [\"g\", \"d\"]\naction = \"cd\"\narg = \"~/Downloads\"\ndescription = \"Go to Downloads\""},
    {title:"Core actions",bullets:["Movement: down, up, parent, open, top, bottom, half_up, half_down","Files: copy, cut, paste, trash, delete, rename, create_file, create_directory","State: select, visual, hidden, find, reload","Tabs: new_tab, close_tab, previous_tab, next_tab, tab","Navigation: home, back, forward, cd"]},
    {title:"How overrides work",paragraphs:["A custom binding replaces the default binding with the same key sequence. All other defaults remain active. The help overlay is generated from the resulting keymap."]}
  ]},
  { slug:"themes", title:"Themes", summary:"Choose a preset or customize individual interface elements.", sections:[
    {title:"Built-in presets",bullets:["default","catppuccin-mocha","gruvbox-dark","dracula","nord","tokyo-night"]},
    {title:"Select and override",code:"# zari.toml\n[theme]\nname = \"catppuccin-mocha\"\n\n# theme.toml\n[manager]\ndirectory = { fg = \"#89b4fa\", bold = true }\nselected = { fg = \"#11111b\", bg = \"#cba6f7\", bold = true }"},
    {title:"Style properties",paragraphs:["Colors accept #RRGGBB values or ANSI names. Styles can independently enable bold, italic, underline, and dim. Terminals may approximate RGB colors depending on their capabilities."]}
  ]},
  { slug:"optional-tools", title:"Optional tools", summary:"Enable richer search, previews, icons, and desktop integration without making them hard dependencies.", sections:[
    {title:"How optional integration works",paragraphs:["Zari starts and remains usable without any tool on this page. Executables are detected through PATH and launched with argument vectors rather than shell command strings. If a tool is missing or fails, Zari falls back to its native preview or reports a concise message."]},
    {title:"Supported now",bullets:["Nerd Fonts — optional file icons; set ui.nerd_fonts = true","fd — accelerates recursive filename search and fzf subtree collection; native traversal remains the fallback","rg / ripgrep — powers S content search","fzf — interactive subtree selection with z","zoxide with fzf — historical directory selection with Z","wl-clipboard, xclip, or xsel — copies selected paths to the Linux system clipboard with cp","jq — formatted JSON previews","poppler / pdftotext — text previews for the first PDF pages","7-Zip / 7z — archive listing previews","FFmpeg / ffprobe — video and audio stream metadata","ImageMagick / magick — metadata for images, fonts, HEIC, and JPEG XL files","resvg — detected for SVG-capable environments; pixel display still needs a terminal image protocol"]},
    {title:"Nerd Font icons",paragraphs:["Install a Nerd Font, configure the terminal to use it, then enable the option below. Plain fallback icons remain the default so Zari never requires a patched font."],code:"[ui]\nshow_file_icons = true\nnerd_fonts = true"},
    {title:"Image and video limits",paragraphs:["Zari can show FFmpeg and ImageMagick metadata today. Actual image and video thumbnails require a supported terminal image protocol in addition to resvg, ImageMagick, or FFmpeg; ncurses alone cannot draw those pixels. Pixel rendering remains tracked integration work and is not advertised as active in version 0.1.1."]},
    {title:"Common package names",code:"# Arch Linux\nsudo pacman -S --needed nerd-fonts ffmpeg 7zip jq poppler fd ripgrep fzf zoxide resvg imagemagick wl-clipboard\n\n# Names vary on other distributions. Choose one Linux clipboard helper:\n# wl-clipboard (Wayland), xclip, or xsel (X11)."}
  ]},
  { slug:"file-operations", title:"File operations", summary:"Copy, move, rename, trash, and delete files deliberately and safely.", sections:[
    {title:"Selection and clipboard",paragraphs:["Press Space to toggle individual items or v to enter visual selection. Operations apply to the current selection, falling back to the cursor item when nothing is selected."],bullets:["y — stage paths for copying","x — stage paths for moving","p — paste into the current directory","r — rename the current item"]},
    {title:"Collision behavior",paragraphs:["Paste never silently overwrites a destination. If a name already exists, Zari creates a numbered sibling name. Symlinks are copied as symlinks rather than followed recursively."]},
    {title:"Trash and deletion",paragraphs:["d moves items to ~/.local/share/Trash and writes freedesktop trash metadata. D permanently removes selected paths after confirmation. Permanent deletion cannot be undone."]}
  ]},
  { slug:"architecture", title:"Architecture", summary:"A tour of the focused C++ modules and their ownership boundaries.", sections:[
    {title:"Core model",bullets:["App — CLI state, input loop, modes, and action dispatch","Ui and Terminal — ncurses rendering and RAII terminal lifecycle","Manager — tabs, clipboard, configuration, and task coordination","Tab — directory listing, cursor, selection, and navigation history"]},
    {title:"Focused services",bullets:["filesystem — metadata, sorting, copy/move/remove, and trash","config, keymap, theme — validated user customization","preview — safe text, directory, binary, and metadata previews","search — fuzzy matching and recursive filename traversal","task — owned worker threads with progress and cancellation state"]},
    {title:"Repository layout",code:"include/zari/   Module interfaces\nsrc/            Implementations\ntests/          Non-TUI tests\nthemes/         Built-in presets\npackaging/      Debian and Arch metadata\ndocs/wiki/      Repository wiki\nsite/           Next.js documentation site"},
    {title:"Design constraints",paragraphs:["Zari uses no global mutable application state, raw owning pointers, plugin runtime, or shell interpolation for filesystem operations. The project deliberately favors direct C++ and POSIX APIs."]}
  ]},
  { slug:"development", title:"Development", summary:"Build, test, contribute, and understand the current roadmap.", sections:[
    {title:"Warning-enabled test build",code:"cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON\ncmake --build build\nctest --test-dir build --output-on-failure"},
    {title:"Contribution checklist",bullets:["Keep implementation native C++20; Zari intentionally has no plugin or scripting runtime","Preserve safe behavior for spaces, Unicode names, leading dashes, symlinks, and recursion","Build with -Wall -Wextra -Wpedantic and run the complete test suite","Update documentation when behavior, keybindings, configuration, or packaging changes"]},
    {title:"Where tests matter most",paragraphs:["Keep UI-independent behavior in testable modules. Add regression coverage for configuration, sorting, path handling, selection, tabs, search, and filesystem operations."]},
    {title:"Roadmap",bullets:["Search-result views and rg content-search integration","Cancellable progress dialogs for long-running operations","Bulk rename and an open-with rules interface","Optional terminal image protocols","Syntax-highlighted source previews","Additional metadata columns and UI polish"]},
    {title:"Project links",bullets:["Source and issues — github.com/nihitdev/zari","Releases — github.com/nihitdev/zari/releases","AUR — aur.archlinux.org/packages/zari","License — GPL-3.0-or-later"]}
  ]},
  { slug:"troubleshooting", title:"Troubleshooting", summary:"Fix common terminal, build, configuration, and opener problems.", sections:[
    {title:"The interface looks garbled",paragraphs:["Confirm that the locale is UTF-8 and TERM identifies the terminal correctly. Zari uses ncursesw for wide-character rendering."]},
    {title:"CMake cannot find curses",code:"# Debian / Ubuntu\nsudo apt install libncursesw5-dev\n\n# Arch Linux\nsudo pacman -S ncurses"},
    {title:"A configuration warning appears",paragraphs:["Read the line number in the status message, correct that file, and press R. Unknown or invalid values fall back safely rather than crashing."]},
    {title:"A file will not open",paragraphs:["Zari invokes xdg-open as an argument vector. Ensure it is installed and that your desktop has a default application registered for the file type."]}
  ]}
];

export const getDoc = (slug: string) => docs.find((doc) => doc.slug === slug);
