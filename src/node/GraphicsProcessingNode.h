/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/08/06
 **********/

#pragma once

#include "GraphicsNode.h"
#include "Node.h"

class GraphicsProcessingNode : public GraphicsNode
{
protected:
    GraphicsProcessingNode()
    {
        this->m_type = NodeType_GraphicsProcessing;
    }

    virtual void process() = 0;
};
