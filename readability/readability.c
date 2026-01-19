// libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//prototypes
void grader(string text);
int letter_count;
int sentence_count;
int word_count;
// main
int main(void)
{
    string text = get_string("Text:");
    grader(text);
     // printf("%i\n%i\n%i", letter_count, word_count, sentence_count);
    float L = (float)letter_count / word_count * 100;
    float S = (float)sentence_count / word_count * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",(int)round(index));
    }
}
// grades text
void grader(string text)
{
    int text_length = strlen(text);
    letter_count = 0;
    sentence_count = 0;
    word_count = 0;
    for (int i = 0; i < text_length; i++)
    {
        // sorts letters
        char letter = text[i];
        if (letter == ' ' || letter == '.' || letter == '!' || letter == '?')
        {
            // if . or ! or ? so an end of sentence then add 1 to sentence count
            if (letter == '.' || letter == '!' || letter == '?')
            {
                sentence_count++;
            }
            else
            {
                word_count++;
            }
        }
        // if its a letter like a,b,c then add 1 to letter count
    else if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z'))
    {
    letter_count++;
    }

    }
    word_count++;
}
