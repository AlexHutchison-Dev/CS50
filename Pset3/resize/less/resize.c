// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n  infile outfile\n");
        return 1;
    }

    // remember filenames and resize factor
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // Check for valid input
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Usage: resize n  infile outfile\n");
        fprintf(stderr, "n must be a positive interger less than or equal to 100\n");
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inbf;
    fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inbi;
    fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 ||
        inbi.biBitCount != 24 || inbi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Calculate infile padding for cursor offset on infile scanlines
    int infpadding = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;



    BITMAPFILEHEADER outbf;
    BITMAPINFOHEADER outbi;
    outbf = inbf;
    outbi = inbi;

    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

 // Recalculate height and width for new size
    outbi.biWidth = inbi.biWidth * n;
    outbi.biHeight = abs(inbi.biHeight) * n;

    // Calculate outfile padding with new height and width
    int padding = (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

 // Calculate new image size and file size
    outbi.biSizeImage = ((sizeof(RGBTRIPLE) * outbi.biWidth) + padding) * abs(outbi.biHeight);
    outbf.bfSize = outbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    long lineStart = 0;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inbi.biHeight); i < biHeight; i++)
    {
        //repeat line n times
        for(int k = 0; k < n; k++)
        {

            if(k == 0)
                {
                    lineStart = ftell(inptr);

                }
            // iterate over pixels in scanline
            for (int j = 0; j < inbi.biWidth; j++)
            {
                    //Add for loop to iterate over this line n times
                    // will need to SEEK_CUR and keep position of cursor for begining of this line to come back to n times //
               // if(j == 0)
                //{
                //    lineStart = ftell(inptr);
                //}

                  // temporary storage
                    RGBTRIPLE triple;
                     // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                 for(int m = 0; m < n; m++)
                {

                   // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                }

                        for (int l = 0; l < padding; l++)
                        {
                            fputc(0x00, outptr);
                        }
                        long offset = sizeof(RGBTRIPLE) *  outbi.biWidth + (0x00 * padding);
                        fseek(inptr, - offset, SEEK_CUR);

            }
                                fseek(inptr, infpadding * 0x00, SEEK_CUR);


        }
        // skip over padding, if any



    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
