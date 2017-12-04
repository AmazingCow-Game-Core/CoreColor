//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Convert.cpp                                                   //
//  Project   : CoreColor                                                     //
//  Date      : Aug 08, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "Convert.h"
// std
#include <algorithm>
#include <cmath>

//COWTODO(n2omatt): Should we validate the input range???


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kOneThird = 1.0f / 3.0f;
constexpr auto kTwoThird = 2.0f / 3.0f;


//----------------------------------------------------------------------------//
// RGB -> XXX                                                                 //
//----------------------------------------------------------------------------//
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

void CoreColor::rgb_to_cmy(
    float r,  float  g, float  b,
    float *c, float *m, float *y)
{
    *c = 1.0f - r;
    *m = 1.0f - g;
    *y = 1.0f - b;
}


//----------------------------------------------------------------------------//
// HSV -> XXX                                                                 //
//----------------------------------------------------------------------------//
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


//----------------------------------------------------------------------------//
// HSL -> XXX                                                                 //
//----------------------------------------------------------------------------//
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


//----------------------------------------------------------------------------//
// CMY -> XXX                                                                 //
//----------------------------------------------------------------------------//
void CoreColor::cmy_to_rgb(
    float  c, float  m, float  y,
    float *r, float *g, float *b)
{
    //Formula taken from:
    //  http://www.easyrgb.com/en/math.php
    *r = 1.0f - c;
    *g = 1.0f - m;
    *b = 1.0f - y;
}


void CoreColor::cmy_to_cmyk(
    float  c, float  m, float  y,
    float *C, float *M, float *Y, float *K)
{
    //Formula taken from:
    //  http://www.easyrgb.com/en/math.php
    auto var_K = 1.0f;

    if(c < var_K) var_K = c;
    if(m < var_K) var_K = m;
    if(y < var_K) var_K = y;

    *K = var_K;

    //Black only
    if(var_K == 1.0f)
    {
        *C = 0;
        *M = 0;
        *Y = 0;

        return;
    }

    *C = (c - var_K) / (1.0f - var_K);
    *M = (m - var_K) / (1.0f - var_K);
    *Y = (y - var_K) / (1.0f - var_K);
}


//----------------------------------------------------------------------------//
// CMYK -> XXX                                                                //
//----------------------------------------------------------------------------//
void CoreColor::cmyk_to_cmy(
    float  c, float  m, float  y, float k,
    float *C, float *M, float *Y)
{
    //Formula taken from:
    //  http://www.easyrgb.com/en/math.php

    *C = (c * (1.0f - k) + k);
    *M = (m * (1.0f - k) + k);
    *Y = (y * (1.0f - k) + k);
}
