
## Functionality Overview

This project provides a comprehensive file system management toolset. Below is an overview of the key functions implemented:

### 1. Touch Function

- **Description:** 
  - If the tree is empty, the `create_file` function initializes a file with the specified name. 
  - If the tree isn't empty, the function adds an element to the tree while maintaining lexicographic order. 
  - If a directory with the same name as the new file exists, the message "DIRECTORY ALREADY EXISTS" is returned.

### 2. Mkdir Function

- **Description:**
  - The `mkdir` function creates a root tree with the initialized name. 
  - It also maintains the parent directory.
  - Similar to the `touch` function, if the directory is empty, it adds a new directory. 
  - If not, it traverses the subdirectory tree and inserts the new directory. 
  - If a file with the same name exists, the message "FILE ALREADY EXISTS!" is returned.

### 3. Ls Function

- **Description:** 
  - Utilizes Inorder Traversal for both directories and subdirectories to list the contents.

### 4. Rm Function

- **Description:** 
  - The `delete_file` function recursively searches for the file to delete and returns the new tree.

### 5. Rmdir Function

- **Description:** 
  - The `delete_dir` function recursively searches for the directory to delete and returns the new tree.

### 6. Cd Function

- **Description:** 
  - Utilizes the `find` function to search for a directory and returns it. 
  - When a directory is found, the root becomes that directory, and its parent is stored in `root->parinte`. 
  - Using the `cd ..` command returns to the initial directory.

## Markdown Code

```markdown
Paste your Markdown code here
