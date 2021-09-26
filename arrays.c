#include "/home/prayag/Codes/Exercise/HackerRank/libs.c"

typedef struct int_array
{
    int *numbers;
    int count;
} int_array;

void int_array_add(int_array*, int);
int_array* get_int_array(void);
void int_array_print(int_array*);
void int_array_free(int_array*);
int int_array_length(int_array*);
void int_array_remove(int_array*, int);


int main (void)
{
    printf("Count: ");
    int c = get_int(), n;
    int_array *a = get_int_array();
    for (int x=0; x<c; x++)
    {
        n = get_int();
        int_array_add(a, n);
    }
    int_array_print(a);
    printf("Length: %i\n", int_array_length(a));
    int z = 0;
    while(z != -100)
    {
        printf("Item to remove: ");
        z = get_int();
        int_array_remove(a, z);
        int_array_print(a);
    }
    int_array_free(a);
}

int_array* get_int_array(void)
{
    int_array *c = malloc(sizeof(int_array));
    (*c).numbers = NULL;
    (*c).count = 0;
    return c;
}


void int_array_add(int_array* a, int c)
{
    (*a).numbers = realloc((*a).numbers, sizeof(int)*(((*a).count) + 1));
    int x = (*a).count;
    (*a).numbers[x] = c;
    (*a).count++;
    return;
}


void int_array_print(int_array* a)
{
    if ((*a).numbers == NULL || (*a).count == 0)
    {
        printf("[]\n");
        return;
    }
        
    int count = (*a).count;
    printf("[");
    for (int c=0; c<count; c++)
    {
        if (c == count - 1)
            printf("%i]\n", (*a).numbers[c]);
        else
            printf("%i, ", (*a).numbers[c]);
    }
}


void int_array_free(int_array *a)
{
    free((*a).numbers);
    free(a);
    return;
}


int int_array_length(int_array *a)
{
    return (*a).count;
}


void int_array_remove(int_array *a, int c)
{
    if ((*a).numbers == NULL || (*a).count == 0)
        return;
    int count = (*a).count, x;
    if (count == 1 && (*a).numbers[0] == c)
    {
        free((*a).numbers);
        (*a).numbers = NULL;
        (*a).count = 0;
        return;
    }

    for (x=0; x<count; x++)
        if ((*a).numbers[x] == c)
            break;
    
    if (x == count)
        return;
    
    int *z = malloc(sizeof(int)*(count-1));
    int i;
    for (i=0; i<x; i++)
        z[i] = (*a).numbers[i];
    
    for (int j=i+1; j<count; j++)
        z[j-1] = (*a).numbers[j];
    
    free((*a).numbers);
    (*a).numbers = z;
    (*a).count--;
    return;
}