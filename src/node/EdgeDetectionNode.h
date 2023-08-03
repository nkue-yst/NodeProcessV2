/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/03
 * Edited:  2023/08/03
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
    void process() override;

private:
    double m_threshold[2];
};
