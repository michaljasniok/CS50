#include <cs50.h>
#include <stdio.h>

void print_row(int i, int length);

int main(void)
{
    int height;
    do
    {
        height = get_int("what height:");
    }
    while (height < 1);
    int i = 0;
    for (i = 0; i < height; i++)
    {
        print_row(i + 1, height);
    }
}

void print_row(int rows, int length)
{
    int spaces = length - rows;
    while (spaces > 0)
    {
        printf(" ");
        spaces = spaces - 1;
    }

    for (int bricks = 0; bricks < rows; bricks++)
    {
        printf("#");
    }
    printf("\n");
}
