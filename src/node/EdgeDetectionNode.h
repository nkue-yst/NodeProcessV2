/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/03
 * Edited:  2023/08/04
 **********/

#pragma once

#include "GraphicsProcessingNode.h"

class EdgeDetectionNode : public GraphicsProcessingNode
{
public:
    EdgeDetectionNode();

    cv::Mat getContent(Pin::Type pin_type) override;

protected:
    void drawContent() override;
    void drawInPins() override;

    void process() override;

private:
    int32_t m_threshold[2];
};
