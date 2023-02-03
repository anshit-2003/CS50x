#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include <ctype.h>

char encrypt(string key , char text);
int main(int argc, string argv[])
{
    if (argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (argc <=1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int len = strlen(argv[1]);
    if (len < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string text = get_string("plaintext:  ");
    int len2 = strlen(text);
    printf("ciphertext: ");
    for(int i = 0 ; i < len ; i++)
    {
        printf("%c",encrypt(argv[1] , text[i]));
    }
    printf("\n");

}
char encrypt(string key , char ch)
{
    if(islower(ch))
    {
        int ascii = (int) ch;
        int index = ascii - 65;
        return tolower(key[index]);

    }
    else if(isupper(ch))
    {
        int ascii = (int) ch;
        int index = ascii - 97;
        return toupper(key[index]);


    }
    else
    {
        return ch;

    }

}