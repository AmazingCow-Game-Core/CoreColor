//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Convert.h                                                     //
//  Project   : CoreColor                                                     //
//  Date      : Aug 08, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once
//CoreColor
#include "CoreColor_Utils.h"


NS_CORECOLOR_BEGIN

////////////////////////////////////////////////////////////////////////////////
// RGB -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
///@brief Converts RGB -> HSV.
///@note Pointer parameters are output vars.
void rgb_to_hsv(
    float  r, float  g, float  b,
    float *h, float *s, float *v);

///@brief Converts RGB -> HSL.
///@note Pointer parameters are output vars.
void rgb_to_hsl(
    float  r, float  g, float  b,
    float *h, float *s, float *l);

///@brief Converts RGB -> CMY.
///@note Pointer parameters are output vars.
void rgb_to_cmy(
    float r,  float  g, float b,
    float *c, float *m, float *y);


////////////////////////////////////////////////////////////////////////////////
// HSV -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
///@brief Converts HSV -> RGB.
///@note Pointer parameters are output vars.
void hsv_to_rgb(
    float  h,  float  s, float v,
    float  *r, float *g, float *b);


////////////////////////////////////////////////////////////////////////////////
// HSL -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
///@brief Converts HSL -> RGB.
///@note Pointer parameters are output vars.
void hsl_to_rgb(
    float   h, float  s, float  l,
    float  *r, float *g, float *b);


////////////////////////////////////////////////////////////////////////////////
// CMY -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
///@brief Converts CMY -> RGB.
///@note Pointer parameters are output vars.
void cmy_to_rgb(
    float  c, float  m, float  y,
    float *r, float *g, float *b);

///@brief Converts CMY -> CMYK.
///@note Pointer parameters are output vars.
void cmy_to_cmyk(
    float  c, float  m, float  y,
    float *C, float *M, float *Y, float *K);


////////////////////////////////////////////////////////////////////////////////
// CMYK -> XXX                                                                //
////////////////////////////////////////////////////////////////////////////////
///@brief Converts CMYK -> CMY.
///@note Pointer parameters are output vars.
void cmyk_to_cmy(
    float  c, float  m, float  y, float k,
    float *C, float *M, float *Y);

NS_CORECOLOR_END
