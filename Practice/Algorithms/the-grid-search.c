#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);
int checkpatterns(int c, int d, int G_count, char **G, int P_count, char **P)
{
    int temp_d = d;
    for (int e = 0; e < P_count; e++)
    {
        for (int f = 0, l = strlen(P[e]); f < l; f++)
        {
            if ((d == strlen(G[c])) || (c == G_count) || (P[e][f] != G[c][d]))
                return 0;
            d++;
        }
        c++;
        d = temp_d;
    }
    return 1;
}

char* gridSearch(int G_count, char** G, int P_count, char** P)
{
    for (int c = 0; c < G_count; c++)
        for (int d = 0, l = strlen(G[c]); d < l; d++)
            if ((G[c][d] == P[0][0]) && (checkpatterns(c, d, G_count, G, P_count, P)))
                return "YES";
    return "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int R = parse_int(*(first_multiple_input + 0));

        int C = parse_int(*(first_multiple_input + 1));

        char** G = malloc(R * sizeof(char*));

        for (int i = 0; i < R; i++) {
            char* G_item = readline();

            *(G + i) = G_item;
        }

        char** second_multiple_input = split_string(rtrim(readline()));

        int r = parse_int(*(second_multiple_input + 0));

        int c = parse_int(*(second_multiple_input + 1));

        char** P = malloc(r * sizeof(char*));

        for (int i = 0; i < r; i++) {
            char* P_item = readline();

            *(P + i) = P_item;
        }

        char* result = gridSearch(R, G, r, P);

        fprintf(fptr, "%s\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
