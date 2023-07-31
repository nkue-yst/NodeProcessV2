/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/01
 * Edited:  2023/08/01
 **********/

#pragma once

#include <cstdint>

struct Color
{
    uint32_t r, g, b;
};

namespace NodeColor
{
    constexpr Color GraphicsAnalyzeNode    {  32,  32,  32 };
    constexpr Color GraphicsProcessingNode {  64, 128, 128 };
    constexpr Color ImageSourceNode        {  64, 128,  64 };
    constexpr Color VideoSourceNode        {  64, 128,  64 };
}
