
#include "CoreColor/CoreColor.h"


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

void print_cmy(const CoreColor::Color::CMY &cmy)
{
    printf("cmy: %f, %f, %f\n", cmy.c, cmy.m, cmy.y);
}

int main()
{
    auto rgb = CoreColor::Color::MakeRGBA(1, 0, 1);
    auto cmy = rgb.toCMY();

    print_cmy(cmy.toRGBA().toHSL().toHSV().toCMY().cmy);

    return 0;
}
