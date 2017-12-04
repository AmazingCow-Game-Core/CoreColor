//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Color.cpp                                                     //
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
#include "../include/Color.h"
// std
#include <algorithm>
#include <iomanip>
#include <sstream>
// CoreColor
#include "../include/Convert.h"

// Usings
USING_NS_CORECOLOR;


//----------------------------------------------------------------------------//
// RGBA Methods                                                               //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
Color Color::MakeRGBA(float r, float g, float b, float a /* = 1.0f */)
{
    Color color;
    color.setRGBA(r, g, b, a);

    return color;
}

//------------------------------------------------------------------------------
void Color::setRGBA(float r, float g, float b, float a /* = 1.0f */)
{
    m_mode = Color::Mode::RGB;

    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    rgb.a = a;
}

//------------------------------------------------------------------------------
Color::uint Color::toPackedRGBA() const
{
    //Just let the RGB function pack the RGB components
    //shift them and add the Alpha component.
    auto value = Color::toPackedRGB();
    auto alpha = static_cast<uint>(m_data[3] * 255);

    value = (value << 8) + alpha;

    return value;
}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
Color Color::toRGBA() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::RGB)
        return *this;

    Color color(*this);
    color.toRGBA_InPlace();

    return color;
}

//------------------------------------------------------------------------------
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
    else if(m_mode == Color::Mode::HSL)
    {
        hsl_to_rgb(
            hsl.h, hsl.s, hsl.l,
            &rgb.r, &rgb.g, &rgb.b
        );
    }

    //CMY -> RGBA : Direct Conversion.
    else if(m_mode == Color::Mode::CMY)
    {
        cmy_to_rgb(
            cmy.c, cmy.m, cmy.y,
            &rgb.r, &rgb.g, &rgb.b
        );
    }

    //CMYK -> RGBA : Needs to convert to CMY first.
    else if(m_mode == Color::Mode::CMYK)
    {
        this->toCMY_InPlace ();
        this->toRGBA_InPlace();
    }

    m_mode = Color::Mode::RGB;
}


//----------------------------------------------------------------------------//
// Hex Methods                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
std::string Color::toHexRGBA(const std::string &prefix /* = "0x"*/)
{
    std::stringstream ss;
    ss << std::hex
       << std::setw(6)
       << std::setfill('0')
       << toPackedRGBA();

    return ss.str();
}

//------------------------------------------------------------------------------
std::string Color::toHexRGB(const std::string &prefix /* = "0x"*/)
{
    std::stringstream ss;
    ss << std::hex
       << std::setw(6)
       << std::setfill('0')
       << toPackedRGB();

    return ss.str();
}


//----------------------------------------------------------------------------//
// HSV Methods                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
Color Color::MakeHSV(float h, float s, float v)
{
    Color color;
    color.setHSV(h, s, v);

    return color;
}

//------------------------------------------------------------------------------
void Color::setHSV(float h, float s, float v, float a /* = 1.0f */)
{
    m_mode = Color::Mode::HSV;

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
    hsv.a = 1;
}

//------------------------------------------------------------------------------
Color Color::toHSV() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::HSV)
        return *this;

    Color color(*this);
    color.toHSV_InPlace();

    return color;
}

//------------------------------------------------------------------------------
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
    else
    {
        this->toRGBA_InPlace();
        this->toHSV_InPlace ();
    }

    m_mode = Color::Mode::HSV;
}


//----------------------------------------------------------------------------//
// HSL Methods                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
Color Color::MakeHSL(float h, float s, float l)
{
    Color color;
    color.setHSL(h, s, l);

    return color;
}

//------------------------------------------------------------------------------
void Color::setHSL(float h, float s, float l, float a /* = 1.0f */)
{
    m_mode = Color::Mode::HSL;

    hsl.h = h;
    hsl.s = s;
    hsl.l = l;
    hsl.a = 1;
}

//------------------------------------------------------------------------------
Color Color::toHSL() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::HSL)
        return *this;

    Color color(*this);
    color.toHSL_InPlace();

    return color;
}

//------------------------------------------------------------------------------
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
    else
    {
        this->toRGBA_InPlace();
        this->toHSL_InPlace ();
    }

    m_mode = Color::Mode::HSL;
}


//----------------------------------------------------------------------------//
// CMY Methods                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
Color Color::MakeCMY(float c, float m, float y)
{
    Color color;
    color.setCMY(c, m, y);

    return color;
}

//------------------------------------------------------------------------------
void Color::setCMY(float c, float m, float y)
{
    m_mode = Color::Mode::CMY;

    cmy.c = c;
    cmy.m = m;
    cmy.y = y;

    m_data[3] = 0; //We're not using this on this color mode.
}

//------------------------------------------------------------------------------
Color Color::toCMY() const
{
    //Already on correct color mode...
    if(m_mode == Color::Mode::CMY)
        return *this;

    Color color(*this);
    color.toCMY_InPlace();

    return color;
}

//------------------------------------------------------------------------------
void Color::toCMY_InPlace()
{
    //RGBA -> CMY : Direct Conversion.
    if(m_mode == Color::Mode::RGB)
    {
        rgb_to_cmy(
            rgb.r,   rgb.g,  rgb.b,
            &cmy.c, &cmy.m, &cmy.y
        );
    }

    //CMYK -> CMY : Direct Conversion.
    else if(m_mode == Color::Mode::CMYK)
    {
        cmyk_to_cmy(
            cmyk.c, cmyk.m, cmyk.y, cmyk.k,
            &cmy.c, &cmy.m, &cmy.y
        );
    }

    //There's no direct conversion
    //  So we need convert to RGBA first and then
    //  convert to the correct color mode.
    else
    {
        this->toRGBA_InPlace();
        this->toCMY_InPlace ();
    }

    m_mode = Color::Mode::CMY;
}


//----------------------------------------------------------------------------//
// CMYK Methods                                                               //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
Color Color::MakeCMYK(float c, float m, float y, float k)
{
    Color color;
    color.setCMYK(c, m, y, k);

    return color;
}

//------------------------------------------------------------------------------
void Color::setCMYK(float c, float m, float y, float k)
{
    m_mode = Color::Mode::CMYK;

    cmyk.c = c;
    cmyk.m = m;
    cmyk.y = y;
    cmyk.k = k;
}

//------------------------------------------------------------------------------
Color Color::toCMYK() const
{
    //Already on correct color mode...
    if(m_mode == Color::Mode::CMYK)
        return *this;

    Color color(*this);
    color.toCMYK_InPlace();

    return color;
}

//------------------------------------------------------------------------------
void Color::toCMYK_InPlace()
{
    //CMY -> CMYK : Direct Conversion.
    if(m_mode == Color::Mode::CMY)
    {
        cmy_to_cmyk(
            cmy.c,    cmy.m,   cmy.y,
            &cmyk.c, &cmyk.m, &cmyk.y, &cmyk.k
        );
    }
    //There's no direct conversion
    //  So we need convert to CMY first and then
    //  convert to the correct color mode.
    else
    {
        this->toCMY_InPlace ();
        this->toCMYK_InPlace();
    }

    m_mode = Color::Mode::CMY;
}

//----------------------------------------------------------------------------//
// Mode Methods                                                               //
//----------------------------------------------------------------------------//
Color::Mode Color::getMode() const
{
    return m_mode;
}
