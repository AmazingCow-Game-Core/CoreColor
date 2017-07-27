//COWTODO: Add the license headers.
#pragma once
//std
#include <string>

#define NS_CORECOLOR_BEGIN namespace CoreColor {
#define NS_CORECOLOR_END   }
#define USING_NS_CORECOLOR using namespace CoreColor


NS_CORECOLOR_BEGIN
// Color Class //
class Color
{
    // Enums / Constants / Typedefs //
public:
    typedef unsigned int uint;
    enum class Mode { RGB = 10, HSV = 20};


    // Inner Types //
public:
    struct HSV { float h, s, v, a; };
    struct RGB { float r, g, b, a; };


    // Static Methods //
public:
    //RGBA
    static Color MakeRGBA(int r, int g, int b, int a = 255);
    static Color MakeRGBA(float r, float g, float b, float a = 1.0f);

    //HEX
    static Color MakeHex(uint hex, bool hasAlpha = false);
    static Color MakeHexStr(const std::string &hex);

    //HSV
    static Color MakeHSV(float h, float s, float v);


    // Getter Methods //
public:
    Mode getMode() const;


    // Setter Methods //
public:
    //RGBA
    void setRGBA(int r, int g, int b, int a = 255);
    void setRGBA(float r, float g, float b, float a = 1.0f);

    //HSV
    void setHSV(float h, float s, float v, float a = 1.0f);


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


    // iVars //
private:
    Mode  m_mode;
    union {
        float m_data[4];
        HSV hsv;
        RGB rgb;
    };
};


// Free Functions //
void rgb_to_hsv(
    float  r, float  g, float  b,
    float *h, float *s, float *v);

void hsv_to_rgb(
    float  h,  float  s, float v,
    float  *r, float *g, float *b);


NS_CORECOLOR_END
