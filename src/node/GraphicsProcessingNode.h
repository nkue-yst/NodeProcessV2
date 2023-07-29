/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/29
 **********/

#pragma once

#include "GraphicsNode.h"
#include "Node.h"

class GraphicsProcessingNode : public GraphicsNode
{
protected:
    virtual void process() = 0;
};
