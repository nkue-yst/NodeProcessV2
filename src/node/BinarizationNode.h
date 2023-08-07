/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/29
 * Edited:  2023/08/07
 **********/

#ifndef __BINARIZATION_NODE_H__
#define __BINARIZATION_NODE_H__

#include "GraphicsProcessingNode.h"

class BinarizationNode : public GraphicsProcessingNode
{
public:
    BinarizationNode();

    template<typename T>
    T getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::m_type::RGB)
            return this->m_content->m_image;
    }

protected:
    void drawContent() override;
    void process() override;

private:
    double m_threshold;
};

#endif
