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
 *     	Provides a struct for working with 3D vectors.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 17, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef PSOW_RAY_HPP
#define PSOW_RAY_HPP

/*  vec3 struct provided here.                                                */
#include "psow_vec3.hpp"

/*  Namespace for the project. "Peter-Shirley-One-Weekend."                   */
namespace psow {

    /*  Struct for rays which are Affine subspaces of R^3, L = {A+tB, t real}.*/
    struct ray {

        /*  A ray is the set of all points of the form p + tv, where p and v  *
         *  are vectors and t is a real number.                               */
        vec3 p, v;

        /*  Empty construct, simply return.                                   */
        inline ray(void)
        {
            return;
        }

        /*  Constructor from a starting point and a direction.                */
        inline ray(const vec3 &P, const vec3 &V)
        {
            p = P;
            v = V;
        }

        /*  Computes a point on a ray from a real parameter. p + t*v.         */
        inline vec3 point(double t) const;

        /*  Function for creating a ray from two points on the ray.           */
        inline ray from_points(const vec3 &P, const vec3 &V);
    };
    /*  End of ray struct.                                                    */
}
/*  End of "psow" namespace.                                                  */

/*  Function for compute the point p + tv on the ray.                         */
inline psow::vec3 psow::ray::point(double t) const
{
    return p + v*t;
}


/*  Creates a ray from two points that fall on it.                            */
inline psow::ray
psow::ray::from_points(const psow::vec3 &A, const psow::vec3 &B)
{
    /*  A tangent vector for the ray is given by the relative positive        *
     *  vector going from A to B. Compute this ray.                           */
    return psow::ray(A, B-A);
}

#endif
/*  End of include guard.                                                     */
