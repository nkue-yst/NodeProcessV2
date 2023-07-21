/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __PROCESSING_NODE_H__
#define __PROSESSING_NODE_H__

#include "Node.h"

class ProcessingNode : public Node
{
public:
    NodeContent& getContent(Pin::Type pin_type) override
    {
        NodeContent* content = new NodeContent();

        if (pin_type == Pin::Type::RGB)
        {
            content->m_cv_mat = this->m_image;
        }

        return *content;
    }

protected:
    virtual void process() = 0;
};

#endif
