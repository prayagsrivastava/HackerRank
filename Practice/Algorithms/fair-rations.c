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

char* reverse_string(char* s)
{
    int l = strlen(s), counter = 0;
    char* news = malloc(sizeof(char)*(l+1));
    for (int c=l-1; c>=0; c--)
    {
        news[counter] = s[c];
        counter++;
    }
    news[l] = '\0';
    free(s);
    return news;
}

char* itos(int s)
{
    char* string = NULL;
    if (s == 0)
    {
        string = malloc(sizeof(char)*2);
        string[0] = '0';
        string[1] = '\0';
        return string;
    }
    
    int multiple = 10, counter = 0, temp;
    while(s)
    {
        temp = (s % multiple);
        if (temp == s && counter == 0)
        {
            string = malloc(sizeof(char)*2);
            string[0] = (char) (temp + 48);
            string[1] = '\0';
            return string;
        }
        else
        {
            string = realloc(string, sizeof(char)*(counter+2));
            string[counter] = (char) (temp + 48);
            string[counter+1] = '\0';
            counter++;
        }
        s = s / multiple;
    }

    if (strlen(string) > 1)
        return reverse_string(string);
    else
        return string;
}

char* fairRations(int B_count, int* B)
{
    int loaf = 0;
    for (int c = 0; c < (B_count); c++)
    {
        if ((B[c] % 2) != 0)
        {
            if (c && ((B[c-1]%2) != 0))
            {
                B[c]++;
                B[c-1]++;
                loaf += 2;
            }
            else if ((c+1) < B_count)
            {
                B[c]++;
                B[c+1]++;
                loaf += 2;
            }
        }
    }
    if ((B[B_count-1] % 2) == 0)
        return itos(loaf);
    else
        return "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int N = parse_int(ltrim(rtrim(readline())));

    char** B_temp = split_string(rtrim(readline()));

    int* B = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        int B_item = parse_int(*(B_temp + i));

        *(B + i) = B_item;
    }

    char* result = fairRations(N, B);

    fprintf(fptr, "%s\n", result);

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
