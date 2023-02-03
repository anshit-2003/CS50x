#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

char encrypt(char c, int k);
bool only_digits(string text);
int main(int argc, string argv[])
{
    //Rejects if given more than 2 command line argument
    if (argc > 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
    //Rejects if given less than 2 command line arguments

    else if (argc <= 1)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
    else
    {
        if (only_digits(argv[1]) == true)
        {
            //Atoi function converts the string argument to int
            int key = atoi(argv[1]);
            string text = get_string("plaintext:  ");
            int len = strlen(text);
            printf("ciphertext: ");
            //Loop to print the encrypted text
            for (int i = 0 ; i < len ; i++)
            {
                printf("%c", encrypt(text[i], key));
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Usage: ./caeser key\n");
            return 1;
        }
    }

}
//Function to check if the argument only contains digits or not
bool only_digits(string text)
{
    int len = strlen(text);
    for (int i = 0 ; i < len ; i++)
    {
        if (text[i] < 48 || text[i] > 57)
        {
            return false;
        }
    }
    return true;


}
//Function to encrypt the plain text inputted by the user
char encrypt(char character, int key)
{
    if (character >= 65 && character <= 90)
    {
        //To Treat A as 0 , B as 1 and as follows subtracting the ascii value of A from the text
        int ascii = (int) character - 65;
        int converted = (ascii + key) % 26;
        return (char) converted + 65;

    }
    else if (character >= 97 && character <= 122)
    {
        int ascii = (int) character - 97;
        int converted = (ascii + key) % 26;
        return (char) converted + 97;
    }
    else
    {
        return character;
    }
}
