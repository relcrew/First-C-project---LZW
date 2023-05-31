#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096

typedef struct {
    char* key;
    int value;
} DictionaryEntry;

void LZW(const char* input, const char* output) {
    DictionaryEntry dictionary[MAX_DICT_SIZE];
    int dictSize = 256; 
    for (int i = 0; i < dictSize; i++) {
        dictionary[i].key = malloc(sizeof(char)); 
        dictionary[i].key[0] = (char)i;
        dictionary[i].value = i;
    }

    FILE* inputFile = fopen(input, "r");
    FILE* outputFile = fopen(output, "w");

    char currentChar;
    char previousChar = fgetc(inputFile); //renvoie la valeur ascii de la 1ere valeur du FILE

    while ((currentChar = fgetc(inputFile)) != EOF) {
        char* key = malloc(strlen(dictionary[previousChar].key));
        strcpy(key, dictionary[previousChar].key);
        key[strlen(key)] = currentChar;

        int found = 0;
        for (int i = 0; i < dictSize; i++) {
            if (strcmp(key, dictionary[i].key) == 0) {
                previousChar = dictionary[i].value;
                found = 1;
                break;
            }
        }

        if (found==0) {
            fprintf(outputFile, "%d ", dictionary[previousChar].value);
            dictionary[dictSize].key = malloc(strlen(key));
            strcpy(dictionary[dictSize].key, key);
            dictionary[dictSize].value = dictSize;
            dictSize++;

            previousChar = currentChar;
        }

        free(key);
    }

    fwrite(&dictionary[previousChar].value, sizeof(int), 1, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    for (int i = 0; i < dictSize; i++) {
        free(dictionary[i].key);
    }
}

int main(int argc, char const *argv[]) {

    LZW(argv[1], "compressed.txt");

    return 0;
}