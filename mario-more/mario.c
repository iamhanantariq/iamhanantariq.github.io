#include <cs50.h>
#include <stdio.h>

int main(void)
{
int i, j, x, h;
//this loop gets the required height
do
{
   h = get_int("Height: ");
}
while(h < 1 || h > 8);

//embedded for loops for building bricks
    for (i=1; i <= h; i++)
    {
    for (j = 1; j <= h-i; j++)
    {
        printf(" ");
    }
    for(x=1; x<=i; x++)
    {
       //for adding left blocks
        printf("#");
    }
    printf("  ");
     for(x=1; x<=i; x++)
    {
      //for adding right blocks
        printf("#");
    }
    printf("\n");
    }
}