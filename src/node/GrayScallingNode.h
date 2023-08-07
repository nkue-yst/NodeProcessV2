/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/08/07
 **********/

#ifndef __GRAY_SCALLING_H__
#define __GRAY_SCALLING_H__

#include "GraphicsProcessingNode.h"

class GrayScallingNode : public GraphicsProcessingNode
{
public:
    GrayScallingNode();

    template<typename T>
    T getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::m_type::RGB)
            return this->m_content->m_image;
    }

protected:
    void drawContent() override;
    void process() override;
};

#endif
