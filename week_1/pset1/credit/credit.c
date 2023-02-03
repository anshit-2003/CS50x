#include<stdio.h>
#include<cs50.h>

void credit_name(long x);
int checksum(long x);
int main(void)
{
    long credit_number = get_long("Number : ");
    int z = checksum(credit_number);
    if ((z % 10) == 0)
    {
        credit_name(credit_number);
    }
    else
    {
        printf("INVALID\n");

    }
}

int checksum(long x)
{
    int even_digit, odd_digit, sum1 = 0, sum2 = 0;
    while (x > 0)
    {
        odd_digit = x % 10;
        x = x / 10;
        sum1 = sum1 + odd_digit;
        even_digit = x % 10;
        x = x / 10;
        even_digit = even_digit * 2;
        if ((even_digit / 10)  != 0)
        {
            for (int i = 0 ; i < 2 ; i++)
            {
                sum2 = sum2 + (even_digit % 10);
                even_digit = even_digit / 10;
            }
        }
        else if ((even_digit / 10) == 0)
        {
            sum2 = sum2 + even_digit;

        }
    }
    return sum1 + sum2;
}

void credit_name(long x)
{

    if ((x > 340000000000000 && x < 349999999999999) || (x > 370000000000000 && x < 3799999999999999))
    {
        printf("AMEX\n");
    }
    else if ((x > 4000000000000 && x < 4999999999999) || (x > 4000000000000000 && x < 4999999999999999))
    {
        printf("VISA\n");
    }
    else if (x > 5100000000000000 && x < 5599999999999999)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}