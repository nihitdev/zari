# File operations and safety

Operations use the selected paths, or the cursor item when no selection exists.

- `y`, `x`, `p`: copy, cut, and paste
- `r`: rename
- `a`, `A`: create a file or directory
- `d`: move to freedesktop trash
- `D`: permanently delete after confirmation

Paste never silently overwrites. Conflicts receive numbered sibling names. Symlinks are copied as symlinks, and filesystem paths are not interpolated into shell commands.
