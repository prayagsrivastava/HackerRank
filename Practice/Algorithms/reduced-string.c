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

/*
 * Complete the 'superReducedString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* str_array_remove(int index, char* s)
{
    int l = strlen(s), counter = 0;
    char* new_s = NULL;
    
    for (int c = 0; c < l; c++)
    {
        if (c != index)
        {
            new_s = realloc(new_s, sizeof(char)*(counter+2));
            new_s[counter] = s[c];
            new_s[counter+1] = '\0';
            counter++;
        }
        else
            c++;
    }

    if (!counter)
        return "";
    
    free(s);
    return new_s;
}

char* superReducedString(char* s)
{
    int check = 1, l;
    while (check)
    {
        check = 0;
        l = strlen(s);
        for (int c = 0; c < (l - 1); c++)
            if (s[c] == s[c+1])
            {
                s = str_array_remove(c, s);
                check = 1;
                break;
            }
        if (!l)
            break;
    }
    if (!l)
        return "Empty String";
    else
        return s;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = superReducedString(s);

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
