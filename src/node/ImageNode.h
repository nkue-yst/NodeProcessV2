/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/07/21
 **********/

#ifndef __IMAGE_NODE_H__
#define __IMAGE_NODE_H__

#include "GL/gl.h"
#include <opencv2/opencv.hpp>

#include "MediaNode.h"

class ImageNode : public MediaNode
{
public:
    ImageNode(std::string file_path);

private:
    void drawContent() override;
    bool loadData(std::string file_path) override;

    int32_t m_width  = 100;
    int32_t m_height = 100;

    cv::Mat m_image;
    GLuint m_gl_texture;
};

#endif
