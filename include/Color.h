//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Color.h                                                       //
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

//std
#include <string>
//CoreColor
#include "CoreColor.h"


NS_CORECOLOR_BEGIN

class Color
{
    // Enums / Constants / Typedefs //
public:
    typedef unsigned int uint;
    enum class Mode {
        RGB = 10,
        HSV = 20,
        HSL = 30
    };


    // Inner Types //
public:
    struct HSV { float h, s, v, a; };
    struct HSL { float h, s, l, a; };
    struct RGB { float r, g, b, a; };


    // Static Methods //
public:
    //RGBA
    static Color MakeRGBA(float r, float g, float b, float a = 1.0f);

    //HEX
    static Color MakeHex(uint hex, bool hasAlpha = false);
    static Color MakeHexStr(const std::string &hex);

    //HSV
    static Color MakeHSV(float h, float s, float v);

    //HSL
    static Color MakeHSL(float h, float s, float l);


    // Getter Methods //
public:
    Mode getMode() const;


    // Setter Methods //
public:
    //RGBA
    void setRGBA(float r, float g, float b, float a = 1.0f);

    //HSV
    void setHSV(float h, float s, float v, float a = 1.0f);

    //HSL
    void setHSL(float h, float s, float l, float a = 1.0f);


    // To Methods //
public:
    //RGB
    uint toPackedRGBA() const;
    uint toPackedRGB () const;

    Color toRGBA() const;
    void  toRGBA_InPlace();

    //Hex
    std::string toHexRGBA(const std::string &prefix = "0x");
    std::string toHexRGB(const std::string &prefix = "0x");

    //HSV
    Color toHSV() const;
    void  toHSV_InPlace();

    //HSL
    Color toHSL() const;
    void  toHSL_InPlace();


    // iVars //
private:
    Mode  m_mode;

public:
    union {
        float m_data[4];
        HSV hsv;
        HSL hsl;
        RGB rgb;
    };
};

NS_CORECOLOR_END
