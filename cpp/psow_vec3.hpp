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
 *      Provides a struct for working with 3D vectors.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 17, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef PSOW_VEC3_HPP
#define PSOW_VEC3_HPP

/*  printf is found here.                                                     */
#include <cstdio>

/*  sqrt function found here.                                                 */
#include <cmath>

/*  Namespace for the project. "Peter-Shirley-One-Weekend."                   */
namespace psow {

    /*  Struct used to represents vectors in R^3.                             */
    struct vec3 {

        /*  The data in a vector is it's Euclidean components.                */
        double x, y, z;

        /*  Empty constructor. Do not set any of the variables, simply return.*/
        inline vec3(void)
        {
            return;
        }

        /*  Constructor from three doubles. Set the components to the inputs. */
        inline vec3(double a, double b, double c)
        {
            x = a;
            y = b;
            z = c;
        }

        /*  Computes the Euclidean norm of the vector using Pythagoras.       */
        inline double norm(void) const;

        /*  Computes the square of the Euclidean norm. Avoids sqrt call.      */
        inline double normsq(void) const;

        /*  Computes the azimuthal component of the vector.                   */
        inline double rho(void) const;

        /*  Computes the square of the cylindrical part of the vector.        */
        inline double rhosq(void) const;

        /*  Computes the Euclidean dot product with another vector.           */
        inline double dot(const vec3 &P) const;

        /*  Computes the standard cross-product with another vector.          */
        inline vec3 cross(const vec3 &P) const;

        /*  Returns a vector of unit magnitude in the same direction.         */
        inline vec3 unit(void) const;

        /*  Normalize "this" vector.                                          */
        inline void normalize(void);

        /*  Simple print function for vectors.                                */
        inline void print(void) const;
    };
    /*  End of vec3 definition.                                               */
}
/*  End of "psow" namespace.                                                  */

/*  Vector addition operator.                                                 */
inline psow::vec3 operator + (const psow::vec3 &P, const psow::vec3 &Q)
{
    return psow::vec3(P.x + Q.x, P.y + Q.y, P.z + Q.z);
}

/*  Vector addition operator.                                                 */
inline void operator += (psow::vec3 &P, const psow::vec3 &Q)
{
    P.x += Q.x;
    P.y += Q.y;
    P.z += Q.z;
}

/*  Vector subtraction operator.                                              */
inline psow::vec3 operator - (const psow::vec3 &P, const psow::vec3 &Q)
{
    return psow::vec3(P.x - Q.x, P.y - Q.y, P.z - Q.z);
}

/*  Vector subtraction operator.                                              */
inline void operator -= (psow::vec3 &P, const psow::vec3 &Q)
{
    P.x -= Q.x;
    P.y -= Q.y;
    P.z -= Q.z;
}

/*  Vector negation.                                                          */
inline psow::vec3 operator - (const psow::vec3 &P)
{
    return psow::vec3(-P.x, -P.y, -P.z);
}

/*  Scalar multiplication on the right.                                       */
inline psow::vec3 operator * (const psow::vec3 &P, double a)
{
    return psow::vec3(a*P.x, a*P.y, a*P.z);
}

/*  Scalar multiplication on the left.                                        */
inline psow::vec3 operator * (double a, const psow::vec3 &P)
{
    return psow::vec3(a*P.x, a*P.y, a*P.z);
}

/*  Scalar multiplication operator.                                           */
inline void operator *= (psow::vec3 &P, double t)
{
    P.x *= t;
    P.y *= t;
    P.z *= t;
}

/*  Scalar division on the right.                                             */
inline psow::vec3 operator / (const psow::vec3 &P, double a)
{
    const double rcpr_a = 1.0 / a;
    return psow::vec3(rcpr_a*P.x, rcpr_a*P.y, rcpr_a*P.z);
}

/*  Scalar division operator.                                                 */
inline void operator /= (psow::vec3 &P, double t)
{
    const double rcpr_t = 1.0 / t;
    P.x *= rcpr_t;
    P.y *= rcpr_t;
    P.z *= rcpr_t;
}

/*  Euclidean norm (the length of the vector).                                */
inline double psow::vec3::norm(void) const
{
    return std::sqrt(x*x + y*y + z*z);
}

/*  Square of the Euclidean norm.                                             */
inline double psow::vec3::normsq(void) const
{
    return x*x + y*y + z*z;
}

/*  Cylindrical part (the length of the azimuthal component).                 */
inline double psow::vec3::rho(void) const
{
    return std::sqrt(x*x + y*y);
}

/*  Square of the cylindrical part.                                           */
inline double psow::vec3::rhosq(void) const
{
    return x*x + y*y;
}

/*  Euclidean dot product.                                                    */
inline double psow::vec3::dot(const psow::vec3 &P) const
{
    return P.x*x + P.y*y + P.z*z;
}

/*  Euclidean cross product in three dimensions.                              */
inline psow::vec3 psow::vec3::cross(const psow::vec3 &P) const
{
    return psow::vec3(y*P.z - z*P.y, z*P.x - x*P.z, x*P.y - y*P.x);
}

/*  Unit vector for the given vector.                                         */
inline psow::vec3 psow::vec3::unit(void) const
{
    return *this / (*this).norm();
}

/*  Unit vector for the given vector.                                         */
inline void psow::vec3::normalize(void)
{
    *this = this->unit();
}

/*  Simple function for printing out the values of the vector.                */
inline void psow::vec3::print(void) const
{
    std::printf("<%f, %f, %f>", x, y, z);
}

#endif
/*  End of include guard.                                                     */
