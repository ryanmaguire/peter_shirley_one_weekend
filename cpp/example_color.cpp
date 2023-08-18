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
 *                                                                            *
 *      This file presents a basic struct used to represent colors.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  fputc is found here.                                                      */
#include <cstdio>

/*  Color struct found here.                                                  */
#include "psow_color.hpp"

/*  Function for testing the color struct defined above.                      */
int main(void)
{
    /*  We'll output the colors to a PPM file. Create and open with fopen.    */
    FILE *fp = std::fopen("simple_color_example.ppm", "w");

    /*  The file will be 1024x1024 pixels. Store this value in "size".        */
    unsigned int size = 1024U;

    /*  Two variables for indexing over the pixels of the PPM file.           */
    unsigned int x, y;

    /*  Values for the red and green components of a given color.             */
    unsigned char r, g;

    /*  This factor will be used to create a gradient in color across the PPM.*/
    double factor = 255.0 / static_cast<double>(size - 1U);

    /*  Declare a psow::color to use for the computation.                     */
    psow::color c;

    /*  If fopen failed, it returns NULL. Check if this happened.             */
    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Write the preamble to the PPM file.                                   */
    std::fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  Loop over the pixels of the PPM and compute the colors.               */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  The red and green values will be a gradient across the image. */
            r = static_cast<unsigned char>(static_cast<double>(x) * factor);
            g = static_cast<unsigned char>(static_cast<double>(y) * factor);

            /*  Use the constructor to create the color from these values.    */
            c = psow::color(r, g, 64U);

            /*  Use the write method to write this color to the PPM file.     */
            c.write(fp);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    std::fclose(fp);
    return 0;
}
/*  End of main.                                                              */

