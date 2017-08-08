//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Convert.cpp                               //
//            █ █        █ █        CoreColor                                 //
//             ████████████                                                   //
//           █              █       Copyright (c) 2017                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Header
#include "Convert.h"
//std
#include <algorithm>
#include <cmath>


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kOneThird = 1.0f / 3.0f;
constexpr auto kTwoThird = 2.0f / 3.0f;
void CoreColor::rgb_to_hsv(
    float  r, float  g, float  b,
    float *h, float *s, float *v)
{
    //Formula from:
    //  http://www.easyrgb.com/en/math.php
    auto min   = std::min({r, g, b});
    auto max   = std::max({r, g, b});
    auto delta = max - min;

    float H = 0,
          S = 0,
          V = max;

    //Color is gray, it has no chroma.
    if(delta == 0)
    {
        //Copy to the output vars.
        *h = H;
        *s = S;
        *v = V;

        return;
    }

    //Color has chroma...
    S = delta / max;

    auto delta_r = ((( max - r) / 6.0f) + (delta / 2.0f)) / delta;
    auto delta_g = ((( max - g) / 6.0f) + (delta / 2.0f)) / delta;
    auto delta_b = ((( max - b) / 6.0f) + (delta / 2.0f)) / delta;

    if     (r == max) H = (delta_b - delta_g);
    else if(g == max) H = (1.0f / 3.0f) + (delta_r  - delta_b);
    else if(g == max) H = (2.0f / 3.0f) + (delta_g  - delta_r);

    if     (H < 0) H += 1;
    else if(H > 0) H -= 1;

    //Copy to the output vars.
    *h = H;
    *s = S;
    *v = V;
}

void CoreColor::hsv_to_rgb(
    float   h, float  s, float  v,
    float  *r, float *g, float *b)
{
    //Formula from:
    //  http://www.easyrgb.com/en/math.php
    if(s == 0)
    {
        //Copy the values to output vars.
        *r = *g = *b = v;
        return;
    }

    float var_h = (h * 6);
    if(var_h == 6) var_h = 0; //H must be < 1

    float var_i = floorf(var_h); //Or ... var_i = floor( var_h )

    float var_1 = v * (1 - s );
    float var_2 = v * (1 - s * (var_h - var_i));
    float var_3 = v * (1 - s * (1 - (var_h - var_i)));

    float var_r, var_g, var_b;
    if      (var_i == 0) { var_r = v    ;  var_g = var_3;  var_b = var_1; }
    else if (var_i == 1) { var_r = var_2;  var_g = v    ;  var_b = var_1; }
    else if (var_i == 2) { var_r = var_1;  var_g = v    ;  var_b = var_3; }
    else if (var_i == 3) { var_r = var_1;  var_g = var_2;  var_b = v    ; }
    else if (var_i == 4) { var_r = var_3;  var_g = var_1;  var_b = v    ; }
    else                 { var_r = v    ;  var_g = var_1;  var_b = var_2; }

    //Copy the values to output vars.
    *r = var_r;
    *g = var_g;
    *b = var_b;
}
