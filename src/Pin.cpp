/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/21
 **********/

#include "Pin.h"

#include "Logger.h"
#include "Node.h"
#include "NodeGui.h"

Pin::Pin(Node* owner, int32_t id, Pin::Type type, std::string name)
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
