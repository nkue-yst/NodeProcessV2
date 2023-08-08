/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/08/09
 **********/

#include "Pin.h"

#include "Logger.h"
#include "Node.h"
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

bool Pin::canConnect(Pin& pair_pin)
{
    Pin::Type type = this->m_type;
    Pin::Type pair_type = pair_pin.m_type;

    if (type <= Pin::Type::Blue && pair_type <= Pin::Type::Blue)
    {
        return true;
    }

    return type == pair_type;
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
    ImGui::Indent(this->m_owner->m_node_width - label_width);
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

    case Pin::Type::Red:
    case Pin::Type::Green:
    case Pin::Type::Blue:
        pin_shape = ImNodesPinShape_Circle;
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
