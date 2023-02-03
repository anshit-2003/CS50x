#include<stdio.h>
#include<cs50.h>

int main(void)
{
    //This statement will ask for your name
    string name = get_string("What is your name? ");
    //This statement will produce the desired output
    printf("hello, %s\n", name);
}