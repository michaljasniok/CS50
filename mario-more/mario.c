// imports fetures like printf or get_int
#include <cs50.h>
#include <stdio.h>
// prototypes of functions
void printing_left(int row);
void spaces(int length, int row);
void spaces_in_between(void);
void printing_right(int row);
void next_line(void);
// executes
int main(void)
{
    int height;
    do
    {
        height = get_int("what height: ");
    }
    while (height < 1 || height > 9);

    for (int row = 0; row < height; row++)
    {
        spaces(height, row + 1);
        printing_left(row + 1);
        spaces_in_between();
        printing_right(row + 1);
        next_line();
    }
}
// prints spaces for left piramid
void spaces(int length, int row)
{
    for (int spaces = length - row; spaces > 0; spaces--)
    {
        printf(" ");
    }
}

// prints left piramid
void printing_left(int row)
{
    for (int done = 0; done < row; done++)
    {
        printf("#");
    }
}
// prints spaces between piramids
void spaces_in_between(void)
{
    printf("  ");
}
// prints right piramid
void printing_right(int row)
{
    for (int done = 0; done < row; done++)
    {
        printf("#");
    }
}
// go to next line
void next_line(void)
{
    printf("\n");
}
