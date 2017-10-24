//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : CoreColor.cpp                                                 //
//  Project   : CoreColor                                                     //
//  Date      : Aug 08, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

//Header
#include "CoreColor.h"
//std
#include <algorithm>
#include <iomanip>
#include <sstream>
//CoreColor
#include "Convert.h"

//Usings
USING_NS_CORECOLOR;


///////////////////////////////////////////////////////////////////////////////
// Static Methods                                                            //
///////////////////////////////////////////////////////////////////////////////
//RGB
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
//RGB
Color::uint Color::toPackedRGBA() const
{
    //Just let the RGB function pack the RGB components
    //shift them and add the Alpha component.
    auto value = Color::toPackedRGB();
    auto alpha = static_cast<uint>(m_data[3] * 255);

    value = (value << 8) + alpha;

    return value;
}

Color::uint Color::toPackedRGB() const
{
    const auto &color = (m_mode == Color::Mode::RGB)
        ? *this           //Refrence to itself.
        : this->toRGBA(); //New converted color.

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
