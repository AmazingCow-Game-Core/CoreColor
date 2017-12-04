//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : CoreColor_Utils.h                                             //
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

//----------------------------------------------------------------------------//
// Namespaces                                                                 //
//----------------------------------------------------------------------------//
// All classes of this core is placed inside this namespace.
// We use MACROS so is easier to change if needed.
// Is (in our opinion) more explicit.
// And finally the editors will not reformat the code.
#define NS_CORECOLOR_BEGIN namespace CoreColor {
#define NS_CORECOLOR_END   }
#define USING_NS_CORECOLOR using namespace CoreColor

//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//
#define COW_CORECOLOR_VERSION_MAJOR    "0"
#define COW_CORECOLOR_VERSION_MINOR    "0"
#define COW_CORECOLOR_VERSION_REVISION "0"

#define COW_CORECOLOR_VERSION       \
    COW_CORECOLOR_VERSION_MAJOR "." \
    COW_CORECOLOR_VERSION_MINOR "." \
    COW_CORECOLOR_VERSION_REVISION
