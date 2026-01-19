// imports needed libralies
#include <cs50.h>
#include <stdio.h>
// defined magic numbers
#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1
// prototypes of function
void calculate_coins(int change);
// main function executes program
int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 1);
    calculate_coins(change);
}
// calculate how many coins are needed
void calculate_coins(int remaining_change)
{
    int coin_count = 0;
    int cents[4] = {QUARTER, DIME, NICKEL, PENNY};
    for (int i = 0; i < 4; i++)
    {
        int coin = cents[i];
        while (coin <= remaining_change)
        {
            remaining_change = remaining_change - coin;
            coin_count++;
        }
    }
    printf("%i", coin_count);
    printf("\n");
}
