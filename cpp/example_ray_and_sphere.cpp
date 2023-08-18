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
 *      Presents a simple struct for working with rays in raytracing.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  The C++ equivalent of math.h. sqrt is found here.                         */
#include <cmath>

/*  And the equivalent of stdio.h.                                            */
#include <cstdio>

#include "psow_color.hpp"
#include "psow_vec3.hpp"
#include "psow_ray.hpp"
#include "psow_sphere.hpp"

/*  Function for coloring the background with a gradient.                     */
static psow::color sky_gradient(psow::ray r)
{
    psow::vec3 v = (r.v).unit();
    double t = 0.5 * (v.y + 1.0);

    /*  Create a gradient from sky blue to white.                             */
    psow::color sky_blue = psow::color(128U, 180U, 255U);
    psow::color white    = psow::color(255U, 255U, 255U);
    return (white*(1.0 - t) + sky_blue*t)*2.0;
}
/*  End of sky_gradient.                                                      */

/*  Function for drawing a sky with a red ball in it.                         */
int main(void)
{
    unsigned int m, n;
    psow::color color;
    const double aspect_ratio = 16.0 / 9.0;
    const unsigned int image_width  = 1920U;
    const unsigned int image_height = static_cast<unsigned int>(
        static_cast<double>(image_width) / aspect_ratio
    );

    const double viewport_height = 2.0;
    const double viewport_width  = viewport_height * aspect_ratio;
    const double width_factor  = 1.0 / static_cast<double>(image_width - 1U);
    const double height_factor = 1.0 / static_cast<double>(image_height - 1U);
    const double focal_length = 1.0;
    const psow::color red = psow::color(255U, 0U, 0U);
    const psow::sphere s = psow::sphere(0.5, psow::vec3(0, 0, -1));
    const psow::vec3 origin = psow::vec3(0.0, 0.0, 0.0);
    const psow::vec3 horizontal = psow::vec3(viewport_width, 0.0, 0.0);
    const psow::vec3 vertical = psow::vec3(0.0, viewport_height, 0.0);
    const psow::vec3 focal_point = psow::vec3(0.0, 0.0, focal_length);

    const psow::vec3 lower_left_corner =
        origin - 0.5*(horizontal + vertical) - focal_point;

    FILE *fp = std::fopen("test_ray_with_sphere.ppm", "w");

    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    std::fprintf(fp, "P6\n%u %u\n255\n", image_width, image_height);

    for (m = image_height; m > 0; --m)
    {
        const double v = m * height_factor;

        for (n = 0U; n < image_width; ++n)
        {
            const double u = n * width_factor;

            const psow::vec3 direction = horizontal*u + vertical*v +
                                         lower_left_corner - origin;

            const psow::ray r = psow::ray(origin, direction);

            if (s.intersects_ray(r))
                color = red;
            else
                color = sky_gradient(r);

            color.write(fp);
        }
    }

    return 0;
}
