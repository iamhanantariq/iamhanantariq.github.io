#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) //only 1 submission for key
    {
        printf("Error, enter 1 key\n");
        return 1;
    }

    int n = strlen(argv[1]);
    string key = argv[1];

    if (n != 26) //key 26 letters
    {
        printf("Error, incorrect key length\n");
        return 1;
    }

    for (int i = 0; i < n; i++) //outer loop
    {
        if (key[i] < 65 || key[i] > 122 || (key[i] > 90 && key[i] < 97)) //not not a letter
        {
            printf("Error, incorrect characters\n");
            return 1;
        }

        for (int j = 0; j < n; j++) //inner loop for checking duplication
        {
            if (key[i] == key[j] && i != j)
            {
                printf("Error, use 26 unique letters\n");
                return 1;
            }
        }
    }
    string text = get_string("plaintext:"); //Ask for text to encrpt
    //declarations
    int m = strlen(text);
    string ciper = text;
    char uppertext[m + 1];

    for (int i = 0; i < m; i++) //loop for each letter to cipher
    {
        uppertext[i] = toupper(text[i]); //upper letter
        if (text[i] < 65 || text[i] > 122 || (text[i] > 90 && text[i] < 97)) //other characters
        {
            ciper[i] = text[i];
        }
    //upper letters
    else if (isupper(text[i]))
    {
        ciper[i] = toupper(key[(uppertext[i] - 65)]);
    }
    else
    {
        ciper[i] = tolower(key[(uppertext[i] - 65)]); //lower letters
    }
    }
    printf("ciphertext:%s\n", ciper); //print ciper text
    return 0; //return
}