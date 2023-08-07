/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/08/08
 **********/

#include "Pin.h"

#include "Logger.h"
#include "NodeStyle.h"

Pin::Pin(class Node* owner, int32_t id, Pin::Type type, std::string name)
    : m_id(id)
    , m_name(name)
    , m_type(type)
    , m_owner(owner)
{
    DEBUG("Created pin.  (id: " + std::to_string(this->m_id) + ", name: " + this->m_name + ")");
}

Pin::~Pin()
{
    DEBUG("Destroy pin.  (id: " + std::to_string(this->m_id) + ", name: " + this->m_name + ")");
}

void Pin::drawAsInput()
{
    ImNodes::PushColorStyle(ImNodesCol_Pin, PIN_COLOR(this->m_type));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, multiplyIM_COL(PIN_COLOR(this->m_type), 1.2));

    ImNodes::BeginInputAttribute(this->m_id, this->getShape());
    ImGui::TextUnformatted(this->m_name.c_str());
    ImNodes::EndInputAttribute();

    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}

void Pin::drawAsOutput()
{
    ImNodes::PushColorStyle(ImNodesCol_Pin, PIN_COLOR(this->m_type));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, multiplyIM_COL(PIN_COLOR(this->m_type), 1.2));

    ImNodes::BeginOutputAttribute(this->m_id, this->getShape());
    const float label_width = ImGui::CalcTextSize(this->m_name.c_str()).x;
    ImGui::Indent(95.f - label_width);
    ImGui::TextUnformatted(this->m_name.c_str());
    ImNodes::EndOutputAttribute();

    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}

int Pin::getShape()
{
    ImNodesPinShape pin_shape;

    switch (this->m_type)
    {
    case Pin::Type::RGB:
        pin_shape = ImNodesPinShape_CircleFilled;
        break;

    case Pin::Type::VALUE:
        pin_shape = ImNodesPinShape_QuadFilled;
        break;

    default:
        pin_shape = ImNodesPinShape_Circle;
        break;
    }

    return pin_shape;
}
