/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/09
 * Edited:  2023/08/09
 **********/

#include "BreakRGBNode.h"

BreakRGBNode::BreakRGBNode()
    : Node(NodeType_Utility)
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Break RGB";

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Input pin
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "Input");
    this->m_in_pins.push_back(new_pin);

    // Output pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::Red, "Red");
    this->m_out_pins.push_back(new_pin);

    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::Green, "Green");
    this->m_out_pins.push_back(new_pin);

    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::Blue, "Blue");
    this->m_out_pins.push_back(new_pin);
}

void BreakRGBNode::drawContent()
{
    if (this->m_need_update)
    {
        this->m_content->m_image.release();

        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(this->m_in_pins.at(0)->m_id);

        if (pair_pin)
        {
            Node* node = pair_pin->m_owner;
            this->m_content->m_image = node->getContent<cv::Mat>(Pin::Type::RGB);
        }
        else
        {
            this->m_content->m_image = cv::Mat::zeros(this->m_initial_node_width, this->m_initial_node_width, CV_8UC3);
        }

        this->m_need_update = false;
    }
}
