#include <cs50.h>
#include <stdio.h>

int get_height(void);
int main(void)
{
    int h = get_height();
    int i, j, k ;
    //For loop to print the pattern
    for (i = 1 ; i <= h ; i++)
    {
        //For loop to print the spaces
        for (k = 0 ; k < h - i  ; k++)
        {
            printf(" ");
        }
        //For loop to print #
        for (j = 0 ; j < i ; j++)
        {
            printf("#");
        }
        //Statement to move to next line
        printf("\n");

    }

}
//Function to take input
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}