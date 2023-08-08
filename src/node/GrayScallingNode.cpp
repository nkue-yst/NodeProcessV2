/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/08/09
 **********/

#include "GrayScallingNode.h"

#include "Logger.h"

GrayScallingNode::GrayScallingNode()
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "GrayScalling";

    this->m_content->m_image = cv::Mat::zeros(this->m_width, this->m_height, CV_8UC3);

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

void GrayScallingNode::drawContent()
{
    if (this->m_need_update)
    {
        this->m_content->m_image.release();

        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(this->m_in_pins.at(0)->m_id);    // Connected pin

        if (pair_pin)
        {
            GraphicsNode* connected_node = dynamic_cast<GraphicsNode*>(pair_pin->m_owner);         // Connected node

            if (connected_node)    // If the connected node is valid
            {
                this->m_content->m_image = connected_node->getContent<cv::Mat>(pair_pin->m_type);
            }
        }
        else
        {
            this->m_content->m_image = cv::Mat::zeros(this->m_initial_node_width, this->m_initial_node_width, CV_8UC3);
        }

        this->process();
        this->resizeFrame();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_content->m_image);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}

void GrayScallingNode::process()
{
    if (!this->m_content->m_image.empty())
    {
        cv::cvtColor(this->m_content->m_image, this->m_content->m_image, cv::COLOR_BGR2GRAY);
    }
}
