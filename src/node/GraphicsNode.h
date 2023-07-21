/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __GRAPHICS_NODE_H__
#define __GRAPHICS_NODE_H__

#include "GL/gl.h"
#include "opencv2/opencv.hpp"

#include "Node.h"
#include "Pin.h"

class GraphicsNode : public Node
{
public:
    virtual cv::Mat getContent(Pin::Type pin_type) = 0;

    int32_t m_width  = 100;
    int32_t m_height = 100;

    cv::Mat m_image;
    GLuint m_gl_texture;
};

#endif
