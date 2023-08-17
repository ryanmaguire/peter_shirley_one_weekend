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

/*  Struct for dealing with spheres.                                          */
struct sphere {

    /*  A sphere is defined by its radius and its center.                     */
    double radius;
    psow::vec3 center;

    /*  Empty constructor. Return NULL.                                       */
    sphere(void)
    {
        return;
    }

    /*  Main constructor.                                                     */
    sphere(double r, psow::vec3 c)
    {
        radius = r;
        center = c;
    }
};
/*  End of definition of sphere.                                              */

/*  Since a sphere satisfies (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = r^2, given a    *
 *  ray L(t) = p + tv, solving for which values of t satisfy the sphere's     *
 *  equation amounts to solving a quadratic equation.                         */
static bool sphere_is_hit(psow::ray r, sphere s)
{
    psow::vec3 oc = r.p - s.center;
    double a = (r.v).normsq();
    double b = 2.0 * (r.v).dot(oc);
    double c = oc.normsq() - s.radius*s.radius;
    double D = b*b - 4.0*a*c;

    if (D > 0.0)
    {
        if (a*(-b + sqrt(D)) > 0.0)
            return true;
        else
            return false;
    }
    else
        return false;
}
/*  End of sphere_is_hit.                                                     */

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
    FILE *fp;
    double width_factor, height_factor, u, v;
    psow::ray r;
    psow::color color;
    psow::vec3 direction;
    const double aspect_ratio = 16.0 / 9.0;
    const unsigned int image_width  = 1920U;
    const unsigned int image_height
        = (unsigned int)((double)image_width / aspect_ratio);

    double viewport_height = 2.0;
    double viewport_width  = viewport_height * aspect_ratio;
    double focal_length = 1.0;
    psow::color red = psow::color(255U, 0U, 0U);

    sphere s = sphere(0.5, psow::vec3(0, 0, -1));

    psow::vec3 origin = psow::vec3(0.0, 0.0, 0.0);
    psow::vec3 horizontal, vertical, lower_left_corner;
    horizontal = psow::vec3(viewport_width, 0.0, 0.0);
    vertical   = psow::vec3(0.0, viewport_height, 0.0);

    lower_left_corner = origin - (horizontal*0.5) - (vertical*0.5) -
                        psow::vec3(0.0, 0.0, focal_length);

    fp = std::fopen("test_ray_with_sphere.ppm", "w");

    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    std::fprintf(fp, "P6\n%u %u\n255\n", image_width, image_height);
    width_factor  = 1.0 / (double)(image_width - 1U);
    height_factor = 1.0 / (double)(image_height - 1U);

    for (m = image_height; m > 0; --m)
    {
        for (n = 0U; n < image_width; ++n)
        {
            u = (double)n * width_factor;
            v = (double)m * height_factor;
            direction = lower_left_corner + horizontal*u + vertical*v - origin;
            r = psow::ray(origin, direction);

            if (sphere_is_hit(r, s))
                color = red;
            else
                color = sky_gradient(r);

            color.write(fp);
        }
    }

    return 0;
}
