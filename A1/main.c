#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096

typedef struct {
    char* key;
    int value;
} DictionaryEntry;

void compressLZW(const char* input, const char* output) {

    DictionaryEntry dictionary[MAX_DICT_SIZE];
    int dictSize = 256;
    for (int i = 0; i < dictSize; i++) {
        dictionary[i].key = malloc(sizeof(char));
        dictionary[i].key[0] = (char)i;
        dictionary[i].key[1] = '\0';
        dictionary[i].value = i;
    }

    FILE* inputFile = fopen(input, "r");
    FILE* outputFile = fopen(output, "w");

    char currentChar;
    char previousChar = fgetc(inputFile);

    while ((currentChar = fgetc(inputFile)) != EOF) {
        char* key = malloc(strlen(dictionary[previousChar].key) + 2);
        strcpy(key, dictionary[previousChar].key);
        key[strlen(key)] = currentChar;
        key[strlen(key) + 1] = '\0';

        int found = 0;
        for (int i = 0; i < dictSize; i++) {
            if (strcmp(key, dictionary[i].key) == 0) {
                previousChar = dictionary[i].value;
                found = 1;
                break;
            }
        }

        if (!found) {
            //fwrite(&dictionary[previousChar].value, sizeof(int), 1, outputFile);
            fprintf(outputFile, "%d ", dictionary[previousChar].value);
            dictionary[dictSize].key = malloc(strlen(key) + 2);
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

    // Libération de la mémoire
    for (int i = 0; i < dictSize; i++) {
        free(dictionary[i].key);
    }
}

int main() {
    const char* inputFileName = "input.txt";
    const char* compressedFileName = "compressed.txt";

    compressLZW(inputFileName, compressedFileName);

    return 0;
}
