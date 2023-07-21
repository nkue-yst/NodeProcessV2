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
    Pin* new_pin = new Pin(Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);

    if (!this->loadData(file_path))
    {
        std::cerr << "[INFO]: Failed to load: \"" << file_path << "\"" << std::endl;
    }
}

NodeContent& ImageNode::getContent(Pin::Type pin_type)
{
    NodeContent* content = new NodeContent();

    if (pin_type == Pin::Type::RGB)
    {
        content->m_cv_mat = this->m_image;
    }

    return *content;
}

void ImageNode::drawContent()
{
    if (this->m_need_update)
    {
        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_image);

        this->m_need_update = false;
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

    this->m_need_update = true;

    return true;
}
