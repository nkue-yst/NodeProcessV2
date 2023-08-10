/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/08/10
 **********/

#pragma once

#include "GraphicsNode.h"
#include "Node.h"

class GraphicsProcessingNode : public GraphicsNode
{
protected:
    GraphicsProcessingNode()
    {
        this->m_type = NodeType_GraphicsProcessing;
    }

    // cv::Mat‚©‚çGLuint‚Ö‚Ì•ÏŠ·
    inline virtual GLuint convert_func(cv::Mat* mat) override
    {
        if (mat->empty())
        {
            return 0;
        }

        GLuint texture_id;

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*mat).cols, (*mat).rows, 0, GL_RGB, GL_UNSIGNED_BYTE, (*mat).ptr());

        return texture_id;
    };

    virtual void process() = 0;
};
