#include <ctype.h>
#include <getopt.h>
#include <stdio.h>

typedef struct options {
    int b;
    int v;
    int e;
    int n;
    int s;
    int t;
}opt;

void parser(int argc, char* argv[], opt* options);
void opener(int argc, char* argv[], opt options);
void reader(FILE* file_ptr, opt options);

int main(int argc, char* argv[]) {
    opt options = {0};
    parser(argc, argv, &options);
    opener(argc, argv, options);
    return 0;
}

void parser(int argc, char* argv[], opt* options) {
    struct option long_flags[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
    int opt = 0, opt_index = 0;
    while ((opt = getopt_long(argc, argv, "benstvET", long_flags,
                                  &opt_index)) != -1) {
        switch (opt) {
            case 'b':
                options->b = 1;
                break;
            case 'v':
                options->v = 1;
                break;
            case 'e':
                options->v = 1;
                options->e = 1;
                break;
            case 'E':
                options->e = 1;
                break;
            case 'n':
                options->n = 1;
                break;
            case 's':
                options->s = 1;
                break;
            case 't':
                options->v = 1;
                options->t = 1;
                break;
            case 'T':
                options->t = 1;
                break;
            default:
                break;
        }
    }
    if (options->b == 1) {
        options->n = 0;
    }
}

void opener(int argc, char* argv[], opt options) {
    int argv_index = 1;
    while (*argv[argv_index] == '-') {
        argv_index++;
    }
    for (; argv_index < argc; argv_index++) {
        FILE* file_ptr = NULL;
        if ((file_ptr = fopen(argv[argv_index], "r")) == NULL) {
            printf("cat: %s: No such file or directory\n", argv[argv_index]);
        } else {
            reader(file_ptr, options);
            fclose(file_ptr);
        }
    }
}

void reader(FILE* file_ptr, opt options) {
    char ch = 0;
    int prev_char = 0;
    int lines_count = 1;
    int new_line = 1;
    while ((ch = fgetc(file_ptr)) != EOF) {
        if (options.s) {
            if (ch == '\n') {
                prev_char++;
                if (prev_char >= 3) {
                    continue;
                }
            } else {
                prev_char = 0;
            }
        }
        if (options.b) {
            if (new_line) {
                if (ch != '\n') {
                    printf("%6d\t", lines_count++);
                    new_line = 0;
                }
            }
            if (ch == '\n') {
                new_line = 1;
            }
        }
        if (options.n) {
            if (new_line) {
                printf("%6d\t", lines_count++);
                new_line = 0;
            }
            if (ch == '\n') {
                new_line = 1;
            }
        }
        if (options.e) {
            if (ch == '\n') {
                printf("%c", '$');
            }
        }
        if (options.t) {
            if (ch == '\t') {
                printf("%c", '^');
                ch = 'I';
            }
        }
        if (options.v) {
            if (!isprint(ch) && ch != 10 && ch != 9) {
                printf("^");
                if (ch == 127)
                    ch -= 64;
                else
                    ch += 64;
            }
        }
        printf("%c", ch);
    }
}
