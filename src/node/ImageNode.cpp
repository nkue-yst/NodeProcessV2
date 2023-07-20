/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/07/21
 **********/

#include "ImageNode.h"

#include "imgui.h"
#include "imnodes.h"
#include <opencv2/opencv.hpp>

#include "Pin.h"

ImageNode::ImageNode(std::string file_path)
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Image Source";

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = new Pin("RGB");
    this->m_out_pins.push_back(new_pin);

    if (!this->loadData(file_path))
    {
        std::cerr << "[INFO]: Failed to load: \"" << file_path << "\"" << std::endl;
    }
}

void ImageNode::drawContent()
{
    auto convert_func = [](cv::Mat* mat) -> GLuint
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

    if (this->m_need_update)
    {
        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_image);

        this->m_need_update ^= 1;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}

bool ImageNode::loadData(std::string file_path)
{
    // When `file_path` is null, generate and set empty image
    if (file_path.empty())
    {
        this->m_image = cv::Mat::zeros(100, 100, CV_8UC3);
        return true;
    }

    // Load image data
    this->m_image = cv::imread(file_path);

    // Set drawing size
    float resize_rate = 100.f / std::max(this->m_width, this->m_height);
    this->m_width *= resize_rate;
    this->m_height *= resize_rate;

    return true;
}
