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
    ///@brief
    ///  Just to reduce verbosity...
    typedef unsigned int uint;

    ///@brief
    ///  Describes witch color space the object is in a given moment.
    enum class Mode {
        RGB  = 10,
        HSV  = 20,
        HSL  = 30,
        CMY  = 40,
        CMYK = 50
    };


    // Inner Types //
public:
    ///@brief RGB object representation.
    struct RGB { float r, g, b, a; };
    ///@brief HSV object representation.
    struct HSV { float h, s, v, a; };
    ///@brief HSL object representation.
    struct HSL { float h, s, l, a; };
    ///@brief CMY object representation.
    struct CMY { float c; float m; float y; };
    ///@brief CMYK object representation.
    struct CMYK { float c; float m; float y; float k; };



    // Static Methods //
public:
    //RGBA
    ///@brief
    ///  Create a Color object initialized in the RGBA color space.
    ///@param r
    ///  Red value (0,1)
    ///@param g
    ///  Green value (0,1)
    ///@param b
    ///  Blue value (0,1)
    ///@param a
    ///  Alpha value (0,1) - Default 1.0
    ///@returns
    ///  The Color object in RGBA color space.
    static Color MakeRGBA(float r, float g, float b, float a = 1.0f);

    //HEX
    ///@brief
    ///  Create a Color object initialized in the RGBA color space
    ///  with the hexadecimal value.
    ///  If hasAlpha is true the function expect a 32 bit integer,
    ///  otherwise it'll consider only the first 24 bits.
    ///@param hex
    ///  The hexadecimal RGB(A) value.
    ///@param hasAlpha
    ///  If the value has the alpha component.
    ///@returns
    ///  The Color object in RGBA color space.
    ///@see MakeHexStr
    static Color MakeHex(uint hex, bool hasAlpha = false);

    ///@brief
    ///  Create a Color object initialized in the RGBA color space
    ///  with the hexadecimal value as string.
    ///  The function will accept the given formats:
    ///    - #RRGGBB(AA) with the leading '#' and optional alpha.
    ///    - 0xRRGGBB(AA) with the leading '0x' and optional alpha.
    ///    - RRGGBB(AA) without any leading chars and optional alpha.
    ///@param hex
    ///  The hexadecimal RGB(A) value.
    ///@returns
    ///  The Color object in RGBA color space.
    static Color MakeHexStr(const std::string &hex);

    //HSV
    ///@brief
    ///  Create a Color object initialized in the HSV color space.
    ///@param h
    ///  Hue value (0,1)
    ///@param s
    ///  Saturation value (0,1)
    ///@param v
    ///  Value value (0,1)
    ///@returns
    ///  The Color object in HSV color space.
    static Color MakeHSV(float h, float s, float v);

    //HSL
    ///@brief
    ///  Create a Color object initialized in the HSL color space.
    ///@param h
    ///  Hue value (0,1)
    ///@param s
    ///  Saturation value (0,1)
    ///@param l
    ///  Luminance value (0,1)
    ///@returns
    ///  The Color object in HSL color space.
    static Color MakeHSL(float h, float s, float l);

    //CMY
    static Color MakeCMY(float c, float m, float y);

    //CMYK
    static Color MakeCMYK(float c, float m, float y, float k);


    // Getter Methods //
public:
    ///@brief Gets which color mode the Color object is.
    ///@see Mode.
    Mode getMode() const;


    // Setter Methods //
public:
    //RGBA
    ///@brief
    ///  Set the object's color mode to RGBA with the given values.
    ///@param r
    ///  Red value (0,1)
    ///@param g
    ///  Green value (0,1)
    ///@param b
    ///  Blue value (0,1)
    ///@param a
    ///  Alpha value (0,1) - Default 1.0
    void setRGBA(float r, float g, float b, float a = 1.0f);

    //HSV
    ///@brief
    ///  Set the object's color mode to HSV with the given values.
    ///@param h
    ///  Hue value (0,1)
    ///@param s
    ///  Saturation value (0,1)
    ///@param v
    ///  Value value (0,1)
    void setHSV(float h, float s, float v, float a = 1.0f);

    //HSL
    ///@brief
    ///  Set the object's color mode to HSL with the given values.
    ///@param h
    ///  Hue value (0,1)
    ///@param s
    ///  Saturation value (0,1)
    ///@param l
    ///  Luminance value (0,1)
    void setHSL(float h, float s, float l, float a = 1.0f);

    //CMY
    void setCMY(float c, float m, float y);

    //CMYK
    void setCMYK(float c, float m, float y, float k);


    // To Methods //
public:
    //RGB
    ///@brief
    ///  Gets a converted packed (32 bit uint) RGBA
    ///  representation of the object.
    ///@note
    ///  The bit structure will be:
    ///    [RRRR RRRR] [GGGG GGGG] [BBBB BBBB] [AAAA AAAA]
    uint toPackedRGBA() const;

    ///@brief
    ///  Gets a converted packed (32 bit uint with last 8 bits set to 0) RGB
    ///  representation of the object.
    ///@note
    ///  The bit structure will be:
    ///    [0000 0000] [RRRR RRRR] [GGGG GGGG] [BBBB BBBB]
    uint toPackedRGB () const;

    ///@brief
    ///  Gets a converted Color object in the RGBA color space.
    Color toRGBA() const;

    ///@brief
    ///  Converts the object to RGBA color space.
    void toRGBA_InPlace();

    //Hex
    ///@brief
    ///  Gets a converted hexadecimal string representation of the object.
    ///@param prefix
    ///  Which prefix should be prepend on the returned string.
    std::string toHexRGBA(const std::string &prefix = "0x");

    ///@brief
    ///  Gets a converted hexadecimal string representation of the object.
    ///@param prefix
    ///  Which prefix should be prepend on the returned string.
    std::string toHexRGB(const std::string &prefix = "0x");

    //HSV
    ///@brief
    ///  Gets a converted Color object in the HSV color space.
    Color toHSV() const;

    ///@brief
    ///  Converts the object to HSV color space.
    void toHSV_InPlace();

    //HSL
    ///@brief
    ///  Gets a converted Color object in the HSV color space.
    Color toHSL() const;

    ///@brief
    ///  Converts the object to HSV color space.
    void toHSL_InPlace();

    //CMY
    Color toCMY() const;
    void toCMY_InPlace();

    //CMYK
    Color toCMYK() const;
    void toCMYK_InPlace();


    // iVars //
private:
    Mode  m_mode;

public:
    union {
        float m_data[4];
        HSV   hsv;
        HSL   hsl;
        RGB   rgb;
        CMY   cmy;
        CMYK  cmyk;
    };
};

NS_CORECOLOR_END
