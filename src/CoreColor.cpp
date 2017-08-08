//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        CoreColor.cpp                             //
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

//COWTODO: Add the license headers.

//Header
#include "CoreColor.h"
//std
#include <algorithm>
#include <iomanip>
#include <sstream>

//Usings
USING_NS_CORECOLOR;


///////////////////////////////////////////////////////////////////////////////
// Static Methods                                                            //
///////////////////////////////////////////////////////////////////////////////
//RGB
Color Color::MakeRGBA(int r, int g, int b, int a /* = 255 */)
{
    Color color;
    color.setRGBA(r, g, b, a);

    return color;
}

Color Color::MakeRGBA(float r, float g, float b, float a /* = 1.0f */)
{
    Color color;
    color.setRGBA(r, g, b, a);

    return color;
}

//HEX
Color Color::MakeHex(uint hex, bool hasAlpha /* = false */)
{
    if(hasAlpha)
    {
        return MakeRGBA(
            static_cast<int>((hex & 0xFF000000) >> 24),
            static_cast<int>((hex & 0x00FF0000) >> 16),
            static_cast<int>((hex & 0x0000FF00) >>  8),
            static_cast<int>((hex & 0x000000FF) >>  0)
        );
    }

    return MakeRGBA(
        static_cast<int>((hex & 0xFF0000) >> 16),
        static_cast<int>((hex & 0x00FF00) >>  8),
        static_cast<int>((hex & 0x0000FF) >>  0)
    );
}

Color Color::MakeHexStr(const std::string &hex)
{
    auto beg_it = std::begin(hex);

    // #RRGGBB - with the # at start.
    if(hex[0] == '#')
        ++beg_it; //Skip the # (first char)...

    // 0xRRGGBB - with the 0x at start.
    else if(hex[0] == '0' && hex[1] == 'x')
        beg_it += 2; //Skip the 0x (First and second chars)...

    // RRGGBB - without any prefix stuff.
    auto size         = std::end(hex) - beg_it;
    auto packed_value = 0;

    //COWTODO(n2omatt): asset the value is 6 or 8.
    std::string buf(beg_it, std::end(hex));
    sscanf(buf.c_str(), "%x", &packed_value);

    return Color::MakeHex(packed_value, size == 8);
}


//HSV
Color Color::MakeHSV(float h, float s, float v)
{
    Color color;
    color.setHSV(h, s, v);

    return color;
}

 //HSL
Color Color::MakeHSL(float h, float s, float l)
{
    Color color;
    color.setHSL(h, s, l);

    return color;
}


///////////////////////////////////////////////////////////////////////////////
// Getter Methods                                                            //
///////////////////////////////////////////////////////////////////////////////
Color::Mode Color::getMode() const
{
    return m_mode;
}


///////////////////////////////////////////////////////////////////////////////
// Setter Methods                                                            //
///////////////////////////////////////////////////////////////////////////////
//RGB
void Color::setRGBA(int r, int g, int b, int a /* = 255 */)
{
    setRGBA(
        r / 255.0f,
        g / 255.0f,
        b / 255.0f,
        a / 255.0f
    );
}

void Color::setRGBA(float r, float g, float b, float a /* = 1.0f */)
{
    m_mode = Color::Mode::RGB;

    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    rgb.a = a;
}

//HSV
void Color::setHSV(float h, float s, float v, float a /* = 1.0f */)
{
    m_mode = Color::Mode::HSV;

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
    hsv.a = 1;
}

//HSL
void Color::setHSL(float h, float s, float l, float a /* = 1.0f */)
{
    m_mode = Color::Mode::HSL;

    hsl.h = h;
    hsl.s = s;
    hsl.l = l;
    hsl.a = 1;
}


///////////////////////////////////////////////////////////////////////////////
// Public Methods                                                            //
///////////////////////////////////////////////////////////////////////////////
//HSV
Color::uint Color::toPackedRGBA() const
{
    //COWTODO(n2omatt): implement...
    return 0;
}

Color::uint Color::toPackedRGB() const
{
    const auto &color = (m_mode == Color::Mode::RGB)
        ? *this           //Refrence to itself.
        : this->toRGBA(); //New converted color.

    //COWTODO: this function is nearly idendical to the RGBA one.
    //  check what can be refactored.
    constexpr auto kComponentsCount = (3 - 1); //RGB -1 to be Zero based.

    uint packed_value = 0;
    for(int i = kComponentsCount; i >= 0; --i)
    {
        auto v = static_cast<uint>(color.m_data[i] * 255);
        packed_value +=  v << (8 * (kComponentsCount - i));
    }
    return packed_value;
}

Color Color::toRGBA() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::RGB)
        return *this;

    Color color(*this);
    color.toRGBA_InPlace();

    return color;
}

void Color::toRGBA_InPlace()
{
    //HSV -> RGBA : Direct Conversion.
    if(m_mode == Color::Mode::HSV)
    {
        hsv_to_rgb(
             hsv.h,  hsv.s,  hsv.v,
            &rgb.r, &rgb.g, &rgb.b
        );
    }
    //HSL -> RGBA : Direct Conversion.
    if(m_mode == Color::Mode::HSL)
    {
        hsl_to_rgb(
            hsl.h, hsl.s, hsl.l,
            &rgb.r, &rgb.g, &rgb.b
        );
    }

    m_mode = Color::Mode::RGB;
    //COWTODO: Implement other modes....
}

//Hex
std::string Color::toHexRGBA(const std::string &prefix /* = "0x"*/)
{
    std::stringstream ss;
    ss << std::hex
        << std::setw(6)
        << std::setfill('0')
        << toPackedRGBA();

    return ss.str();
}

std::string Color::toHexRGB(const std::string &prefix /* = "0x"*/)
{
    std::stringstream ss;
    ss << std::hex
       << std::setw(6)
       << std::setfill('0')
       << toPackedRGB();

    return ss.str();
}


//HSV
Color Color::toHSV() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::HSV)
        return *this;

    Color color(*this);
    color.toHSV_InPlace();

    return color;
}

void Color::toHSV_InPlace()
{
    //RGBA -> HSV : Direct Conversion.
    if(m_mode == Color::Mode::RGB)
    {
        rgb_to_hsv(
            rgb.r,  rgb.g,  rgb.b,
            &hsv.h, &hsv.s, &hsv.v
        );
    }
    //HSL -> HSV : No Direct Conversion.
    //  Need transform to RGBA first.
    else if(m_mode == Color::Mode::HSL)
    {
        this->toRGBA_InPlace();
        this->toHSV_InPlace ();
    }

    m_mode = Color::Mode::HSV;
}

Color Color::toHSL() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::HSL)
        return *this;

    Color color(*this);
    color.toHSL_InPlace();

    return color;
}

void Color::toHSL_InPlace()
{
    //RGBA -> HSL : Direct Conversion.
    if(m_mode == Color::Mode::RGB)
    {
        rgb_to_hsl(
            rgb.r,  rgb.g,  rgb.b,
            &hsl.h, &hsl.s, &hsl.l
        );
    }
    //HSV -> HSL : No Direct Conversion.
    //  Need transform to RGBA first.
    else if(m_mode == Color::Mode::HSV)
    {
        this->toRGBA_InPlace();
        this->toHSL_InPlace ();
    }

    m_mode = Color::Mode::HSL;
}
