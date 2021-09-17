#include "/home/prayag/Codes/Exercise/HackerRank/libs.c"

int mostBalancedPartition(int parent_count, int* parent, int files_size_count, int* files_size);

int main (void)
{
    int parent[4] = {-1, 0, 1, 2};
    int file_size[4] = {1, 4, 3, 4};
    int c = mostBalancedPartition(4, parent, 4, file_size);
    printf("Expected Output: 2\nYour Output: %i\n\n", c);


    int parent1[4] = {-1, 0, 0, 0};
    int file_size1[4] = {10, 11, 10, 10};
    c = mostBalancedPartition(4, parent1, 4, file_size1);
    printf("Expected Output: 19\nYour Output: %i\n\n", c);





    printf("parent_count: %i\n", 4);
}

int mostBalancedPartition(int parent_count, int* parent, int files_size_count, int* files_size)
{
    return 0;

}