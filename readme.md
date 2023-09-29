# Terminal UI Library (tui.h)

![GitHub](https://img.shields.io/github/license/dleiferives/tui)

tui.h is a minimal C library for creating terminal-based applications. This library simplifies terminal application development by providing basic functionality for terminal manipulation. It relies on `term.h`, which uses `terminfo` and therefore the  `ncurses` library for terminal handling.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [TODO](#todo)
- [Contributing](#contributing)
- [License](#license)

## Installation

To use tui.h in your C project, follow these steps:

1. Clone this repository to your local machine.

   ```bash
   git clone https://github.com/dleiferives/tui.git
   ```

2. Include the `tui.h` header in your C code.

   ```c
   #include "tui.h"
   ```

3. Compile your C program with the `tinfo` library.

   ```bash
   gcc -o myprogram myprogram.c -ltinfo
   ```

## Usage

Here's a basic example of how to use the `tui.h` library in your C program:

```c
#include <stdio.h>
#include "tui.h"

int main() {
    // Initialize the terminal
    Terminal_t term = Terminal_t_init();
    Terminal_t_create(&term);

    // Make the cursor invisible
    Terminal_t_cursor_invis(&term);

    // Move the cursor to position (5, 10)
    Terminal_t_move_cursor(&term, 5, 10);

    // Repeat the character 'X' 3 times
    Terminal_t_repeat_char(&term, 'X', 3);

    // Delete 2 lines
    Terminal_t_delete_lines(&term, 2);

    // Clear to the end of the line
    Terminal_t_clear_to_l_end(&term);

    // Clear to the end of the screen
    Terminal_t_clear_to_screen_end(&term);

    // Destroy the terminal and reset cursor
    Terminal_t_destroy();

    return 0;
}
```

## Functions

- `Terminal_t Terminal_t_init(void)`: Initializes a zeroed terminal structure.
- `void Terminal_t_create(Terminal_t *t)`: Sets up the terminal, retrieves terminal dimensions, and prepares cursor handling.
- `void Terminal_t_destroy()`: Closes the terminal and resets the cursor.
- `void Terminal_t_cursor_invis(void)`: Makes the cursor invisible.
- `void Terminal_t_move_cursor(Terminal_t *t, unsigned short x, unsigned y)`: Moves the cursor to the specified position.
- `void Terminal_t_repeat_char(Terminal_t *t, char c, int n)`: Repeats a character `n` times at the current cursor position.
- `void Terminal_t_delete_lines(Terminal_t *t, int n)`: Deletes `n` lines (currently not fully implemented).
- `void Terminal_t_clear_to_screen_end(Terminal_t *t)`: Clears from the cursor position to the end of the screen.
- `void Terminal_t_clear_to_l_end(Terminal_t *t)`: Clears from the cursor position to the end of the current line.

## TODO

- Reimplement functions using ASCII escape sequences.
- Reduce dependencies on `ncurses` and retrieve information directly from the terminal or SSH connection.
- Handle errors gracefully if they occur.

## Contributing

Contributions are welcome! If you have suggestions, bug reports, or would like to contribute code, please feel free to open an issue or create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
