/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/20
 **********/

#include "Pin.h"

#include "NodeGui.h"

Pin::Pin(std::string name)
{
    this->m_id = NodeGui::get().m_pin_manager->usePin();
}

Pin::~Pin()
{
}
