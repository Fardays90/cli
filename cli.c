#include <stdio.h>
#include <string.h>

void help(){
    printf("Available commands:\n");
    printf("help - Show this help message\n");
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
        else if(strcmp(command, "exit") == 0){
            break;
        }else{
            printf("Unknown command: %s\n", command);
        }
    }
    printf("We shall meet again. \n");
    return 0;
}