/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/10
 * Edited:  2023/08/10
 **********/

#include "PreviewNode.h"

PreviewNode::PreviewNode()
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Preview";

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Input pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "Input");
    this->m_in_pins.push_back(new_pin);
}

void PreviewNode::drawContent()
{
    if (this->m_need_update)
    {
        this->m_content->m_image.release();

        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(this->m_in_pins.at(0)->m_id);

        if (pair_pin)
        {
            Node* node = pair_pin->m_owner;
            this->m_content->m_image = node->getContent<cv::Mat>(pair_pin->m_type);
        }
        else
        {
            this->m_content->m_image = cv::Mat::zeros(this->m_initial_node_width, this->m_initial_node_width, CV_8UC3);
        }

        this->resizeFrame();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_content->m_image);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}
