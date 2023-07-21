/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/07/21
 **********/

#pragma once

#include <string>
#include <vector>

#include "NodeContent.h"
#include "Pin.h"

class Node
{
public:
    Node();
    ~Node();

    void draw();

    virtual NodeContent& getContent(Pin::Type pin_type) = 0;

    // cv::MatからGLuintへの変換
    static GLuint convert_func(cv::Mat* mat)
    {
        GLuint texture_id;

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        cv::cvtColor((*mat), (*mat), cv::COLOR_RGB2BGR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*mat).cols, (*mat).rows, 0, GL_RGB, GL_UNSIGNED_BYTE, (*mat).ptr());

        return texture_id;
    };

    void setDirtyFlag()
    {
        this->m_need_update = true;

        for (Pin* pin : m_out_pins)
        {
            for (Node* node : pin->m_connected_nodes)
            {
                node->setDirtyFlag();
            }
        }
    }

private:
    void drawInPins();
    void drawOutPins();

protected:
    virtual void drawContent() = 0;

public:
    uint32_t m_id;
    std::string m_name;

    std::vector<class Pin*> m_in_pins;
    std::vector<class Pin*> m_out_pins;

    cv::Mat m_image;
    GLuint m_gl_texture;

    int32_t m_width  = 100;
    int32_t m_height = 100;

    bool m_need_update;
};
