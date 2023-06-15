#include "../include/code.h"

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
