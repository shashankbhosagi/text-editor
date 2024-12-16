# Line-Based Text Editor

This is a simple line-based text editor implemented in C. It allows users to read a text file, modify its content through various commands, and save changes back to the file. The editor supports commands for printing, appending, editing, inserting, deleting, and saving lines.

---

## Features
- **Print**: View the current contents of the file.
- **Append**: Add a new line at the end of the file.
- **Edit**: Modify an existing line.
- **Insert**: Insert a new line at a specific position.
- **Delete**: Remove a specific line.
- **Save**: Save changes back to the file.
- **Help**: Display a list of available commands.
- **Exit**: Exit the editor (without auto-saving).

---

## Requirements
- GCC or any other C compiler.
- A text file to work with.
- Supported on Linux or Unix-like systems.

---

## Compilation
To compile the program, use the following command:
```bash
gcc -o main main.c
```

This will create an executable file named `line_editor`.

---

## Running the Editor
Run the editor by specifying the name of the text file as an argument:
```bash
./main <filename>
```

### Example:
```bash
./main sample.txt
```

If the specified file does not exist, you will need to create it first.

---

## Commands

| Command       | Alias   | Description                                                                 |
|---------------|---------|-----------------------------------------------------------------------------|
| `p`           | `print` | Prints the current contents of the file with line numbers.                 |
| `a`           | `append`| Appends a new line to the end of the file.                                  |
| `e`           | `edit`  | Edits an existing line. Requires a line number and new content.             |
| `i`           | `insert`| Inserts a new line at a specific position. Requires a line number.          |
| `d`           | `delete`| Deletes a specific line. Requires a line number.                            |
| `w`           | `write` | Saves the buffer content to the file.                                      |
| `h`           | `help`  | Displays a list of available commands and their descriptions.               |
| `exit`        | -       | Exits the editor without saving changes automatically.                      |

---

## Usage
### 1. Print the File
```bash
Command: p
```
This displays the file's content with line numbers.

### 2. Append a Line
```bash
Command: a
 This is a new line (Enter the line to append)
```
This adds a new line to the end of the file.

### 3. Edit a Line
```bash
Command: e
2 (Enter the line number)
Current content is shown
Updated line content(Enter the new content)
```
This modifies the specified line with the new content.

### 4. Insert a Line
```bash
Command: i
3 (Enter the line number)
Inserted line content (Enter the new content)
```
This inserts a new line at the specified position, shifting subsequent lines down.

### 5. Delete a Line
```bash
Command: d
1 (Enter the line number)
```
This removes the specified line from the file.

### 6. Save the File 
```bash
Command: w
```
This writes the current buffer content back to the file.

### 7. Display Help
```bash
Command: h
```
This shows a list of all available commands.

### 8. Exit the Editor
```bash
Command: exit
```
This exits the editor <b>without</b> saving the buffer to the file automatically.

---

## Notes
- Line numbers in commands start from 0.
- The maximum number of lines is **100**.
- The maximum line length is **1024 characters**.
- Commands are case-sensitive.
- Before exiting save using `w` command

---

## Error Handling
- If a line exceeds the maximum length or the number of lines exceeds the limit, the program will terminate with an error message.
- Invalid commands or line numbers will display appropriate warnings.

---

## License
This project is open-source. Feel free to use and modify as needed.

