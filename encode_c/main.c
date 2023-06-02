#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define CLEAR_CODE 256
#define END_CODE 257

char** create_dico(int code) {
    char** dico = (char**)malloc(sizeof(char*) * code);
    for (int i = 0; i < code; i++) {
        dico[i] = (char*)malloc(sizeof(char) * 50);
        dico[i][0] = (char)i;
        dico[i][1] = '\0';
    }
    return dico;
}

int find(char** dict, int size, char* input) {
    for (int i = 0; i < size; i++) {
        if (dict[i] && strcmp(dict[i], input) == 0) {
            return i;
        }
    }
    return -1;
}

void encoder() {
    int size = 258;
    char** dict = create_dico(size);
    char input;
    char last_valid[50] = "";

    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    fprintf(outputFile, "%d ", CLEAR_CODE);
    
    while (!feof(inputFile)) {
        input = fgetc(inputFile);
        if(input==-1){
            break;
        }
        char*try = (char*)malloc((strlen(last_valid) + strlen((char[2]) {input, '\0'}) +1)* sizeof(char));
        strcpy(try, last_valid);
        strcat(try, (char[2]) {input, '\0'});
        if (find(dict, size, try) != -1) {
            strcpy(last_valid, try);
        } else {
            fprintf(outputFile, "%d ", find(dict, size, last_valid));
            dict[size] = (char*)malloc((strlen(try) + 1) * sizeof(char));
            strcpy(dict[size], try);
            size++;
            strcpy(last_valid, (char[2]) {input, '\0'});    
        }
        free(try);
    }

    fprintf(outputFile, "%d ", find(dict, size, last_valid));
    fprintf(outputFile, "%d",  END_CODE);

    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char const* argv[]) {
    encoder();
    return 0;
}