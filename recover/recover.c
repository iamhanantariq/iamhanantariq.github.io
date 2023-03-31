#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE; //define byte

int main(int argc, char *argv[])
{
    if (argc != 2) //only 1 submission for key
    {
        printf("Error, enter 1 key\n");
        return 1;
    }

    // Open raw file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //initialize a few things
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int filenum = 0;
    char filename[8];
    FILE *img;

    //read loop for each 512 block
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //check if start of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (filenum > 0) //close already openned file
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", filenum); //make new filename
            img = fopen(filename, "w"); //open new file
            fwrite(buffer, 1, BLOCK_SIZE, img); //write to it
            filenum++;
        }
        else if (filenum > 0) //keep writing if not
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    //close last file
    fclose(img);
    fclose(raw_file);
}