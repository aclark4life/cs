#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Number of arguments: 0\n");
    } else {
        printf("Number of arguments: %d\n", argc - 1);
        for(int i = 1; i < argc; i++) {
            printf("Argument %d: %s\n", i, argv[i]);
        }
    }
    return 0;
}
