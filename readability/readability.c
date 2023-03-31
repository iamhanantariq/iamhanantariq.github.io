#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sen(string text);

int main(void)
{
    string text = get_string("Text: "); //get text into
    printf("Text: %s\n", text);

    int c = count_letters(text); //call function for counting letters
    printf("Letters %i\n", c);

    int w = count_words(text); //call function to count words
    printf("Words %i\n", w);

    int s = count_sen(text); //call function to count sentences
    printf("Sentences %i\n", s);

    int index = round(0.0588 * c / w * 100 - 0.296 * s / w * 100 - 15.8); //index formula
    if (index > 15)
    {
        printf("Grade 16+\n"); //if too high
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n"); // if too low
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

int count_letters(string text) //count letters
{
    int letters = 0;
    // loop for this
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 65 && text [i] <= 90)
        {
            letters++;
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text) // word counter function
{
    int words = 0;
    // loop for this
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            words++;
        }
        else if (text[i + 1] == 0)
        {
            words++;
        }
    }
    return words;
}

int count_sen(string text) //function for sentences
{
    int sen = 0;
    //loopy
    for (int i = 0, n = strlen(text); i < n; i++)
    {
       if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sen++;
        }
    }
    return sen;
}