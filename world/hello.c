#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("what's is your name ");
    printf("hello, %s\n", name);
}
