//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Color.h                                   //
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

NS_CORECOLOR_END
