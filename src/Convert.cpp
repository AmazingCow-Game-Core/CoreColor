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


////////////////////////////////////////////////////////////////////////////////
// RGB -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
void CoreColor::rgb_to_hsv(
    float  r, float  g, float  b,
    float *h, float *s, float *v)
{
    //Formula from:
    //  http://www.easyrgb.com/en/math.php
    auto var_min = std::min({r, g, b});
    auto var_max = std::max({r, g, b});
    auto del_max = (var_max - var_min);

    float H = 0,
          S = 0,
          V = var_max;

    //Color is gray, it has no chroma.
    if(del_max == 0)
    {
        //Copy to the output vars.
        *h = H;
        *s = S;
        *v = V;

        return;
    }

    //Color has chroma...
    S = del_max / var_max;

    auto del_r = (((var_max - r) / 6.0f) + (del_max / 2.0f)) / del_max;
    auto del_g = (((var_max - g) / 6.0f) + (del_max / 2.0f)) / del_max;
    auto del_b = (((var_max - b) / 6.0f) + (del_max / 2.0f)) / del_max;

    if     (r == var_max) H = (del_b - del_g);
    else if(g == var_max) H = kOneThird + (del_r  - del_b);
    else if(b == var_max) H = kTwoThird + (del_g  - del_r);

    if     (H < 0) H += 1;
    else if(H > 1) H -= 1;

    //Copy to the output vars.
    *h = H;
    *s = S;
    *v = V;
}

void CoreColor::rgb_to_hsl(
    float  r, float  g, float  b,
    float *h, float *s, float *l)
{
    //Formula taken from:
    //  http://www.easyrgb.com/en/math.php
    auto var_min = std::min({r, g, b});
    auto var_max = std::max({r, g, b});
    auto del_max = (var_max - var_min);

    float H = 0,
          S = 0,
          L = (var_max + var_min) / 2.0f;

    //This is gray, no chroma
    if(del_max == 0)
    {
        //Copy the values to output vars.
        *h = H;
        *s = S;
        *l = L;

        return;
    }

    if(L < 0.5f) S = del_max / (var_max + var_min);
    else         S = del_max / (2.0f - var_max - var_min);

    float del_r = (((var_max - r) / 6.0f) + (del_max / 2.0f)) / del_max;
    float del_g = (((var_max - g) / 6.0f) + (del_max / 2.0f)) / del_max;
    float del_b = (((var_max - b) / 6.0f) + (del_max / 2.0f)) / del_max;

    if     (r == var_max) H = (del_b - del_g);
    else if(g == var_max) H = kOneThird + (del_r - del_b);
    else if(b == var_max) H = kTwoThird + (del_g - del_r);

    if     (H < 0) H += 1;
    else if(H > 1) H -= 1;

    //Copy to the output vars.
    *h = H;
    *s = S;
    *l = L;
}


////////////////////////////////////////////////////////////////////////////////
// HSV -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////
// HSL -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
float _hsl_hue_2_rgb(float v1, float v2, float vH)
{
    if     (vH < 0.0f) vH += 1.0f;
    else if(vH > 1.0f) vH -= 1.0f;

    if((6.0f * vH) < 1.0f) return (v1 + (v2 - v1) * 6.0f * vH);
    if((2.0f * vH) < 1.0f) return (v2);
    if((3.0f * vH) < 2.0f) return (v1 + (v2 - v1) * (kTwoThird - vH) * 6.0f);

    return v1;
}

void CoreColor::hsl_to_rgb(
    float   h, float  s, float  l,
    float  *r, float *g, float *b)
{
    if(s == 0)
    {
        *r = l;
        *g = l;
        *b = l;

        return;
    }

    float var_1 = 0,
          var_2 = 0;

    var_2 = (l < 0.5f) ? (l * (1 + s))
                       : (l + s) - (s * l);

    var_1 = (2 * l) - var_2;

    *r = _hsl_hue_2_rgb(var_1, var_2, h + kOneThird);
    *g = _hsl_hue_2_rgb(var_1, var_2, h);
    *b = _hsl_hue_2_rgb(var_1, var_2, h - kOneThird);
}


