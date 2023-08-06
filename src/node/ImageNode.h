/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/08/06
 **********/

#pragma once

#include "GraphicsNode.h"

class ImageNode : public GraphicsNode
{
public:
    ImageNode(std::string file_path);

    cv::Mat getContent(Pin::Type pin_type) override;

private:
    void drawContent() override;
    bool loadData(std::string file_path);
};
