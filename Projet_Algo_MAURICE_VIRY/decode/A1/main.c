#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define CLEAR_CODE 256
#define END_CODE 257

typedef struct {
    char* key;
    int value;
} Dico;

Dico** create_dico(int code) {
    Dico** dico = (Dico**) malloc(sizeof(Dico*) * code);
    for (int i = 0; i < 128; i++) {
        dico[i] = (Dico*) malloc(sizeof(Dico) * code);
        dico[i]->key = (char*) malloc(sizeof(char)*2);
        dico[i]->value = i;
        dico[i]->key = (char[2]) { (char) i,'\0'};
    }
    return dico;
}

int find(Dico** dict, int size, char*input) {
    for (int i = 0; i < size; i++) {
        printf("s %s", dict[i]->key);
        if (strcmp(dict[i]->key, input) == 0) {
            return i;
        }
    }
    return -1;
}

void LZW() {
    Dico** dict = create_dico(256);
    /* printf("%scaca", dict[78]->key); */
    int size = 258;

    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");
    char input;

    char last_valid[100] = "";

    fprintf(outputFile, "%d ", CLEAR_CODE);

    while ((input = fgetc(inputFile)) != -1) {
        char try[100];
        strcpy(try, last_valid);
        strncat(try, (char*)&input, 1);
        if (find(dict, size, try) != -1) {
            strcat(last_valid, &input);
        } else {
            printf("%d", find(dict, size, last_valid));
            fprintf(outputFile, "%d ", dict[find(dict, size, last_valid)]->value);
            dict[size]->key = malloc((strlen(try) + 1) * sizeof(char));
            strcpy(dict[size]->key, try);
            dict[size]->value = size;
            size++;
            strcpy(last_valid, &input);
        }
    }

    fprintf(outputFile, "%d %d\n", dict[find(dict, size, last_valid)]->value, END_CODE);

    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char const* argv[]) {
    LZW();
    return 0;
}