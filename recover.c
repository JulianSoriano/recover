//include header files from these libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////

//variables

//create an unsigned char called buffer to represent a block of 512 Bytes
unsigned char buffer[512];

//File to represent the memory card
FILE *card;

//File to represent the image
FILE *image;

//char to represent the new image name
char imagename[7];

//create an int called imagecounter to represent current image count
int imagecounter = 0;

//create a bool switch to represent when the program is writing
bool writingmode = false;

/////////////////////////////////////////////////////////////////////////

//Main body of code
int main(int argc, char *argv[])
{

    //command line check:

    //if it doesn't equal 2
    if (argc != 2)
    {
        //tell user cmd line is incorrect
        printf("Command line is incorrect\n");

        //return an error
        return 1;
    }

    /////////////////////////////////////////////////////////////////////

    //open memory card in read mode:
    card = fopen(argv[1], "r");

    //read the memory card
    while (fread(buffer, 512, 1, card) > 0)
    {

        ////////////////////////////////////////////////////////////

        //look for a JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {

                //create a new jpg and give it the proper name

                //Filenames: ###.jpg, starting at 000.jpg
                sprintf(imagename, "%03i.jpg", imagecounter);
                printf("creating image name\n");

                //imagecounter +1
                imagecounter++;

                //use fopen in write mode on imagename to make your image file
                image = fopen(imagename, "w");

                //turn writing mode on
                writingmode = true;

                //fwrite(data, size, number, outptr);
                fwrite(buffer, 512, 1, image);
            }
        }

        //otherwise keep writing
        else if (writingmode == true)
        {
            //fwrite(data, size, number, outptr);
            fwrite(buffer, 512, 1, image);
        }
    }

    ////////////////////////////////////////////////////////////////

    //if you encounter another jpg header
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
    {
        //close the image
        fclose(image);
    }

    ////////////////////////////////////////////////////////////////

    //close memory card
    fclose(card);
}
