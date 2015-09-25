# QxtGlobalShortcut
Extracted from libqxt.

History and initial file structure is preserved to make possible cherry-picking potential changes from libqxt.
Everything not required for `QxtGlobalShortcut` to work is removed.
For more info on the original `libqxt` project check out their repo on Bitbucket: https://bitbucket.org/libqxt/libqxt

## Usage

This project is designed for static linking.

1. Add source code to your project.

  I recommend using git submodules unless you have a better option.

2. Enable `QxtGlobalShortcut` by importing provided `.pri` file:

  In your `.pro` file add:

  ```qmake
  # Adding QxtGlobalShortcut
  include(path/to/QxtGlobalShortcut/QxtGlobalShortcut.pri)
  ```

3. Include `"qxtglobalshortcut.h"` and use `QxtGlobalShortcut` class:

  ```cpp
  #include "qxtglobalshortcut.h"

  ...

  QxtGlobalShortcut myShortcut(QKeySequence("Shift+F1"));
  QObject::connect(&myShortcut, SIGNAL(activated()), something, SLOT(shortcutActivated()));
  ```

For a more complete usage example see `examples` dir.
