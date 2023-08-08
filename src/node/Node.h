/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/08/08
 **********/

#pragma once

#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "GL/gl.h"
#include "opencv2/opencv.hpp"

#include "NodeContent.h"
#include "NodeStyle.h"

class Pin;
enum Pin::Type;

namespace detail
{
    template<typename T>
    inline T getContent(NodeContent* body, Pin::Type pin_type);
    
    template<>
    inline cv::Mat getContent(NodeContent* body, Pin::Type pin_type)
    {
        cv::Mat mat = body->m_image.clone();

        switch (pin_type)
        {
        case Pin::Type::RGB:
            return mat;

        case Pin::Type::Red:
            for (uint32_t y = 0; y < mat.rows; ++y)
            {
                for (uint32_t x = 0; x < mat.cols; ++x)
                {
                    cv::Vec3b* data = mat.ptr<cv::Vec3b>(y);
                    data[x] = cv::Vec3b(0, 0, data[x][2]);
                }
            }
            return mat;

        case Pin::Type::Green:
            for (uint32_t y = 0; y < mat.rows; ++y)
            {
                for (uint32_t x = 0; x < mat.cols; ++x)
                {
                    cv::Vec3b* data = mat.ptr<cv::Vec3b>(y);
                    data[x] = cv::Vec3b(0, data[x][1], 0);
                }
            }
            return mat;

        case Pin::Type::Blue:
            for (uint32_t y = 0; y < mat.rows; ++y)
            {
                for (uint32_t x = 0; x < mat.cols; ++x)
                {
                    cv::Vec3b* data = mat.ptr<cv::Vec3b>(y);
                    data[x] = cv::Vec3b(data[x][0], 0, 0);
                }
            }
            return mat;

        default:
            return cv::Mat();
        }
    }

    template<>
    inline int32_t getContent(NodeContent* body, Pin::Type pin_type)
    {
        if (pin_type == Pin::Type::VALUE)
        {
            return body->m_value;
        }
        else
        {
            return -1;
        }
    }
}

class Node
{
public:
    Node(NodeType type = NodeType_UNDEFINED);
    virtual ~Node();

    ///////////////////////////////////
    ///// Get content by template /////
    ///////////////////////////////////
    NodeContent* m_content;

    template<typename T>
    T getContent(Pin::Type pin_type)
    {
        return detail::getContent<T>(this->m_content, pin_type);
    }

    // cv::MatからGLuintへの変換
    static GLuint convert_func(cv::Mat* mat)
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

        cv::cvtColor((*mat), (*mat), cv::COLOR_RGB2BGR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*mat).cols, (*mat).rows, 0, GL_RGB, GL_UNSIGNED_BYTE, (*mat).ptr());

        return texture_id;
    };

    void draw();

    void setDirtyFlag(int32_t new_priority = -1);

protected:
    virtual void drawInPins();
    virtual void drawOutPins();

    virtual void drawContent() = 0;

public:
    uint32_t m_id;
    std::string m_name;

    const uint32_t m_initial_node_width;
    uint32_t m_node_width;

    std::vector<class Pin*> m_in_pins;
    std::vector<class Pin*> m_out_pins;

    int32_t m_priority;

    bool m_need_update;

protected:
    NodeType m_type;
};
