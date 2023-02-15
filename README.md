1.TOUCH FUNCTION 

    --> in case that the tree is empty, I used create_file function which create a file only with initialized name(in case that the tree wasn’t empty, I go through the       whole tree and add an element to the tree, taking into account the lexicographic order. In plus, if exists a directory with the same name as the new file we want to     add, we return the message “DIRECTORY ALREADY EXISTS”(I used the check2 function which verify if a certain directory already exists in the tree and if it does,           return 1);

2.MKDIR FUNCTION 

    --> I made a function which create a root tree just with the initialized name.Also, I made a function that keep directory’s parent too.
        as with the touch function, if it’s empty ->add a new directory and if it’s not->I go through subdirectory tree and insert the new directory. If exists a file           with the same name, I return the message “FILE ALREADY EXISTS!”(I used the file_exists function);

3.LS FUNCTION

    --> I used Inorder Traversal both for directories and subdirectories.

4.RM FUNCTION 

    --> delete_file function search a file which we want to delete recursively(Function return the new tree);

5.RMDIR FUNCTON

    --> delete_dir function search a directory which we want to delete recursiverly(function return the new tree);

6.CD FUNCTION 

    --> I used find function which search a directory and returns it. If we found the directory, we move on it(root becomes that directory and its kept in root->parinte        and when we use cd .. command, we return at initial directory.


