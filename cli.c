#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_FILES 1000 

typedef struct{
    char name[256];
    time_t mod_time;
}FileInfo;

FileInfo files[MAX_FILES];
int file_count = 0;

void list_files(){
    DIR *d;
    struct dirent *dir;
    struct stat file_stat;
    d = opendir(".");
    if(d){
        while((dir = readdir(d)) != NULL){
            if(stat(dir->d_name, &file_stat) == 0 && S_ISREG(file_stat.st_mode)){
                strcpy(files[file_count].name,  dir-> d_name);
                stat(dir -> d_name, &file_stat);
                files[file_count].mod_time = file_stat.st_mtime;
                file_count++;
            }
        }
        closedir(d);
    }
}
int compare_alpha(const void *a, const void *b){
    return strcmp(((FileInfo *)a) -> name, ((FileInfo *)b) -> name);
}
int compare_time(const void *a, const void *b){
    return difftime(((FileInfo*) b) -> mod_time, ((FileInfo*)a) -> mod_time);
}
void sort_alpha(){
    qsort(files, file_count, sizeof(FileInfo), compare_alpha);
    printf("Files sorted alphabetically:\n");
    for(int i = 0; i < file_count; i++){
        printf("%s\n", files[i].name);
    }
}
void sort_time(){
    qsort(files, file_count, sizeof(FileInfo), compare_time);
    printf("Files sorted by modification time (newest first):\n");
    for(int i = 0; i < file_count; i++){
        printf("%s\n", files[i].name);
    }
}
void list(){
    for(int i = 0; i < file_count; i++){
        printf("%s\n", files[i].name);
    }
}

void help(){
    printf("Available commands:\n");
    printf("help - Show this help message\n");
    printf("list - Check all the files in current directory\n");
    printf("sort_alpha - Sort files alphabetically\n");
    printf("sort_time - Sort files by modification time\n");
    printf("exit - Exit the CLI\n");
}
int main(int argc, char *argv[]){
    char command[256];
    printf("-----------------------------------------------------------------------------\n");
    printf("Welcome to the blood moon cli. Type 'help' to check all commands available.\n");

    while(1){
        printf("~~>");
        if(fgets(command, sizeof(command), stdin) == NULL){
            break;
        }
        command[strcspn(command, "\n")] = 0;
        if(strcmp(command, "help") == 0){
            help();
        }
        else if(strcmp(command, "sort_alpha") == 0){
            list_files();
            sort_alpha();
        }
        else if(strcmp(command, "list") == 0){
            list_files();
            list();
        }
        else if(strcmp(command, "sort_time") == 0){
            list_files();
            sort_time();
        }
        else if(strcmp(command, "exit") == 0){
            break;
        }else{
            printf("Unknown command: %s\n", command);
        }
    }
    printf("We shall meet again. \n");
    return 0;
}