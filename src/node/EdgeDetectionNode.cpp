/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/03
 * Edited:  2023/08/09
 **********/

 #include "EdgeDetectionNode.h"

 #include "Logger.h"
 #include "Pin.h"

EdgeDetectionNode::EdgeDetectionNode()
{
    this->m_threshold[0] = 255 / 3;
    this->m_threshold[1] = 255 / 3 * 2;

    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "EdgeDetection";

    this->m_content->m_image = cv::Mat::zeros(this->m_width, this->m_height, CV_8UC3);

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Input pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "Input");
    this->m_in_pins.push_back(new_pin);

    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::VALUE, "Threshold");
    this->m_in_pins.push_back(new_pin);

    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::VALUE, "Threshold");
    this->m_in_pins.push_back(new_pin);

    // Output pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);
}

void EdgeDetectionNode::drawContent()
{
    if (this->m_need_update)
    {
        this->m_content->m_image.release();

        ////////////////////////////////
        ///// Input from 'RGB' pin /////
        ////////////////////////////////
        auto pin_iter = this->m_in_pins.begin();
        Pin* pin = *(pin_iter++);
        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(pin->m_id);

        if (pair_pin)
        {
            GraphicsNode* connected_node = dynamic_cast<GraphicsNode*>(pair_pin->m_owner);    // Connected node

            if (connected_node)    // If the connected node is valid
            {
                this->m_content->m_image = connected_node->getContent<cv::Mat>(pair_pin->m_type);
            }
        }
        else
        {
            this->m_content->m_image = cv::Mat::zeros(this->m_initial_node_width, this->m_initial_node_width, CV_8UC3);
        }

        ///////////////////////////////////
        ///// Input from 'VALUE' pins /////
        ///////////////////////////////////
        for (int i = 0; i < 2; ++i)
        {
            pin = *(pin_iter++);
            pair_pin = NodeGui::get().m_pin_manager->getPair(pin->m_id);

            if (pair_pin)
            {
                Node* node = pair_pin->m_owner;
                
                if (node)
                {
                    this->m_threshold[i] = node->getContent<int32_t>(Pin::Type::VALUE);
                }
            }
        }

        this->process();
        this->resizeFrame();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_content->m_image);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}

void EdgeDetectionNode::drawInPins()
{
    // Draw pin for input image
    auto pin_iter = this->m_in_pins.begin();
    Pin* pin = *(pin_iter++);
    pin->drawAsInput();

    pin = *(pin_iter++);
    pin->drawAsInput();

    if (pin->m_connected_pins.empty())
    {
        ImGui::PushID(pin->m_id);
        ImGui::PushItemWidth(this->m_width);
        if (ImGui::SliderInt("", &this->m_threshold[0], 0, 1000))
        {
            this->setDirtyFlag();
        }
        ImGui::PopItemWidth();
        ImGui::PopID();
    }

    pin = *(pin_iter++);
    pin->drawAsInput();

    if (pin->m_connected_pins.empty())
    {
        ImGui::PushID(pin->m_id);
        ImGui::PushItemWidth(this->m_width);
        if (ImGui::SliderInt("", &this->m_threshold[1], 0, 1000))
        {
            this->setDirtyFlag();
        }
        ImGui::PopItemWidth();
        ImGui::PopID();
    }
}

void EdgeDetectionNode::process()
{
    if (!this->m_content->m_image.empty())
    {
        if (this->m_content->m_image.channels() != 1)
        {
            cv::cvtColor(this->m_content->m_image, this->m_content->m_image, cv::COLOR_BGR2GRAY);
        }

        double threshold[2];
        threshold[0] = std::min(this->m_threshold[0], this->m_threshold[1]);
        threshold[1] = std::max(this->m_threshold[0], this->m_threshold[1]);

        cv::Canny(this->m_content->m_image, this->m_content->m_image, threshold[0], threshold[1]);
    }
}

