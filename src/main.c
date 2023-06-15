#include "../include/encode.h"
#include "../include/decode.h"

int main(int argc, char const* argv[]) {
    /* if (!strcmp(argv[1], "-d")) {
        decoder((char*) argv[2]);
    } else if (!strcmp(argv[1], "-e")) {
        encoder((char*) argv[2]);
    } else {
        printf("invalid arg\n");
        return 1;
    } */

    encoder("./input/input.txt");
    return 0;
}
