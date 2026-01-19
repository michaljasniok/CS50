// libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// prototypes
string caesar (string word, int key);
string ciphertext;
// main
int main (int argc, string argv[])
{
    // if exacly one argument then proceed
    if (argc == 2)
    {
        int length = strlen(argv[1]);
        string word = argv[1];
        // check if all letters are numbers
        for (int i = 0; i < length;)
        {
            char letter = word[i];
            if (letter >= '0' && letter <= '9')
            {
                i++;
            }
            else
            {
                printf("Usage: ./caesar key \n ");
                return(1);
            }
        }
        // convert string key to int key
        int key = atoi(word);
        string plaintext = get_string("plaintext: ");
        caesar(plaintext, key);
        printf("plaintext: %s\n", plaintext);
        printf("ciphertext: %s\n", ciphertext);
        free(ciphertext);
    }
    else
    {
        printf("Usage: ./caesar key \n ");
        return(1);
    }
}
// function to rotate letters
string caesar (string word, int key)
{
    int length = strlen(word);
    ciphertext = malloc(length + 1);
    // take letter do some math and return to main
    for (int i = 0; i < length; i++)
    {
        char letter = word[i];
        if (letter >= 'A' && letter <= 'Z')
        {
            ciphertext[i] = ((letter - 'A' + key) % 26) + 'A';
        }
        else if (letter >= 'a' && letter <= 'z')
        {
            ciphertext[i] = ((letter - 'a' + key) % 26) + 'a';
        }
        else
        {
            ciphertext[i] = letter;
        }
    }
    ciphertext[length] = '\0';
    return(ciphertext);
}
