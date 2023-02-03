#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include <math.h>

int count_sentences(string text);
int count_letters(string text);
int count_words(string text);
int main(void)
{
    string text = get_string("Text : ");
    float words = count_words(text);
    float letters = count_letters(text);
    float sentences = count_sentences(text);
    //Statement to calculate average letter per words
    float L = (letters / words) * 100;
    //Statement to calculare average sentences per words
    float S = (sentences / words) * 100;
    //Statement to calculate the index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    //Conditions to assign Grade
    if ((int)index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int) round(index) >= 1 && (int) round(index) <= 16)

    {
        printf("Grade %d\n", (int) round(index));
    }
    else
    {
        printf("Grade 16+\n");
    }
}
//Function to count the number of words
int count_words(string text)
{
    int words = 0, len = strlen(text);
    for (int i = 0 ; i < (len + 1) ; i++)
    {
        if (text[i] == '\0' || text[i] == 32)
        {
            words++;
        }

    }
    return words;
}
//Function to count the letters in the given text
int count_letters(string text)
{
    int letters = 0, len = strlen(text);
    for (int i = 0 ; i < len ; i++)
    {
        if ((text[i] >= 65  && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
    }
    return letters;

}
//Function to count the number of sentences
int count_sentences(string text)
{
    int sentences = 0 ;
    int len = strlen(text);
    for (int i = 0 ; i < len ; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}