/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/03
 * Edited:  2023/08/04
 **********/

 #include "EdgeDetectionNode.h"

 #include "Logger.h"

EdgeDetectionNode::EdgeDetectionNode()
{
    this->m_threshold[0] = 255 / 3;
    this->m_threshold[1] = 255 / 3 * 2;

    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "EdgeDetection";
    this->m_color = NodeColor::GraphicsProcessingNode;

    this->m_image = cv::Mat::zeros(this->m_width, this->m_height, CV_8UC3);

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

cv::Mat EdgeDetectionNode::getContent(Pin::Type pin_type)
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

void EdgeDetectionNode::drawContent()
{
    if (this->m_need_update)
    {
        this->m_image.release();

        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(this->m_in_pins.at(0)->m_id);    // Connected pin

        if (pair_pin)
        {
            GraphicsNode* connected_node = dynamic_cast<GraphicsNode*>(pair_pin->m_owner);    // Connected node

            if (connected_node)    // If the connected node is valid
            {
                this->m_image = connected_node->getContent(Pin::Type::RGB);
            }
        }
        else
        {
            this->m_image = cv::Mat::zeros(this->m_width, this->m_height, CV_8UC3);
        }

        this->process();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_image);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}

void EdgeDetectionNode::drawInPins()
{
    // Draw pin for input image
    auto pin_iter = this->m_in_pins.begin();
    Pin* pin = *(pin_iter++);
    ImNodes::BeginInputAttribute(pin->m_id, pin->getShape());
    ImGui::TextUnformatted(pin->m_name.c_str());
    ImNodes::EndInputAttribute();

    // Threshold settings
    auto unify = [this]() -> void
    {
        if (this->m_threshold[0] > this->m_threshold[1])
        {
            int32_t temp = this->m_threshold[0];
            this->m_threshold[0] = this->m_threshold[1];
            this->m_threshold[1] = temp;
        }
    };

    pin = *(pin_iter++);
    ImNodes::BeginInputAttribute(pin->m_id, pin->getShape());
    ImGui::TextUnformatted(pin->m_name.c_str());
    ImNodes::EndInputAttribute();

    if (pin->m_connected_pins.empty())
    {
        ImGui::PushID(pin->m_id);
        ImGui::PushItemWidth(this->m_width);
        if (ImGui::SliderInt("", &this->m_threshold[0], 0, 255))
        {
            unify();
            this->setDirtyFlag();
        }
        ImGui::PopItemWidth();
        ImGui::PopID();
    }

    pin = *(pin_iter++);
    ImNodes::BeginInputAttribute(pin->m_id, pin->getShape());
    ImGui::TextUnformatted(pin->m_name.c_str());
    ImNodes::EndInputAttribute();

    if (pin->m_connected_pins.empty())
    {
        ImGui::PushID(pin->m_id);
        ImGui::PushItemWidth(this->m_width);
        if (ImGui::SliderInt("", &this->m_threshold[1], 0, 255))
        {
            unify();
            this->setDirtyFlag();
        }
        ImGui::PopItemWidth();
        ImGui::PopID();
    }
}

void EdgeDetectionNode::process()
{
    if (!this->m_image.empty())
    {
        if (this->m_image.channels() != 1)
        {
            cv::cvtColor(this->m_image, this->m_image, cv::COLOR_BGR2GRAY);
        }

        cv::Canny(this->m_image, this->m_image, this->m_threshold[0], this->m_threshold[1]);
    }
}

