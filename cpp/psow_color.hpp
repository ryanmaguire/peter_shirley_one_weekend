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
 *      Provides a struct for working with colors.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 17, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef PSOW_COLOR_HPP
#define PSOW_COLOR_HPP

/*  The C++ equivalent of math.h. sqrt is found here.                         */
#include <cmath>

/*  And the equivalent of stdio.h.                                            */
#include <cstdio>

/*  Namespace for the project. "Peter-Shirley-One-Weekend."                   */
namespace psow {

    /*  A color is an ordered triple (r, g, b) of the amount of red, green,   *
     *  and blue present in the color.                                        */
    struct color {
        unsigned char red, green, blue;

        /*  Empty constructor.                                                */
        color(void)
        {
            return;
        }

        /*  Constructor from three values, RGB.                               */
        color(unsigned char r, unsigned char g, unsigned char b)
        {
            red   = r;
            green = g;
            blue  = b;
        }

        /*  Operator for adding colors.                                       */
        color operator + (color r)
        {
            /*  To avoid an arithmetic overflow with unsigned char's, compute *
             *  the sum using unsigned int's. Unsigned int's are required to  *
             *  be least 16 bits in the C-standard, and I imagine the same    *
             *  would apply in C++. Since our colors are represented by 8-bit *
             *  numbers (char can be larger than 8-bit, but is required to be *
             *  at least 8 bits, and we only want values 0 to 255, which is   *
             *  8-bit), if we use unsigned int's to perform the addition, we  *
             *  are guaranteed to NOT get an overflow, which is useful.       */
            unsigned char out_red, out_green, out_blue;

            /*  Cast to unsigned int's and compute the sum.                   */
            const unsigned int x = static_cast<unsigned int>(r.red) +
                                   static_cast<unsigned int>(red);
            const unsigned int y = static_cast<unsigned int>(r.green) +
                                   static_cast<unsigned int>(green);
            const unsigned int z = static_cast<unsigned int>(r.blue) +
                                   static_cast<unsigned int>(blue);

            /*  If the values exceed 255 return 255. 255 is the max intensity.*/
            if (x >= 255U)
                out_red = 255U;
            else
                out_red = static_cast<unsigned char>(x);

            if (y >= 255U)
                out_green = 255U;
            else
                out_green = static_cast<unsigned char>(y);

            if (z >= 255U)
                out_blue = 255U;
            else
                out_blue = static_cast<unsigned char>(z);

            /*  Use the constructor to return the sum from the RGB values.    */
            return color(out_red, out_green, out_blue);
        }
        /*  End of color addition.                                            */

        /*  Scaling a color by a real number.                                 */
        color operator * (double a)
        {
            const unsigned char r =
                static_cast<unsigned char>(a * static_cast<double>(red));
            const unsigned char g =
                static_cast<unsigned char>(a * static_cast<double>(green));
            const unsigned char b =
                static_cast<unsigned char>(a * static_cast<double>(blue));
            return color(r, g, b);
        }

        /*  Function for writing the color to a PPM file.                     */
        void write(FILE *fp)
        {
            std::fputc(red, fp);
            std::fputc(green, fp);
            std::fputc(blue, fp);
        }
    };
    /*  End of psow::color.                                                   */
}
/*  End of namespace psow.                                                    */

#endif
/*  End of include guard.                                                     */
