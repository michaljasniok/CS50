// libralies needed for this program to work
#include <cs50.h>
#include <stdio.h>
// prototypes of functions
void company(int last_number, int second_last_number, long card_num);
void luhn_algorithm(long card_number);
// main function
int main(void)
{
    long card_number;
    do
    {
        card_number = get_long("What number:");
    }
    while (card_number < 1000000000);
    if (card_number > 1000000000000)
    {
        luhn_algorithm(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}
// prints company name
void company(int last_number, int second_last_number, long card_num)
{
    if (last_number == 4)
    {
        if (card_num > 1000000000000 && (card_num < 10000000000000 || card_num > 1000000000000000))
       {
        printf("VISA");
        printf("\n");
       }
       else
       {
        printf("INVALID\n");
       }
    }
    else if (last_number == 3 && (second_last_number == 4 || second_last_number == 7))
    {
        if (card_num > 100000000000000 && card_num < 1000000000000000)
        {
            printf("AMEX");
            printf("\n");
        }
        else
        {
            printf("INVALID");
            printf("\n");
        }
    }
    else if (last_number == 5 && (second_last_number == 1 || second_last_number == 2 || second_last_number == 3 || second_last_number == 4 || second_last_number == 5))
    {
        printf("MASTERCARD");
        printf("\n");
    }
    else
    {
        printf("INVALID");
        printf("\n");
    }
}
// does luhn algorithm
void luhn_algorithm(long card_number)
{
    int global_sum = 0;
    int underlined_number;
    int not_underlined_number;
    int underlined_over_ten;
    long card_num = card_number;
    int last;
    int last_set;
    int second_last;
    int second_last_set;
    int i = 0;
    for (i = 0; card_number > 10; i++)
    {
        not_underlined_number = card_number % 10;
        card_number = card_number / 10;
        underlined_number = (card_number % 10) * 2;
        if (underlined_number >= 10)
        {
            underlined_over_ten = underlined_number ;
            underlined_number = (((card_number % 10) * 2) - (underlined_number % 10)) / 10 + underlined_over_ten % 10;
            if (card_number <= 99 && card_number > 9)
            {
                 second_last = underlined_over_ten / 2;
                 second_last_set = 1;
            }
            if (card_number <= 10)
            {
                     last = underlined_over_ten / 2;
                     last_set = 1;
            }
        }
        card_number = card_number / 10;
        global_sum = global_sum + not_underlined_number + underlined_number;
    }
    if (i != 8)
    {
        not_underlined_number = card_number % 10;
        global_sum = global_sum + not_underlined_number;
    }
    if (global_sum % 10 == 0)
    {
        if (i == 8)
        {
            if (last_set == 1)
            {
                company(last, not_underlined_number, card_num);
            }
            else if (second_last_set == 1)
            {
                company(underlined_number / 2, second_last, card_num);
            }
            else
            {
                company(underlined_number / 2, not_underlined_number, card_num);
            }
        }
        else
        {
            if (last_set == 1)
            {
                company(last, not_underlined_number, card_num);
            }
            else if (second_last_set == 1)
            {
                company(not_underlined_number, second_last, card_num);
            }
            else
            {
                company(not_underlined_number, underlined_number / 2, card_num);
            }
        }
    }
    else
    {
        printf("INVALID");
        printf("\n");
    }
}
