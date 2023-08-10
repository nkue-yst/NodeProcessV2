/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/10
 * Edited:  2023/08/10
 **********/
 
#pragma once

#include "GraphicsNode.h"

class PreviewNode : public GraphicsNode
{
public:
    PreviewNode();

protected:
    void drawContent() override;
};
