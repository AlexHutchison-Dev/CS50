#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover filename\n");
        return 1;
    }

    int filenumber = 0;

    //remember infile name
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //declare out file and place to store name
    FILE *outptr;
    char outfile[10];

    // declare buffer of length 512 bytes
    unsigned char buffer[512];

    //Declare variables for infile and to store file number
    bool filestarted = false;
    size_t bytesread = 0;
    //while blocks read are full 512 bytes
    while (true)
    {

        bytesread = fread(buffer, 1, 512, inptr);

        if (bytesread != 512)
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (filestarted)
            {
                filenumber++;
                fclose(outptr);

                sprintf(outfile, "%03i%s", filenumber, ".jpg");

                // open output file
                outptr = fopen(outfile, "w");

                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", outfile);
                    return 3;
                }

                fwrite(buffer, 1, 512, outptr);

            }

            else if (!filestarted)
            {

                sprintf(outfile, "%03i%s", filenumber, ".jpg");

                // open output file
                outptr = fopen(outfile, "w");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", outfile);
                    return 3;
                }


                //write 512 bytes to file

                fwrite(buffer, 1, 512, outptr);
                filestarted = true;
            }



        }

        else if (filestarted)
        {
            fwrite(buffer, 1, 512, outptr);

        }
        else
        {
            continue;
        }

    }


    //print final block and close both

    fwrite(buffer, 1, bytesread, outptr);

    //close files and return 0
    filenumber++;
    fclose(inptr);
    fclose(outptr);
    return 0;

}
