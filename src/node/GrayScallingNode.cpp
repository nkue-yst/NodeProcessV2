/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#include "GrayScallingNode.h"

#include "imgui.h"

#include "Log.h"
#include "NodeGui.h"

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

    // Input pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "Input");
    this->m_in_pins.push_back(new_pin);

    // Output pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);
}

cv::Mat GrayScallingNode::getContent(Pin::Type pin_type)
{
    cv::Mat content;

    if (pin_type == Pin::Type::RGB)
    {
        content = this->m_image;
    }
    else
    {
        log(LogType::ERROR, "Wrong type of pin connected.");
        NodeGui::get().abort();
    }

    return content;
}

void GrayScallingNode::drawContent()
{
    if (this->m_need_update)
    {
        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(this->m_in_pins.at(0)->m_id);    // Connected pin
        GraphicsNode* connected_node = dynamic_cast<GraphicsNode*>(pair_pin->m_owner);         // Connected node

        if (connected_node)
        {
            this->m_image = connected_node->getContent(Pin::Type::RGB);
        }

        this->process();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_image);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}

void GrayScallingNode::process()
{
    if (!this->m_image.empty())
    {
        cv::cvtColor(this->m_image, this->m_image, cv::COLOR_BGR2GRAY);
    }
}
