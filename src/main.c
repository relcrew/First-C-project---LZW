#include "../include/code.h"

void encoder() {
    int size = 258;
    HashTable* dict = createHashTable(MAX_DICT_SIZE);

    char input;
    char last_valid[50] = "";

    FILE* inputFile = fopen("./input/input.txt", "r");
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

void decoder() {
    HashTable* dict = createHashTable(MAX_DICT_SIZE);

    char code[4] = "";
    char* seq = NULL;
    char* last_valid = "";
    int next_code = 258;

    FILE* inputFile = fopen("./output/output.txt", "r");
    FILE* outputFile = fopen("./input/input.txt", "w");

    while (fscanf(inputFile, "%s", code) == 1) {
        int current_code = atoi(code);

        if (current_code == CLEAR_CODE) {
            free_dict(dict);
            dict = createHashTable(MAX_DICT_SIZE);
            next_code = 258;
            last_valid = "";
            continue;
        }
        if (current_code == END_CODE) {
            break;
        }
        seq = find(dict, current_code);
        if (seq != NULL) {
            fprintf(outputFile, "%s", seq);
            char* new_seq = (char*)malloc((strlen(last_valid) + 2) * sizeof(char));
            strcpy(new_seq, last_valid);
            new_seq[strlen(last_valid)] = seq[0];
            new_seq[strlen(last_valid) + 1] = '\0';
            insert(dict, new_seq, next_code);
            next_code++;
            free(new_seq);
            last_valid = seq;
        } else {
            seq = (char*)malloc((strlen(last_valid) + 2) * sizeof(char));
            strcpy(seq, last_valid);
            seq[strlen(last_valid)] = last_valid[0];
            seq[strlen(last_valid) + 1] = '\0';
            fprintf(outputFile, "%s", seq);
            insert(dict, seq, next_code);
            next_code++;
            last_valid = seq;
        }
    }

    free_dict(dict);
    fclose(inputFile);
    fclose(outputFile);
}


int main(int argc, char const* argv[]) {
    if (!strcmp(argv[1], "-d")) {
        decoder();
    } else if (!strcmp(argv[1], "-e")) {
        encoder();
    } else {
        printf("invalid arg\n");
        return 1;
    }
    return 0;
}
