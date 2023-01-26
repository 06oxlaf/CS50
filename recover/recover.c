#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
 if(argc < 2 || argc > 2)
 {
    printf("Usage: ./recover IMAGE/n");
    return 1;
 }
//open memory card
FILE *f = fopen(argv[1], "r");
//repeat until end of card:
    //read 512 bytes into bufffer
    //if start of new JPEG
        //if first JPEG
            //write to file
        //else
            //close and open new file
    //else
        //if alreadyfound keep going
    //close remaining files

//look for JPEG
if (f== NULL)
{
    printf("Could not open file");
    return 2;
}
int BLOCK_SIZE = 512;
BYTE buffer[BLOCK_SIZE];
int n = 0;
char imagefile[8];
FILE *img = NULL;
while (fread(buffer, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        if (n == 0)
        {
            //Open new Jpeg
            sprintf(imagefile, "%03i.jpg", n);
            img = fopen(imagefile, "w");
            //write bytes until a new jpeg is found
            fwrite(buffer, 1, BLOCK_SIZE,  img);
            n = n + 1;
        }
        else
        {
            //Open new Jpeg
            fclose(img);
            //Open new Jpeg
            sprintf(imagefile, "%03i.jpg", n);
            img = fopen(imagefile, "w");
            //write bytes until a new jpeg is found
            fwrite(buffer, 1, BLOCK_SIZE, img);
            n = n + 1;
        }
    }
    else
    {
        if (n != 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

}
fclose(img);
fclose(f);
}
