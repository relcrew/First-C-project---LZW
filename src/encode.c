#include "../include/encode.h"

unsigned int hash(const char* key, int tableSize) {
    unsigned int hashValue = 0;
    int length = strlen(key);

    for (int i = 0; i < length; i++) {
        hashValue = (hashValue << 5) + key[i];
    }

    return hashValue % tableSize;
}

void free_dict(HashTable* dict) {
    if (dict == NULL) {
        return;
    }

    for (int i = 0; i < dict->size; i++) {
        if (dict->entries[i] != NULL) {
            free(dict->entries[i]->key);
            free(dict->entries[i]);
        }
    }

    free(dict->entries);
    free(dict);
}

void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key, table->size);

    while (table->entries[index] != NULL) {
        index = (index + 1) % table->size;
    }

    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = value;

    table->entries[index] = entry;
}

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->entries = (Entry**)malloc(sizeof(Entry*) * size);
    table->size = size;

    for (int i = 0; i < 256; i++) {
        char* entry = (char*)malloc(2 * sizeof(char));
        entry[0] = (char)i;
        entry[1] = '\0';
        insert(table, entry, i);
    }

    return table;
}

int find(HashTable* table, const char* value) {
    unsigned int index = hash(value, table->size);

    while (table->entries[index] != NULL) {
        if (strcmp(table->entries[index]->key, value) == 0) {
            return table->entries[index]->value;
        }
        index = (index + 1) % table->size;
    }

    return -1;
}

void encoder(char*path) {
    int size = 258;
    HashTable* dict = createHashTable(MAX_DICT_SIZE);

    char input;
    char last_valid[50] = "";

    FILE* inputFile = fopen(path, "r");
    FILE* outputFile = fopen("./output/output.txt", "w");

    fprintf(outputFile, "%d ", CLEAR_CODE);

    while (!feof(inputFile)) {
        input = fgetc(inputFile);
        if (input == -1) {
            break;
        }

        char* try = (char*)malloc((strlen(last_valid) + 2) * sizeof(char));
        strcpy(try, last_valid);
        try[strlen(last_valid)] = input;
        try[strlen(last_valid) + 1] = '\0';

        if (find(dict, try) != -1) {
            strcpy(last_valid, try);
        } else {
            fprintf(outputFile, "%d ", find(dict, last_valid));
            insert(dict, try, size);
            size++;
            strcpy(last_valid, (char[2]) {input, '\0'});
        }

        free(try);
    }

    fprintf(outputFile, "%d ", find(dict, last_valid));
    free_dict(dict);
    fprintf(outputFile, "%d", END_CODE);

    fclose(inputFile);
    fclose(outputFile);
}