#include <stdio.h>
#include <string.h>

void deleteLine(char *buffer, int lineNumber){
    for(int i=0;i<lineNumber;i++){
        buffer = strchr(buffer, '\n');
        if (!buffer || *(buffer + 1) == '\0') {
            printf("Invalid line number!\n");
            return;
        }
        buffer++;
    }
    char *lineEnd = strchr(buffer, '\n');
    if (!lineEnd) {
        buffer[0] = '\0';
        return;     
    }
    strcpy(buffer, lineEnd + 1);
}

void editLine(char *buffer, int lineNumber){
    for(int i=0;i<lineNumber;i++){
        buffer = strchr(buffer, '\n');
        if (!buffer || *(buffer + 1) == '\0') {
            printf("Invalid line number!\n");
            return;
        }
        buffer++;
    }

    char *lineEnd = strchr(buffer, '\n');
    char saved[1024]={0};
    if (lineEnd) {
        strcpy(saved, buffer);     
    }

    scanf(" %[^\n]", buffer);

    if (lineEnd) {
        strcpy(buffer+strlen(buffer), saved);
    }else {
        buffer[strlen(buffer)] = '\0'; 
    }


}

void addLine(char *buffer, int lineNumber){
    for(int i=0;i<lineNumber;i++){
        buffer = strchr(buffer, '\n');
        if (!buffer || *(buffer + 1) == '\0') {
            printf("Invalid line number!\n");
            return;
        }
        buffer++;
    }
    // printf("Exited loop :) also... Line reading : %s\n", buffer);
    char temp[1024]={0};
    char saved[1024]={0};
    strcpy(saved, buffer);     

    scanf(" %[^\n]", temp);
    temp[strlen(temp)]='\n';
    strcpy(buffer+strlen(temp)+1, saved);
    buffer[strlen(buffer)] = '\0'; 

}

void printBuffer(char *buffer){
    // printf("*-*-*-*-*-*-*-*-*- \n%s\n", buffer);
    // printf("*-*-*-*-%ld*-*-*-*-\n",strlen(buffer));
}

char *readFile(char *fileName, char *buffer){
    FILE *f = fopen(fileName, "r");
    size_t bytesRead = fread(buffer, sizeof(char), 1023, f);
    buffer[bytesRead]='\0';
    fclose(f);
    return buffer;
}

void writeFile(char *fileName, char *buffer){
    FILE *f = fopen(fileName, "w");
    int length = strlen(buffer);
    fwrite(buffer, strlen(buffer), 1, f);
    fclose(f);
    printf("%ld\n",strlen(buffer));

}

int main(int argc, char** argv){
    char buffer[1024];
    char *fileName = argv[1];
    readFile(fileName, buffer);
    printBuffer(buffer);

    int lineNumber;
    char *command;
    while(1){
        printf("%s", buffer);
        scanf("%s", command);
        if(strcmp(command, "exit")==0){
            writeFile(fileName, buffer);
            break;
        }
        else if(strcmp(command, "p")==0){
            printBuffer(buffer);
        }
        else if(strcmp(command, "e")==0){
            scanf("%d", &lineNumber);
            editLine(buffer, lineNumber);
            buffer[strlen(buffer)] = '\0';
        }
        else if(strcmp(command, "a")==0){
            scanf("%d", &lineNumber);
            addLine(buffer, lineNumber);
            buffer[strlen(buffer)] = '\0';
        }
        else if(strcmp(command, "d")==0){
            scanf("%d", &lineNumber);
            deleteLine(buffer, lineNumber);
            buffer[strlen(buffer)] = '\0';
        }
        else{
            printf("?\n");
            // printf("Unknown command! Available commands: p, e, a, d and exit. \n");
        }
    }
    
    return 0;
}