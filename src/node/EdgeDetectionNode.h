/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/03
 * Edited:  2023/08/07
 **********/

#pragma once

#include "GraphicsProcessingNode.h"

class EdgeDetectionNode : public GraphicsProcessingNode
{
public:
    EdgeDetectionNode();

    template<typename T>
    T getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::m_type::RGB)
            return this->m_content->m_image;
    }

protected:
    void drawContent() override;
    void drawInPins() override;

    void process() override;

private:
    int32_t m_threshold[2];
};
