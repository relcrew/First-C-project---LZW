#include "../include/decode.h"

char** create_dico(int code) {
    char** dico = (char**)malloc(sizeof(char*) * code);
    for (int i = 0; i < code; i++) {
        dico[i] = (char*)malloc(sizeof(char) * 50);
        dico[i][0] = (char)i;
        dico[i][1] = '\0';
    }
    return dico;
}

int find_decode(char** dict, int size, char* input) {
    for (int i = 0; i < size; i++) {
        if (dict[i] && strcmp(dict[i], input) == 0) {
            return i;
        }
    }
    return -1;
}

void decoder(char*path) {

    char code[4] = "";
    char seq[50] = "";
    int next_code;
    char*try;
    char last_valid[50] = "";
    char** dict = NULL;

    FILE* inputFile = fopen(path, "r");
    FILE* outputFile = fopen("../input/input.txt", "w");

    while (fscanf(inputFile, "%s", code) == 1) {

        printf("%s\n", code);

        if(atoi(code) == CLEAR_CODE){
            next_code = 255;
            dict = create_dico(next_code);
            next_code += 2;
            strcpy(last_valid, "");
            continue;
        }

        if(atoi(code) == END_CODE){
            break;
        }

        if(dict[atoi(code)]){
            strcpy(seq,dict[atoi(code)]);
        }else{
            try = (char*)malloc((strlen(last_valid) + 2)* sizeof(char));
            strcpy(try, last_valid);
            strcat(try, (char[2]) {last_valid[0], '\0'});
            free(try);
        }
        fprintf(outputFile, "%s",  seq);
        if (!strcmp(last_valid,"")){
            try = (char*)malloc((strlen(last_valid) + 2)* sizeof(char));
            strcpy(try, last_valid);
            strcat(try, (char[2]) {seq[0], '\0'});
            dict[next_code] = (char*)malloc((strlen(try) + 1) * sizeof(char));
            next_code++;
            free(try);
        }
        strcpy(last_valid,seq);
    }

    fclose(inputFile);
    fclose(outputFile);
}
