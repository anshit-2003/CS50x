#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : ./recover card");
        return 1;
    }
    //Opeaning card.raw
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 2;
    }
    //Buffer For storing data
    BYTE buffer[512];
    //counter for jpgs
    int count = 0;
    char filename[8];
    int is_jpg = 0;
    //File for making jpgs
    FILE *jpg = NULL;

    while (fread(buffer, 512, 1, card) == 1)
    {
        //Checking for header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (is_jpg == 1)
            {
                fclose(jpg);
            }
            else
            {
                is_jpg = 1;
            }
            //Making and giving file a new name
            sprintf(filename, "%03i.jpg", count);
            jpg = fopen(filename, "w");
            count++;
        }
        if (is_jpg == 1)
        {
            //Writing data to the jpg file
            fwrite(buffer, 512, 1, jpg);
        }

    }
    fclose(jpg);
    fclose(card);
}