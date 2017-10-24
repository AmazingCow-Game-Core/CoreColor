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
void rgb_to_hsv(
    float  r, float  g, float  b,
    float *h, float *s, float *v);

void rgb_to_hsl(
    float  r, float  g, float  b,
    float *h, float *s, float *l);


////////////////////////////////////////////////////////////////////////////////
// HSV -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
void hsv_to_rgb(
    float  h,  float  s, float v,
    float  *r, float *g, float *b);


////////////////////////////////////////////////////////////////////////////////
// HSL -> XXX                                                                 //
////////////////////////////////////////////////////////////////////////////////
void hsl_to_rgb(
    float   h, float  s, float  l,
    float  *r, float *g, float *b);


NS_CORECOLOR_END
