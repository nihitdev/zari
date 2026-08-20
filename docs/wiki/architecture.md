# Architecture

- `App`: input loop, application modes, and action dispatch
- `Ui` / `Terminal`: ncurses rendering and RAII terminal lifetime
- `Manager`: tabs, clipboard, configuration, and tasks
- `Tab`: directory state, selection, cursor, and history
- `filesystem`: metadata, sorting, copy/move/remove, and trash
- `config`, `keymap`, `theme`: validated customization
- `preview`, `search`, `task`: focused supporting services

Zari avoids global mutable state, raw owning pointers, plugin runtimes, and shell interpolation for filesystem operations.
