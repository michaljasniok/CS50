// librarys
#include <cs50.h>
#include <stdio.h>
#include <string.h>
// prototypes
int points_counter(string word);
int points;
// main
int main(void)
{
    string player_1_word = get_string("Player 1:");
    string player_2_word = get_string("Player 2:");
    points_counter(player_1_word);
    int points_1_word = points;
    points_counter(player_2_word);
    int points_2_word = points;
    if (points_1_word > points_2_word)
    {
        printf("Player 1 wins!");
    }
    else if (points_1_word < points_2_word)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}
// function that counts points
int points_counter(string word)
{
    points = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        char letter = word[i];
        if (letter == 'A' || letter == 'a')
        {
            points = points + 1;
        }
        else if (letter == 'B' || letter == 'b')
        {
            points = points + 3;
        }
        else if (letter == 'C' || letter == 'c')
        {
            points = points + 3;
        }
        else if (letter == 'D' || letter == 'd')
        {
            points = points + 2;
        }
        else if (letter == 'E' || letter == 'e')
        {
            points = points + 1;
        }
        else if (letter == 'F' || letter == 'f')
        {
            points = points + 4;
        }
        else if (letter == 'G' || letter == 'g')
        {
            points = points + 2;
        }
        else if (letter == 'H' || letter == 'h')
        {
            points = points + 4;
        }
        else if (letter == 'I' || letter == 'i')
        {
            points = points + 1;
        }
        else if (letter == 'J' || letter == 'j')
        {
            points = points + 8;
        }
        else if (letter == 'K' || letter == 'k')
        {
            points = points + 5;
        }
        else if (letter == 'L' || letter == 'l')
        {
            points = points + 1;
        }
        else if (letter == 'M' || letter == 'm')
        {
            points = points + 3;
        }
        else if (letter == 'N' || letter == 'n')
        {
            points = points + 1;
        }
        else if (letter == 'O' || letter == 'o')
        {
            points = points + 1;
        }
        else if (letter == 'P' || letter == 'p')
        {
            points = points + 3;
        }
        else if (letter == 'Q' || letter == 'q')
        {
            points = points + 10;
        }
        else if (letter == 'R' || letter == 'r')
        {
            points = points + 1;
        }
        else if (letter == 'S' || letter == 's')
        {
            points = points + 1;
        }
        else if (letter == 'T' || letter == 't')
        {
            points = points + 1;
        }
        else if (letter == 'U' || letter == 'u')
        {
            points = points + 1;
        }
        else if (letter == 'V' || letter == 'v')
        {
            points = points + 4;
        }
        else if (letter == 'W' || letter == 'w')
        {
            points = points + 4;
        }
        else if (letter == 'X' || letter == 'x')
        {
            points = points + 8;
        }
        else if (letter == 'Y' || letter == 'y')
        {
            points = points + 4;
        }
        else if (letter == 'Z' || letter == 'z')
        {
            points = points + 10;
        }
        else
        {
            points = points + 0;
        }
    }
    return (points);
}
