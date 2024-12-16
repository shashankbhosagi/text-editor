#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 8192
#define MAX_LINES 100
#define LINE_LENGTH 1024


void printBuffer(char *buffer){
    printf("*-*-*-*-*-*-*-*-*- \n%s\n", buffer);
    printf("*-*-*-*%ld*-*-*-*-\n",strlen(buffer));
}

void readFile(char *fileName, char buffer[]){
    FILE *f = fopen(fileName, "r");
    if (!f) {
        perror("Error opening file");
        exit(1);
    }
    size_t bytesRead = fread(buffer, sizeof(char), MAX_BUFFER_SIZE - 1, f);
    buffer[bytesRead] = '\0';
    fclose(f);
}
void writeFile(char *fileName, char **fileBuffer, int lineCount){
    FILE *f = fopen(fileName, "w");
    if (!f) {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < lineCount; i++) {
        fprintf(f, "%s\n", fileBuffer[i]);
    }
    fclose(f);

}
int parseLines(char *buffer, char **fileBuffer){
    int lineCount=0;
    char *lineStart = buffer;
    while(*lineStart != '\0'){
        if(lineCount>=MAX_LINES){
            fprintf(stderr, "Erro: file contains more then %d lines\n", MAX_LINES);
            exit(1);
        }
        char *lineEnd = strchr(lineStart, '\n');
        if (lineEnd == NULL) {
            lineEnd = lineStart + strlen(lineStart); 
        }

        size_t lineLength = lineEnd - lineStart;

        if(lineLength >=LINE_LENGTH){
            fprintf(stderr, "Error: The line exceeds the limit of %d", LINE_LENGTH);
            exit(1);
        }

        fileBuffer[lineCount] = (char *)malloc((lineLength + 1) * sizeof(char));
        if (fileBuffer[lineCount] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        strncpy(fileBuffer[lineCount], lineStart, lineLength);
        fileBuffer[lineCount][lineLength] = '\0'; // Null-terminate the line
        lineCount++;



        lineStart = (*lineEnd=='\n')?lineEnd+1:lineEnd;
    }


    return lineCount;
}

void printFile(char **fileBuffer, int lineCount){
        for(int i=0;i<lineCount;i++){
            printf("%d:%s\n", i, fileBuffer[i]);
        }
}


//! check if line number exists 0<lineNumber<=lineCount-1 
//? Feature make line number human readable like starting from 1.. instead of 0
void editLine(char **fileBuffer, char *newLine,int lineNumber){
    size_t newLength = strlen(newLine);
    if(newLength>LINE_LENGTH){
        printf("Can't store this exceed max allowed line length limit of %d\n", LINE_LENGTH);
        return;
    }
    fileBuffer[lineNumber] = (char *)realloc(fileBuffer[lineNumber],newLength);
    if(fileBuffer[lineNumber]==NULL){
        fprintf(stderr, "Error: Memory reallocation failed\n");
        exit(1);
    }
    strcpy(fileBuffer[lineNumber], newLine);
}

void appendLine(char **fileBuffer,char *lineToBeAppended, int *lineCount){
    fileBuffer[*lineCount] = (char *)malloc(strlen(lineToBeAppended)*sizeof(char));
    strcpy(fileBuffer[*lineCount], lineToBeAppended);
    *lineCount = *lineCount + 1;
}

void insertLine(char **fileBuffer, char *lineToBeInserted, int lineNumber, int *lineCount){
    if(*lineCount!=0){
        fileBuffer[*lineCount] = (char*)malloc(strlen(fileBuffer[*lineCount-1])*sizeof(char));
        strcpy(fileBuffer[*lineCount], fileBuffer[*lineCount-1]);
        for(int i=*lineCount;i>lineNumber;i--){
            fileBuffer[i] = (char*)realloc(fileBuffer[i], strlen(fileBuffer[i-1]));
            strcpy(fileBuffer[i], fileBuffer[i-1]);
        }
        fileBuffer[lineNumber] = (char*)realloc(fileBuffer[lineNumber], strlen(lineToBeInserted));
        strcpy(fileBuffer[lineNumber], lineToBeInserted);
        *lineCount = *lineCount+1;

    }else{
        fileBuffer[*lineCount] = (char*)malloc(strlen(lineToBeInserted)*sizeof(char));
        strcpy(fileBuffer[*lineCount], lineToBeInserted);
        *lineCount = *lineCount+1;
    }

}

void deleteLine(char **fileBuffer, int lineNumber, int *lineCount){
    
    // if(lineCount==0){
    //     printf("Error: cannot deleteLine");
    //     return;
    // }
    
    for(int i=lineNumber;i<*lineCount-1;i++){
        fileBuffer[i] =(char*) realloc(fileBuffer[i], strlen(fileBuffer[i+1]));
        strcpy(fileBuffer[i], fileBuffer[i+1]);
    }
    free(fileBuffer[*lineCount-1]);
    *lineCount = *lineCount -1;

}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <filename> \n",argv[0]);
        return 1;
    }
    char buffer[MAX_BUFFER_SIZE]; 
    char *fileBuffer[MAX_LINES]; 
    readFile(argv[1], buffer); // file is now in buffer :o

    int lineCount = parseLines(buffer, fileBuffer);
    printf("File has %d number of lines \n", lineCount);

     char command[10];

    while(1==1){
        scanf("%s", command);

        if(strcmp(command, "p") == 0 || strcmp(command, "print") == 0){
            printFile(fileBuffer, lineCount);
        }
        else if(strcmp(command, "a") == 0 || strcmp(command, "append") == 0){
            char lineToAppend[LINE_LENGTH];
            scanf(" %[^\n]",lineToAppend);
            if(strlen(lineToAppend)>=LINE_LENGTH){
                printf("Line Exceeds the maximum line length of %d\n", LINE_LENGTH);
            }
            appendLine(fileBuffer, lineToAppend, &lineCount);
        }
        else if(strcmp(command, "e") == 0 || strcmp(command, "edit") == 0){
            int lineNumber;
            char newLine[LINE_LENGTH];
            if(scanf("%d", &lineNumber) != 1){  // Check if input is valid
                printf("Invalid input. Please enter a number.\n");
            }
            if(lineNumber<0 || lineNumber>=lineCount){
                printf("Invalid line number\n");
                continue;
            }
            printf("%s\n",fileBuffer[lineNumber]);
            scanf(" %[^\n]", newLine);
            if(strlen(newLine)>=LINE_LENGTH){
                printf("Line Exceeds the maximum line length of %d\n", LINE_LENGTH);
            }
            editLine(fileBuffer, newLine, lineNumber);
        }
        else if(strcmp(command, "i") == 0 || strcmp(command, "insert") == 0){
            int line;
            char newLine[LINE_LENGTH];
            if(scanf("%d", &line) != 1){  // Check if input is valid
                printf("Invalid input. Please enter a number.\n");
            }
            if(line<0 || line>=lineCount){
                printf("Invalid line number\n");
                continue;
            }
            scanf(" %[^\n]", newLine);
            if(strlen(newLine)>=LINE_LENGTH){
                printf("Line Exceeds the maximum line length of %d\n", LINE_LENGTH);
            }
            insertLine(fileBuffer, newLine, line, &lineCount);
        }
        else if(strcmp(command, "d") == 0 || strcmp(command, "delete") == 0){
            int line;
            if(scanf("%d", &line) != 1){  // Check if input is valid
                printf("Invalid input. Please enter a number.\n");
            }
            if(line<0 || line>=lineCount){
                printf("Invalid line number\n");
                continue;
            }
            deleteLine(fileBuffer, line, &lineCount);
        }
        else if(strcmp(command, "w") == 0 || strcmp(command, "write") == 0){
            writeFile(argv[1], fileBuffer, lineCount);
        }
        else if (strcmp(command, "h") == 0 || strcmp(command, "help") == 0) {
            printf("Available commands:\n");
            printf("1. `p` or `print`: Prints the current contents of the file.\n");
            printf("2. `a` or `append`: Appends a new line to the end of the file.\n");
            printf("3. `e` or `edit`: Edits an existing line in the file.\n");
            printf("4. `i` or `insert`: Inserts a new line at a specific position in the file.\n");
            printf("5. `d` or `delete`: Deletes a specific line from the file.\n");
            printf("6. `w` or `write`: Writes the buffer contents to the file <saves the progress>.\n");
            printf("7. `h` or `help`: Displays this help message.\n");
            printf("8. `exit`: To exit the line editior, doesn't saves the buffer to file automatically.\n");
        }
        else if(strcmp(command, "exit") == 0){
            break;
        }
        else{
            printf("?\n");
        }
    }

    for(int i=0;i<lineCount;i++){
        free(fileBuffer[i]);
    }

    return 0;
}