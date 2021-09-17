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

int parse_int(char*);

/*
 * Complete the 'biggerIsGreater' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING w as parameter.
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
int largest_index_k(char* s);
int largest_index_l(char* s, int k);
void swap(char* s, int k, int l);
void reverse_sequence(char*s, int k, int l);
int next_permutation(char *s);

char* biggerIsGreater(char* w)
{
    //https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order
    int c = next_permutation(w);
    if (c)
        return w;
    else
        return "no answer";
}

int next_permutation(char *s)
{       
    int k = largest_index_k(s);
    if (k < 0)
        return 0;

    int l = largest_index_l(s, k);

    swap(s, k, l);
    reverse_sequence(s, k, l);
    return 1;
}


void sort_string(char** arr , int len)
{
    char* temp = NULL;
    int swaps = 0;
    for (int c = 0; c < len ; c++)
    {
        for (int d = c + 1; d < len; d++)
        {
            if (strcmp(arr[c], arr[d]) > 0)
            {
                temp = arr[c];
                arr[c] = arr[d];
                arr[d] = temp;
            }
        }
    }
}


void reverse_sequence(char*s, int k, int l)
{
    int size = strlen(s);
    k = k + 1;
    if (k == size-1)
        return;
    
    char temp;
    for (int c = size-1; c >= k; c--)
    {
        if (k >= c)
            break;
        temp = s[c];
        s[c] = s[k];
        s[k] = temp;
        k++;
    }
    return;
}


void swap(char* s, int k, int l)
{
    char temp = s[k];
    s[k] = s[l];
    s[l] = temp;
}


int largest_index_k(char* s)
{
    int lindex = -1;

    for (int c=1, n=strlen(s); c<n; c++)
        if (s[c-1] < s[c])
            if (c > lindex)
                lindex = c;
    
    lindex--;
    return lindex;
}


int largest_index_l(char* s, int k)
{
    int lindex = -1;
    for (int c=0, size=strlen(s); c<size; c++)
        if (s[k] < s[c])
            if (c > k)
                if (c > lindex)
                    lindex = c;
    
    return lindex;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int T = parse_int(ltrim(rtrim(readline())));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        char* w = readline();

        char* result = biggerIsGreater(w);

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
