// libraries
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// prototypes
string mapping_and_encrypting(string word, string key);
string ciphertext;
// main
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // checks if argument has 26 letters
        int length = strlen(argv[1]);
        if (length == 26)
        {
            char letter;
            string key = argv[1];
            int seen[26] = {0};
            for (int i = 0; i < 26;)
            {
                letter = key[i];
                if (letter >= 'a' && letter <= 'z')
                {
                    seen[(int) letter - 'a'] = seen[(int) letter - 'a'] + 1;
                    if (seen[(int) letter - 'a'] == 2)
                    {
                        printf("Double letter");
                        return (1);
                    }
                    else
                    {
                        i++;
                    }
                }
                else if (letter >= 'A' && letter <= 'Z')
                {
                    seen[(int) letter - 'A'] = seen[(int) letter - 'A'] + 1;
                    if (seen[(int) letter - 'A'] == 2)
                    {
                        printf("Double letter");
                        return (1);
                    }
                    else
                    {
                        i++;
                    }
                }
                else
                {
                    printf("Key must be letters");
                    return (1);
                }
            }
            string word = get_string("plaintext: ");
            mapping_and_encrypting(word, key);
            printf("ciphertext: %s\n", ciphertext);
            free(ciphertext);
            return (0);
        }
        else
        {
            printf("Key must contain 26 characters");
            return (1);
        }
    }
    else
    {
        printf("Usage: ./substitution key");
        return (1);
    }
}
// function that map alphabet
string mapping_and_encrypting(string word, string key)
{
    int length_word = strlen(word);
    ciphertext = malloc(length_word + 1);
    char letter;
    // takes letters from plaintext uses key to encrypt it then adds to ciphertext
    for (int z = 0; z < length_word; z++)
    {
        letter = word[z];
        if (letter >= 'a' && letter <= 'z')
        {
            letter = letter - 'a';
            ciphertext[z] = tolower(key[(int) letter]);
        }
        else if (letter >= 'A' && letter <= 'Z')
        {
            letter = letter - 'A';
            ciphertext[z] = toupper(key[(int) letter]);
        }
        else
        {
            ciphertext[z] = letter;
        }
    }
    ciphertext[length_word] = '\0';
    return (ciphertext);
}
