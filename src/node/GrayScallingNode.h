/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __GRAY_SCALLING_H__
#define __GRAY_SCALLING_H__

#include "GraphicsProcessingNode.h"

class GrayScallingNode : public GraphicsProcessingNode
{
public:
    GrayScallingNode();

    cv::Mat getContent(Pin::Type pin_type) override;

protected:
    void drawContent() override;
    void process() override;
};

#endif
