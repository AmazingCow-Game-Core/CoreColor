#include "CoreColor.h"


void print_hsv(const CoreColor::Color::HSV &hsv)
{
    auto h = hsv.h * 360;
    auto s = hsv.s * 100;
    auto v = hsv.v * 100;

    printf("hsv: %f %f %f\n", h, s, v);
}

void print_hsl(const CoreColor::Color::HSL &hsl)
{
    auto h = hsl.h * 360;
    auto s = hsl.s * 100;
    auto l = hsl.l * 100;

    printf("hsl: %f %f %f\n", h, s, l);
}

int main()
{
    auto rgb = CoreColor::Color::MakeRGBA(0.999999762f, 0, 1);
    auto hsv = rgb.toHSV();
    auto hsl = rgb.toHSL();

    print_hsv(hsv.hsv);
    print_hsl(hsl.hsl);

    auto hsv2 = hsl.toHSV();
    auto hsl2 = hsv.toHSL();

    print_hsv(hsv2.hsv);
    print_hsl(hsl2.hsl);

    return 0;
}
