/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/04
 * Edited:  2023/08/05
 **********/

#pragma once

#include "GraphicsNode.h"

class VideoNode : public GraphicsNode
{
public:
    VideoNode(std::string file_path);

    cv::Mat getContent(Pin::Type pin_type) override;

private:
    void drawContent() override;
    bool loadData(std::string file_path);

    cv::VideoCapture m_video;

    bool m_playing;
};
