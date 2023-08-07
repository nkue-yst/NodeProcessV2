/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/01
 * Edited:  2023/08/07
 **********/

#pragma once

#include <algorithm>
#include <cstdint>

#include "imgui.h"

typedef int32_t NodeType;
typedef int32_t PinType;

typedef uint32_t NodeColor;
typedef uint32_t PinColor;

enum NodeType_
{
    NodeType_Constant,
    NodeType_GraphicsAnalyze,
    NodeType_GraphicsProcessing,
    NodeType_ImageSource,
    NodeType_VideoSource,

    NodeType_UNDEFINED,
};

enum PinType_
{
    PinType_RGB,
    PinType_Value,

    PinType_UNDEFINED,
};

inline uint32_t multiplyIM_COL(uint32_t base_color, float factor)
{
    uint32_t r = (base_color >> IM_COL32_R_SHIFT) & 0xFF;
    uint32_t g = (base_color >> IM_COL32_G_SHIFT) & 0xFF;
    uint32_t b = (base_color >> IM_COL32_B_SHIFT) & 0xFF;

    r = static_cast<uint32_t>(r * factor);
    g = static_cast<uint32_t>(g * factor);
    b = static_cast<uint32_t>(b * factor);

    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    return IM_COL32(r, g, b, base_color >> IM_COL32_A_SHIFT);
}

namespace
{
    constexpr NodeColor node_color[] =
    {
        IM_COL32( 142, 209, 224, 200 ),  // Constant
        IM_COL32(  70, 120,  82, 200 ),  // GraphicsAnalyze
        IM_COL32( 183,  37,  71, 200 ),  // GraphicsProcessing
        IM_COL32(  27,  61, 176, 200 ),  // ImageSource
        IM_COL32( 255, 127,  80, 200 ),  // VideoSource

        IM_COL32(0, 0, 0, 0),            // UNDEFINED
    };

    constexpr PinColor pin_color[] =
    {
        IM_COL32( 255, 255, 251, 255 ),  // RGB
        IM_COL32( 255, 235,  88, 255 ),  // Value

        IM_COL32(0, 0, 0, 0),            // UNDEFINED
    };
}

#define NODE_COLOR(NODE_TYPE) node_color[NODE_TYPE]
#define PIN_COLOR(PIN_TYPE) pin_color[PIN_TYPE]
