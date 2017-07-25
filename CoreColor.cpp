//COWTODO: Add the license headers.

//Header
#include "CoreColor.h"
//std
#include <algorithm>

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

Color Color::MakeHexStr(const char *pHexStr)
{
    //COWTODO(n2omatt): Implement....
    return MakeHex(0, false);
}

//HSV
Color Color::MakeHSV(float h, float s, float v)
{
    Color color;
    color.setHSV(h, s, v);

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
void Color::setHSV(float h, float s, float v)
{
    m_mode = Color::Mode::HSV;

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
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
    auto &color = (m_mode == Color::Mode::RGB) 
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

    Color color;
    color.toRGBA_InPlace();

    return color;
}

void Color::toRGBA_InPlace()
{
    if(m_mode == Color::Mode::HSV)
    {
        rgb_to_hsv(
            rgb.r,  rgb.g,  rgb.b,
           &hsv.h, &hsv.s, &hsv.v
        );
    }

    //COWTODO: Implement other modes....
}


//HSV
Color Color::toHSV() const
{
    //Already on the correct color mode...
    if(m_mode == Color::Mode::HSV)
        return *this;

    Color color;
    color.toHSV_InPlace();

    return color;
}

void  Color::toHSV_InPlace()
{
}



///////////////////////////////////////////////////////////////////////////////
// Free Functions                                                            //
///////////////////////////////////////////////////////////////////////////////
void CoreColor::rgb_to_hsv(
    float  r, float  g, float  b,
    float *h, float *s, float *v)
{
    //Formula from: http://www.easyrgb.com/en/math.php
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
    //COWTODO: Implement....
}

