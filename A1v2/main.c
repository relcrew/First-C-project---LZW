#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 5000
#define SINGLE_VALUE_ASCII 256

typedef struct {
    char* key;
    int value;
} Dictionary;

void createDictionary(Dictionary* dictionary){
    for (int i = 0; i < SINGLE_VALUE_ASCII; i++) {
        dictionary[i].key = malloc(sizeof(char)); 
        dictionary[i].key[0] = (char)i;
        dictionary[i].value = i;
    }
}

void LZW(const char* input, const char* output) {
    Dictionary dictionary[5000];
    createDictionary(dictionary);

    int dictSizeSingleValue = 256; 

    FILE* inputFile = fopen(input, "r");
    FILE* outputFile = fopen(output, "w");

    char currentChar;
    char previousChar = fgetc(inputFile);

    while ((currentChar = fgetc(inputFile)) != EOF) {
        char* key = malloc(strlen(dictionary[previousChar].key));
        strcpy(key, dictionary[previousChar].key);
        key[strlen(key)] = currentChar;

        int found = 0;
        for (int i = 0; i < dictSizeSingleValue; i++) {
            if (strcmp(key, dictionary[i].key) == 0) {
                previousChar = dictionary[i].value;
                found = 1;
                break;
            }
        }

        if (found==0) {
            fprintf(outputFile, "%d ", dictionary[previousChar].value);
            dictionary[dictSizeSingleValue].key = malloc(strlen(key));
            strcpy(dictionary[dictSizeSingleValue].key, key);
            dictionary[dictSizeSingleValue].value = dictSizeSingleValue;
            dictSizeSingleValue++;

            previousChar = currentChar;
        }

        free(key);
    }

    fwrite(&dictionary[previousChar].value, sizeof(int), 1, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    for (int i = 0; i < dictSizeSingleValue; i++) {
        free(dictionary[i].key);
    }
}

int main(int argc, char const *argv[]) {

    LZW(argv[1], "compressed.txt");

    return 0;
}