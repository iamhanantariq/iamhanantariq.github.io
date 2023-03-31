#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <strings.h>

int get_cents(void);

int main(void)
{
    //asks for name
    //string name = get_string("What's your name? ");
    //prints name
    //printf("hello, %s\n", name);
    //int cents = get_cents();
    char ch = '\'';
    printf("%c\n%i\n%i\n%i\n",ch,ch,toupper(ch),strcasecmp("fo'o","foo"));
}


int get_cents(void)
{
    // TODO
    int i;
    do
    {
        i = get_int("Change owed ");
    }
    while(i < 0);
    return i;
}