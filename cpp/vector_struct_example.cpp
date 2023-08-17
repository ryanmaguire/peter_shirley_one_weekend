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
 *      This file presents a basic struct used to represent vectors.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  And the equivalent of stdio.h.                                            */
#include <cstdio>

/*  vec3 struct provided here.                                                */
#include "psow_vec3.hpp"

/*  Test the tools provided with this struct.                                 */
int main(void)
{
    psow::vec3 p = psow::vec3(1, 2, 3);
    psow::vec3 q = psow::vec3(2, 1, 0);
    psow::vec3 s = p.cross(q);

    std::printf("p           = ");
    p.print();
    std::printf("\n");

    std::printf("-p          = ");
    (-p).print();
    std::printf("\n");

    std::printf("q           = ");
    q.print();
    std::printf("\n");

    s = p + q;
    std::printf("p + q       = ");
    s.print();
    std::printf("\n");

    s = p - q;
    std::printf("p - q       = ");
    s.print();
    std::printf("\n");

    s = p.cross(q);
    std::printf("p x q       = ");
    s.print();
    std::printf("\n");

    printf("p * q       = %f\n", p.dot(q));
    printf("(p x q) * p = %f\n", p.dot(s));
    printf("(p x q) * q = %f\n", q.dot(s));

    p = p.unit();
    std::printf("p_hat       = ");
    p.print();
    std::printf("\n");

    q = q.unit();
    std::printf("q_hat       = ");
    q.print();
    std::printf("\n");

    printf("||p_hat||   = %f\n", p.norm());
    printf("||q_hat||   = %f\n", q.norm());
    return 0;
}
/*  End of main.                                                              */
