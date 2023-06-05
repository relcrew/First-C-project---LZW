#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 5000
#define SINGLE_KEY_ASCII 256

typedef struct {
    char* value;
    int key;
} Dictionary;

void createDictionary(Dictionary* dictionary){
    for (int i = 0; i < SINGLE_KEY_ASCII; i++) {
        dictionary[i].value = malloc(sizeof(char));
        dictionary[i].value[0] = (char)i;
        dictionary[i].key = i;
    }
}

void LZW(const char* input, const char* output) {
    Dictionary dictionary[5000];
    createDictionary(dictionary);

    int dictSize = 256;

    FILE* inputFile = fopen(input, "r");
    FILE* outputFile = fopen(output, "w");

    char currentChar;
    char previousChar = fgetc(inputFile);

    while ((currentChar = fgetc(inputFile)) != -1) {
        char* value = malloc(strlen(dictionary[previousChar].value));
        strcpy(value, dictionary[previousChar].value);
        value[strlen(value)] = currentChar;

        int found = 0;

        for (int i = 0; i < dictSize; i++) {
            if (strcmp(value, dictionary[i].value) == 0) {
                previousChar = dictionary[i].key;
                break;
            }
        }

        if (found==0) {
            fprintf(outputFile, "%d ", dictionary[previousChar].key);
            dictionary[dictSize].value = malloc(strlen(value));
            strcpy(dictionary[dictSize].value, value);
            dictionary[dictSize].key = dictSize;
            dictSize++;

            previousChar = currentChar;
        }

        free(value);
    }

    fclose(inputFile);
    fclose(outputFile);

    for (int i = 0; i < dictSize; i++) {
        free(dictionary[i].value);
    }
}

int main(int argc, char const *argv[]) {

    LZW(argv[1], "compressed.txt");

    return 0;
}
