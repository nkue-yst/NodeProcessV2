/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __NODE_CONTENT_H__
#define __NODE_CONTENT_H__

#include "GL/gl.h"
#include "opencv2/opencv.hpp"

////////////////////////////////////////////////
///// ピンの接続による受け渡しを行うデータ /////
////////////////////////////////////////////////
union NodeContent
{
public:
    NodeContent() {}
    ~NodeContent() {}

    cv::Mat m_cv_mat;
    GLuint m_gl_texture;
};

#endif
