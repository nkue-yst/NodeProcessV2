/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#include "GrayScallingNode.h"

#include "imgui.h"

GrayScallingNode::GrayScallingNode()
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "GrayScalling";

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;
    new_pin = new Pin(Pin::Type::RGB, "Input");
    this->m_in_pins.push_back(new_pin);

    new_pin = new Pin(Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);
}

void GrayScallingNode::drawContent()
{
    if (this->m_need_update)
    {
        this->process();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_image);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}

void GrayScallingNode::process()
{
    cv::cvtColor(this->m_image, this->m_image, cv::COLOR_BGR2GRAY);
}
