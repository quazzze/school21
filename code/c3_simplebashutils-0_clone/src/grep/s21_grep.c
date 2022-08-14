#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 2048
#define STRMAX 1024

typedef struct options {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
}opt;

void parser(int argc, char** argv, opt* options, char* ef_arg);
void init_options();
void add_e_arg(char* ef_arg, char* optarg, int* ef_counter);
void add_f_arg(char* ef_arg, char* optarg, int* ef_counter, int flag_s);
void search_and_print(char* name, opt options, char* ef_arg, int number_of_files);

int main(int argc, char* argv[]) {
    char ef_arg[BUFSIZE] = {0};
    opt options = {0};
    parser(argc, argv, &options, ef_arg);
    int file_to_read;
    char* regex_;
    if (options.f == 1 || options.e == 1) {
        file_to_read = optind;
        regex_ = ef_arg;
    } else {
        file_to_read = optind + 1;
        regex_ = argv[optind];
    }
    int number_of_files = argc - file_to_read;
    for (; argv[file_to_read]; file_to_read++)
        search_and_print(argv[file_to_read], options, regex_, number_of_files);
}

void search_and_print(char* name, opt options, char* regex_,
            int number_of_files) {
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(name, "r")) == NULL) {
        if (!options.s) printf("s21_grep: %s: No such file or directory", optarg);
    } else {
        regex_t regex = {0};
        if (options.i)
            regcomp(&regex, regex_, REG_EXTENDED | REG_ICASE);
        else
            regcomp(&regex, regex_, REG_EXTENDED);
        char line[BUFSIZE] = {0};
        int line_counter = 0;
        int success_counter = 0;
        regmatch_t regmat[1] = {0};
        char result_o[BUFSIZE];
        if (options.v) options.o = 0;
        while (!feof(file_ptr)) {
            line_counter++;
            fgets(line, BUFSIZE, file_ptr);
            int status = regexec(&regex, line, 1, regmat, 0);
            if (options.v) status = (status) ? 0 : 1;
            if (!status && line[0] != 0) {
                if (number_of_files > 1 && !options.c && !options.l && !options.h)
                    printf("%s:", name);
                if (options.n && !options.c && !options.l)
                    printf("%d:", line_counter);
                if (options.o) {
                    char* ptr = line;
                    while (status == 0) {
                        int len = regmat[0].rm_eo - regmat[0].rm_so;
                        memcpy(result_o, ptr + regmat[0].rm_so, len);
                        result_o[len] = 0;
                        if (!options.l && !options.c) {
                            printf("%s\n", result_o);
                        }
                        ptr += regmat[0].rm_eo;
                        status = regexec(&regex, ptr, 1, regmat, REG_NOTBOL);
                    }
                }
                success_counter++;
                if (!options.c && !options.l && !options.o) {
                    printf("%s", line);
                    if (line[strlen(line)-1] != '\n')
                        printf("\n");
                }
                line[0] = '\0';
            }
        }
        if (number_of_files > 1 && options.c && !options.h) printf("%s:", name);
        if (options.c && options.l && success_counter) success_counter = 1;
        if (options.c) printf("%d\n", success_counter);
        if (options.l && success_counter) printf("%s\n", name);
        regfree(&regex);
        fclose(file_ptr);
    }
}

void parser(int argc, char** argv, opt* options, char* ef_arg) {
    int c;
    int ef_counter = 0;
    while ((c = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
        if (c == 'e') {
            options->e = 1;
            add_e_arg(ef_arg, optarg, &ef_counter);
        }
        if (c == 'i') options->i = 1;
        if (c == 'v') options->v = 1;
        if (c == 'c') options->c = 1;
        if (c == 'l') options->l = 1;
        if (c == 'n') options->n = 1;
        if (c == 'h') options->h = 1;
        if (c == 's') options->s = 1;
        if (c == 'f') {
            options->f = 1;
            add_f_arg(ef_arg, optarg, &ef_counter, options->s);
        }
        if (c == 'o') options->o = 1;
    }
}
void add_e_arg(char* ef_arg, char* optarg, int* ef_counter) {
    if (*optarg == '\0') {
        optarg[0] = '.';
        optarg[1] = '\0';
    }
    if (*ef_counter) {
        char ch[2] = "|";
        strcat(ef_arg, ch);
        strcat(ef_arg, optarg);
    } else {
        strcat(ef_arg, optarg);
    }
    *ef_counter += 1;
}

void add_f_arg(char* ef_arg, char* optarg, int* ef_counter, int flag_s) {
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(optarg, "r")) == NULL) {
        if (!flag_s) printf("s21_grep: %s: Noo such file or directory", optarg);
        exit(1);
    }
    while (!feof(file_ptr)) {
        if (*ef_counter) {
            char ch[2] = "|";
            strcat(ef_arg, ch);
            int len = strlen(ef_arg);
            fgets(ef_arg + len, STRMAX, file_ptr);
            if (ef_arg[len] == '\n') ef_arg[len] = '.';
            if (ef_arg[len] == '\0') ef_arg[len-1] = 'g';
            if (ef_arg[strlen(ef_arg) - 1] == '\n') ef_arg[strlen(ef_arg) - 1] = '\0';
        } else {
            fgets(ef_arg, STRMAX, file_ptr);
            if (ef_arg[0] == '\n') ef_arg[0] = '.';
            else if (ef_arg[strlen(ef_arg) - 1] == '\n') ef_arg[strlen(ef_arg) - 1] = '\0';
        }
        *ef_counter += 1;
    }
    fclose(file_ptr);
}
