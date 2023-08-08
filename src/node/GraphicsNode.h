/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/08/08
 **********/

#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include "GL/gl.h"
#include "opencv2/opencv.hpp"

#include "Node.h"
#include "Pin.h"

class GraphicsNode : public Node
{
public:
    virtual ~GraphicsNode()
    {
        /////////////////////////////
        ///// Release resources /////
        /////////////////////////////
        glDeleteTextures(1, &this->m_gl_texture);
    }

    void resizeFrame()
    {
        // Set drawing size
        this->m_width  = this->m_content->m_image.size().width;
        this->m_height = this->m_content->m_image.size().height;

        float resize_rate = static_cast<float>(this->m_initial_node_width) / std::max(this->m_width, this->m_height);

        this->m_width  *= resize_rate;
        this->m_height *= resize_rate;

        this->m_node_width = this->m_width;
    }

    int32_t m_width  = this->m_node_width;    // Drawing width
    int32_t m_height = this->m_node_width;    // Drawing height

    ///cv::Mat m_image;
    GLuint m_gl_texture;
};
