/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/28
 **********/

#include "PinManager.h"

#include "Logger.h"

PinManager::PinManager()
{
    LOG("Initialize PinManager.");
}

PinManager::~PinManager()
{
    LOG("Destroy PinManager.");

    for (auto pin : this->m_pins)
    {
        delete pin;
    }
}

Pin* PinManager::newPin(Node* owner, Pin::Type type, std::string name)
{
    Pin* new_pin = nullptr;

    // Find the smallest ID not in use
    for (int32_t i = 0; i < INT32_MAX; ++i)
    {
        if (this->m_used_id.find(i) == this->m_used_id.end())
        {
            this->m_used_id.insert(i);

            new_pin = new Pin(owner, i, type, name);
            this->m_pins.push_back(new_pin);

            break;
        }
    }

    return new_pin;
}

void PinManager::unusePin(int32_t id)
{
    this->m_used_id.erase(id);
}
