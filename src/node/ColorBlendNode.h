/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/11
 * Edited:  2023/08/11
 **********/
 
#pragma once

#include "GraphicsNode.h"

class [[deprecated("There is a bug in the image display process.")]]
ColorBlendNode : public GraphicsNode
{
public:
    ColorBlendNode();

protected:
    void drawContent() override;
};
