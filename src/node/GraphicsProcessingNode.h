/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __PROCESSING_NODE_H__
#define __PROSESSING_NODE_H__

#include "GraphicsNode.h"
#include "Node.h"

class GraphicsProcessingNode : public GraphicsNode
{
protected:
    virtual void process() = 0;
};

#endif
