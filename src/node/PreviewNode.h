/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/10
 * Edited:  2023/08/10
 **********/
 
#pragma once

#include "GraphicsProcessingNode.h"

class PreviewNode : public GraphicsProcessingNode
{
public:
    PreviewNode();

protected:
    void drawContent() override;
    void process() override {}
};
