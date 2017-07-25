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
void Color::setHSV(float h, float s, float v, float a /* = 1.0f */)
{
    m_mode = Color::Mode::HSV;

    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
    hsv.a = 1;
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
    if(m_mode == Color::Mode::HSV)
    {
        hsv_to_rgb(
             hsv.h,  hsv.s,  hsv.v,
            &rgb.r, &rgb.g, &rgb.b
        );

        m_mode = Color::Mode::RGB;
    }

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

void  Color::toHSV_InPlace()
{
    if(m_mode == Color::Mode::RGB)
    {
        rgb_to_hsv(
            rgb.r,  rgb.g,  rgb.b,
            &hsv.h, &hsv.s, &hsv.v
        );

        m_mode = Color::Mode::HSV;
    }
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
    //Formula from: http://www.easyrgb.com/en/math.php
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

