/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/08/06
 **********/

#include "ImageNode.h"

#include "imgui.h"
#include "imnodes.h"
#include <opencv2/opencv.hpp>

#include "Logger.h"
#include "NodeGui.h"
#include "Pin.h"

ImageNode::ImageNode(std::string file_path)
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Image Source";
    this->m_type = NodeType_ImageSource;

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Output pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);

    ///////////////////////////
    ///// Load image data /////
    ///////////////////////////
    if (!this->loadData(file_path))
    {
        WARNING("Failed to load: \"" + file_path + "\"");
    }
}

cv::Mat ImageNode::getContent(Pin::Type pin_type)
{
    cv::Mat content;

    if (pin_type == Pin::Type::RGB)
    {
        content = this->m_image;
    }
    else
    {
        ERROR("Wrong type of pin connected.");
        NodeGui::get().abort();
    }

    return content;
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
