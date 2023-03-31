#include <cs50.h>
#include <stdio.h>

long get_ccnumber(void);
int get_valid(long number);

int main(void)
{
    // formulas to determine card validity
  long number = get_ccnumber();
  int type = get_valid(number);

  //print differnt results based on card type

  if (type == 1)
  {
        printf("VISA\n");
  }
  else if (type == 2)
  {
        printf("MASTERCARD\n");
  }
   else if (type == 3)
  {
        printf("AMEX\n");
  }
   else
  {
        printf("INVALID\n");
  }

}

long get_ccnumber(void)
{
    long n = get_long("Number: ");
    return n;
}
// function to confirm type and use luhn method
int get_valid(long number)
{
    // 1=visa , 2=MC, 3=amex, 4=invalid
    int card, i;
    long n, r, x, f, s, sum;
    //check visa
    if (number / 1000000000000000 == 4)
    {
        n = number;
        s = 0;
        f = 0;
        for (i = 1; i <= 8; i++)
        {
            s = s + n % 10;
            n = n / 10;
            r = n % 10;
            n = n / 10;
            x = r * 2;
            f = f + x / 10 + x % 10;
        }
        sum = s + f;
        if (sum % 10 == 0)
        {
            card = 1;
        }
        else
        {
            card = 4;
        }
    }
    else if (number / 1000000000000 == 4)
    {
        n = number;
        s = 0;
        f = 0;
        for (i = 1; i <= 7; i++)
        {
            s = s + n % 10;
            n = n / 10;
            r = n % 10;
            n = n / 10;
            x = r * 2;
            f = f + x / 10 + x % 10;
        }
        sum = s + f;
        if (sum % 10 == 0)
        {
            card = 1;
        }
        else
        {
            card = 4;
        }
    }
    //check MC
    else if (number / 100000000000000 >= 51 && number / 100000000000000 <= 55)
    {
        n = number;
        s = 0;
        f = 0;
        for (i = 1; i <= 8; i++)
        {
            s = s + n % 10;
            n = n / 10;
            r = n % 10;
            n = n / 10;
            x = r * 2;
            f = f + x / 10 + x % 10;
        }
        sum = s + f;
        if (sum % 10 == 0)
        {
            card = 2;
        }
        else
        {
            card = 4;
        }
    }
    //check amex
    else if (number / 10000000000000 == 34 || number / 10000000000000 == 37)
    {
        n = number;
        s = 0;
        f = 0;
        for (i = 1; i <= 8; i++)
        {
            s = s + n % 10;
            n = n / 10;
            r = n % 10;
            n = n / 10;
            x = r * 2;
            f = f + x / 10 + x % 10;
        }
        sum = s + f;
        if (sum % 10 == 0)
        {
            card = 3;
        }
        else
        {
            card = 4;
        }
    }
    //invalid all else
    else
    {
        card = 4;
    }
    return card;
}