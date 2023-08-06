/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/31
 * Edited:  2023/08/06
 **********/

#pragma once

#include "Node.h"

class GraphicsAnalyzeNode : public Node
{
protected:
    GraphicsAnalyzeNode()
    {
        this->m_type = NodeType_GraphicsAnalyze;
    }
};
