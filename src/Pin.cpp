/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/04/09
 **********/

#include "Pin.h"

#include "NodeGui.h"

Pin::Pin()
{
    this->m_id = NodeGui::get().getPinManager().usePin();
}

Pin::~Pin()
{
}
