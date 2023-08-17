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
 *      Provides a struct for working with sphere.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 17, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef PSOW_SPHERE_HPP
#define PSOW_SPHERE_HPP

/*  vec3 struct provided here.                                                */
#include "psow_vec3.hpp"

/*  ray struct given here.                                                    */
#include "psow_ray.hpp"

/*  Namespace for the project. "Peter-Shirley-One-Weekend."                   */
namespace psow {

    /*  Struct for dealing with spheres.                                      */
    struct sphere {

        /*  A sphere is defined by its radius and its center.                 */
        double radius;
        vec3 center;

        /*  Empty constructor. Return NULL.                                   */
        inline sphere(void)
        {
            return;
        }

        /*  Main constructor.                                                 */
        inline sphere(double r, const psow::vec3 &c)
        {
            radius = r;
            center = c;
        }

        /*  Function for determining if a ray intersects a sphere.            */
        inline bool intersects_ray(const psow::ray &r) const;
    };
    /*  End of definition of sphere.                                          */
}
/*  End of "psow" namespace.                                                  */

/*  Since a sphere satisfies (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = r^2, given a    *
 *  ray L(t) = p + tv, solving for which values of t satisfy the sphere's     *
 *  equation amounts to solving a quadratic equation.                         */
inline bool psow::sphere::intersects_ray(const psow::ray &r) const
{
    const psow::vec3 oc = r.p - center;
    const double a = r.v.normsq();
    const double b = 2.0 * r.v.dot(oc);
    const double c = oc.normsq() - radius*radius;
    const double D = b*b - 4.0*a*c;

    if (D > 0.0)
    {
        const double sqrt_D = std::sqrt(D);

        if (sqrt_D - b > 0.0)
            return true;

        return false;
    }

    return false;
}
/*  End of intersects_ray.                                                    */

#endif
/*  End of include guard.                                                     */
