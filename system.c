
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LEN 50

typedef struct director {
    char *nume; //directory name
    struct director *parinte; //pointer to parent directory
    struct director *directories; //pointer to the root of the subdirectory tree
    struct director *st; //pointer to next dir < than it
    struct director *dr; //pointer to next dir > than it
    struct fisier  *files; //pointer to the root of the file tree
}Directory;

typedef struct fisier {
    char* nume; //file name
    struct fisier* st; //pointer to next file < than it
    struct fisier* dr; //pointer to urm file > than it
    Directory* parinte; //pointer to directory's parent
}File;

//function which allocate a root directory 
Directory* create_root(char* numedir) {
    Directory* dir = (Directory*)calloc(1, sizeof(Directory));
    assert(dir);
    dir->nume = (char*)malloc(MAX_LEN*sizeof(char));
    assert(dir->nume);
    strcpy(dir->nume, numedir);
    dir->directories = NULL;
    dir->parinte = NULL;
    dir->st = NULL;
    dir->st = NULL;
    dir->files = NULL;
    return dir;
}

//function that allocate a directory to have a parent
Directory* create_directory(char* numedir, Directory* parinte) {
    Directory* dir = (Directory*)malloc(sizeof(Directory));
    assert(dir);
    dir->nume = (char*)malloc(50);
    assert(dir->nume);
    strcpy(dir->nume, numedir);
    dir->directories = NULL;
    dir->parinte = (Directory*)calloc(1, sizeof(Directory));
    assert(dir->parinte);
    dir->parinte = parinte;
    dir->st = NULL;
    dir->st = NULL;
    dir->files = NULL;
    return dir;
}

//function that allocate memory for a file
File* create_file(char* nume_dir, Directory* parinte) {
    File* fisier = (File*)calloc(1, sizeof(File));
    assert(fisier);
    fisier->nume = (char*)malloc(MAX_LEN);
    assert(fisier->nume);
    strcpy(fisier->nume, nume_dir);
    fisier->dr = NULL;
    fisier->st = NULL;
    fisier->parinte = (Directory*)calloc(1, sizeof(Directory));
    assert(fisier->parinte);
    fisier->parinte = parinte;
    return fisier;
}

//function that checks if a certain file exists
bool file_exists(File* a, char* nume) {
    if(a == NULL)  
        return false;
    if(strcmp(nume, a->nume) == 0) 
        return true;
    bool res1 = file_exists(a->st, nume);
    if(res1)
        return true;
    bool res2 = file_exists(a->dr, nume);

    return res2;
}

//function that checks if a certain directory exists.
bool check2(Directory* a, char* nume) {
    if(a == NULL)
        return false;
    if(strcmp(nume, a->nume) == 0) 
        return true;
    bool res1 = check2(a->st, nume);
    if(res1)
        return true;
    bool res2 = check2(a->dr, nume);

    return res2;
}

//function that find a directory and return it
Directory* find(Directory* a, char* nume) {
    if(a == NULL)
        return NULL;
    if(strcmp(nume, a->nume) == 0) 
        return a;
    Directory* res1 = find(a->st, nume);
    if(res1)
        return a;
    Directory* res2 = find(a->dr, nume);
        return res2;
}

//function that creates a file
int touch_file(File** fisier, char* nume_file, Directory* director) {
    File* new = NULL;
    File* aux = NULL;
    File* p = NULL;
    Directory* temp = NULL;
    temp = director->directories; //pastram arborele de subdirectoare
    //ma asigur ca numele fisierului pe care vreau sa-l inserez nu coincide 
    //cu un director
    if(check2(temp, nume_file)) {
        printf("Directory %s already exists!\n", nume_file);
        return 0;
    } 
    //daca nu exista niciun fisier in director   
    if(*fisier == NULL) {
        *fisier = create_file(nume_file, director);
        if(!(*fisier)) {
            printf("alocarea nu a reusit");
            return 0;
        }
        return 1;
    }	
    new = *fisier;
    while (new) {
        p = new;
        if(strcmp(nume_file, new->nume) < 0) {
            new = new->st;
        } else  if( strcmp(nume_file, new->nume) > 0) {
            new = new->dr;
        } else if( strcmp(nume_file, new->nume) == 0) {
            printf("File %s already exists!\n", nume_file);
            return 0;
        }
    }    
        aux = create_file(nume_file, director);
        if(!aux) return 0;
	    if(strcmp(nume_file, p->nume) < 0 )
		    p->st = aux;
	    else if(strcmp(nume_file, p->nume) > 0)	
		    p->dr = aux;

    return 1;
}

//function which finds the min number in the tree
File* minvalue(File* fis) {
    File* aux = fis;
    while(aux && aux->st != NULL) 
        aux = aux->st;
    return aux;
}

Directory* minvalue2(Directory* dir) {
    Directory* aux = dir;
    while(aux && aux->st != NULL) 
        aux = aux->st;
    return aux;
}

//function that delete a file
File* delete_file(File* fisier, char* nume_fisier, Directory* files) {
    if(fisier == NULL) 
        return fisier;

    //in cazul in care fisierul nu exita
    if(!file_exists(files->files, nume_fisier)) {
        printf("File %s doesn't exist!\n", nume_fisier);
        return fisier;
    }
    //il cautam in arbore
    if(strcmp(nume_fisier, fisier->nume) < 0) 
        fisier->st = delete_file(fisier->st, nume_fisier, files);
    else if(strcmp(nume_fisier, fisier->nume) > 0) 
        fisier->dr = delete_file(fisier->dr, nume_fisier,files);
    else {
        if(fisier->st == NULL) {
            File* temp = fisier->dr;
            free(fisier);
            return temp;
        } else if(fisier->dr == NULL) {
            File* temp = fisier->st;
            free(fisier);
            return temp;
        }

    File* aux = minvalue(fisier->dr);
    strcpy(fisier->nume, aux->nume);
    fisier->dr = delete_file(fisier->dr, aux->nume, files);
    }

    return fisier;
}

//function that delete a directory
Directory* delete_directory(Directory* director, char* nume_dir) {

    if(director == NULL) 
        return director;

    if(!check2(director, nume_dir)) {
        printf("Directory %s doesn't exist!\n", nume_dir);
        return director;
    }
    
    if(strcmp(nume_dir, director->nume) < 0) 
        director->st = delete_directory(director->st, nume_dir);
    else if(strcmp(nume_dir, director->nume) > 0) 
        director->dr = delete_directory(director->dr, nume_dir);
    else {
        if(director->st == NULL) {
            Directory* temp = director->dr;
            free(director);
            return temp;
        } else if(director->dr == NULL) {
            Directory* temp = director->st;
            free(director);
            return temp;
        }

     Directory* aux = minvalue2(director->dr);
     strcpy(director->nume, aux->nume);
     director->dr = delete_directory(director->dr, aux->nume);
        
    }

    return director;
}

//function which display File Tree
void SRD_file(File* a)
{
	if(!a) return;
	SRD_file(a->st);
    printf("%s ", a->nume);
	SRD_file(a->dr);
}

//function which display Directory tree
void SRD_dir(Directory* a)
{
	if(!a) return;
	SRD_dir(a->st);
    printf("%s ", a->nume);
	SRD_dir(a->dr);
}

//function which display the parents.
void SRD_parent(Directory* a) {

    if(!a) return;
    
    if(a->parinte) {
        printf("/%s", a->parinte->nume);
    } 
    printf("/%s", a->nume);
    a = a->parinte;
   
}

//function that creates a directory
int make_dir(Directory* dir, char* nume_dir, Directory* parinte) {
    Directory* aux = NULL;
    Directory* p = NULL;
    File* temp = dir->files;
    if(file_exists(temp, nume_dir)) {
        printf("File %s already exists!\n", nume_dir);
        return 0;
    }
    if(dir->directories == NULL) {
        dir->directories = create_directory(nume_dir, parinte );
        if(!(dir->directories)) {
            printf("alocarea nu a reusit");
            return 0;
        }
            return 1;
    }
    Directory* new = dir->directories;
    while (new != 0) {
        p = new;
        if(strcmp(nume_dir, new->nume) < 0) {
            new = new->st;
        } else  if( strcmp(nume_dir, new->nume) > 0) {
            new = new->dr;
        } else if( strcmp(nume_dir, new->nume) == 0)  {
            printf("Directory %s already exists!\n", nume_dir);
            return 0;
        } 
    }    
        aux = create_directory(nume_dir, parinte);
        if(!aux) return 0;
	    if(strcmp(nume_dir, p->nume) < 0 )
		    p->st = aux;
	    else if(strcmp(nume_dir, p->nume) > 0)	
		    p->dr = aux;

    return 1;
}

//function that destroy a file
void distruge_file(File **r) 
{   File *left = (*r)->st;
    (*r)->st = left->dr;
    left->dr = *r;
    *r = left;
}

void vine(File **tree)  {
    while (*tree) {
        while ((*tree)->st)
            distruge_file(tree);
        tree = &((*tree)->dr);
    }
}    

void TreeDestroy(File *tree)
{
    vine(&tree);
    while (tree) {
        assert(!tree->st);
        File *right = tree->dr;
        free(tree->nume);
        free(tree);
        tree = right;
    }
}

//functon which destroy a directory
void distruge_director(Directory **r)
{   Directory *left = (*r)->st;
    (*r)->st = left->dr;
    left->dr = *r;
    *r = left;
}

void vine_dir(Directory **tree)  {
    while (*tree) {
        while ((*tree)->st)
            distruge_director(tree);
        tree = &((*tree)->dr);
    }
}    

void DirDestroy(Directory *tree)
{
    vine_dir(&tree);
    while (tree) {
        assert(!tree->st);
        Directory *right = tree->dr;
        free(tree->nume);
        free(tree);
        tree = right;
    }
}

int main() {
   
    char nume[MAX_LEN] = "root";
    Directory* root = create_root(nume);
    char command[MAX_LEN];
    char* vector[100];
    vector[0] = "root";
    int i = 1;

    while(1) {
        scanf("%s", command);
        if(!strcmp(command, "touch")) {
            char nume_fisier[MAX_LEN];
            scanf("%s", nume_fisier);
            touch_file(&(root->files), nume_fisier, root);
         
        } else if(!strcmp(command, "mkdir")) {
            char nume_director[MAX_LEN];
            scanf("%s", nume_director);
            make_dir(root, nume_director, root);
               
        } else if(!strcmp(command,"ls")) {
            SRD_dir(root->directories);
            SRD_file(root->files);
            printf("\n");

        } else if(!strcmp(command,"rm")) {
            char nume_fisier[MAX_LEN];
            scanf("%s", nume_fisier);
            root->files = delete_file(root->files, nume_fisier, root);
             
        } else if(!strcmp(command, "rmdir")) {
            char nume_director[MAX_LEN];
            scanf("%s", nume_director);
            root->directories = delete_directory(root->directories,
                                                 nume_director);

        } else if(!strcmp(command, "cd")) {
            char nume_director[MAX_LEN];
            scanf("%s", nume_director);
            Directory* temp = create_root(nume_director);
            if(!check2(root->directories, nume_director) &&
                     strcmp(nume_director, "..") != 0)
                printf("Directory not found!\n");

            Directory* aux = find(root->directories, nume_director);
            if(!strcmp(nume_director, "..")) {
                root = root->parinte;
                i--;
            }    
            if(aux) {
                root = aux;
            }    
            if(check2(root, nume_director) && aux){
                *(vector + i) = temp->nume;
                i++;
            }

        } else if(!strcmp(command , "pwd")) {  
            for(int j = 0; j < i; j++) {
                printf("/%s", vector[j]);
            }  

            printf("\n");
            
        } else if(!strcmp(command, "find")) {
            return 0;   

        } else if(!strcmp(command, "quit")) {
            TreeDestroy(root->files);
            DirDestroy(root->directories);
            DirDestroy(root->parinte);
            DirDestroy(root);
            exit(EXIT_FAILURE);
        }
    }
   return 0;
}
