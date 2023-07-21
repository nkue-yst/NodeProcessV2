/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/21
 **********/

#include "Pin.h"

#include "Node.h"
#include "NodeGui.h"

Pin::Pin(Node* owner, int32_t id, Pin::Type type, std::string name)
    : m_id(id)
    , m_name(name)
    , m_type(type)
    , m_owner(owner)
{
}

Pin::~Pin()
{
}
