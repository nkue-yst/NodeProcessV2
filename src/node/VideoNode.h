/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/04
 * Edited:  2023/08/07
 **********/

#pragma once

#include "GraphicsNode.h"

class VideoNode : public GraphicsNode
{
public:
    VideoNode(std::string file_path);

    template<typename T>
    T getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::m_type::RGB)
            return this->m_content->m_image;
    }

private:
    void drawContent() override;
    bool loadData(std::string file_path);

    cv::VideoCapture m_video;

    bool m_playing;
};
