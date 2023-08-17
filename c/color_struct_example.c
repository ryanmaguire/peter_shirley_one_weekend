/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is free software: you can redistribute it and/or modify         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This file is distributed in the hope that it will be useful,              *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with thie file.  If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This is part of a set of files I made while studying from Peter       *
 *      Shirley's "Ray Tracing in One Weekend", Copyright 2018-2020, Peter    *
 *      Shirley, All rights reserved. The code is my own, but follows the     *
 *      ideas laid out in the text.                                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  fputc is found here.                                                      */
#include <stdio.h>

/*  A color is an ordered triple (r, g, b) of the amount of red, green, and   *
 *  blue present in the color.                                                */
typedef struct psow_color_def {
    unsigned char red, green, blue;
} psow_color;

/*  Function for creating a color from three integers.                        */
static psow_color
psow_color_create(unsigned char r, unsigned char g, unsigned char b)
{
    psow_color out;

    /*  Simply set the individual components and return.                      */
    out.red   = r;
    out.green = g;
    out.blue  = b;
    return out;
}
/*  End of psow_color_create.                                                 */

/*  Function for adding colors without overflow.                              */
static psow_color
psow_color_add(psow_color C1, psow_color C2)
{
    /*  ISO C90 forbids mixed declarations with code. Declare all necessary   *
     *  variables at the top. We'll use unsigned int's to perform the         *
     *  computation to ensure we don't have an overflow. Since an unsigned    *
     *  int is required to be at LEAST 16 bits, these can easily handle       *
     *  addition with integers that are at most 8 bits (Unsigned char's can   *
     *  be larger than 8 bits, but the max value we allow in our computations *
     *  using colors is 255, so this doesn't matter. Even so, char's are      *
     *  almost universally always 8 bits).                                    */
    psow_color out;

    /*  Perform a type cast to unsigned short int and compute the sum of the  *
     *  two colors component-wise.                                            */
    const unsigned int x = (unsigned int)C1.red   + (unsigned int)C2.red;
    const unsigned int y = (unsigned int)C1.green + (unsigned int)C2.green;
    const unsigned int z = (unsigned int)C1.blue  + (unsigned int)C2.blue;

    /*  If the sum overflows (goes over 255), set the output value to 255.    */
    out.red = (x >= 255U ? 0xFFU : (unsigned char)x);
    out.green = (y >= 255U ? 0xFFU : (unsigned char)y);
    out.blue = (z >= 255U ? 0xFFU : (unsigned char)z);
    return out;
}
/*  End of psow_color_add.                                                    */

/*  Function for multiplying a color by a non-negative real number.           */
static psow_color psow_color_scale(psow_color C, double a)
{
    psow_color out;

    /*  Perform a typecast and multiply. Note, if the real number is negative,*
     *  or if the product goes over 255, we'll end up wrapping around.        */
    out.red = (unsigned char)(a * (double)C.red);
    out.green = (unsigned char)(a * (double)C.green);
    out.blue = (unsigned char)(a * (double)C.blue);
    return out;
}
/*  End of psow_color_scale.                                                  */

/*  Function for writing a psow_color to an output.                           */
static void psow_color_write(psow_color C, FILE *fp)
{
    fputc(C.red, fp);
    fputc(C.green, fp);
    fputc(C.blue, fp);
}
/*  End of psow_color_write.                                                  */

/*  Function for testing the color struct defined above.                      */
int main(void)
{
    /*  We'll output the colors to a PPM file. Create and open with fopen.    */
    FILE *fp = fopen("simple_color_example.ppm", "w");

    /*  The file will be 1024x1024 pixels. Store this value in "size".        */
    unsigned int size = 1024U;

    /*  Two variables for indexing over the pixels of the PPM file.           */
    unsigned int x, y;

    /*  Values for the red and green components of a given color.             */
    unsigned char r, g;

    /*  This factor will be used to create a gradient in color across the PPM.*/
    double factor = 255.0 / (double)(size - 1U);

    /*  Declare a psow_color to use for the computation.                      */
    psow_color c;

    /*  The blue part of our picture will be constant. Store this value.      */
    const psow_color dark_blue = {0U, 0U, 1U};

    /*  This is just to show how to use the psow_color_scale function. Scale  *
     *  the blue part by 64.0 so it is not too dark. (0, 0, 1) is essentialy  *
     *  the color black.                                                      */
    psow_color blue = psow_color_scale(dark_blue, 64.0);

    /*  If fopen failed, it returns NULL. Check if this happened.             */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Write the preamble to the PPM file.                                   */
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  Loop over the pixels of the PPM and compute the colors.               */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  The red and green values will be a gradient across the image. */
            r = (unsigned char)((double)x * factor);
            g = (unsigned char)((double)y * factor);

            /*  Create the color from the red and green parts and then add in *
             *  the blue part.                                                */
            c = psow_color_create(r, g, 0U);
            c = psow_color_add(c, blue);

            /*  Use the write method to write this color to the PPM file.     */
            psow_color_write(c, fp);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

