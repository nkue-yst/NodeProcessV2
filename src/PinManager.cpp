/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/20
 **********/

#include "PinManager.h"

#include <iostream>

PinManager::PinManager()
{
}

PinManager::~PinManager()
{
}

uint32_t PinManager::usePin()
{
    // Find the smallest ID not in use
    for (uint32_t i = 0; i < UINT32_MAX; ++i)
    {
        if (this->m_used_id.find(i) == this->m_used_id.end())
        {
            this->m_used_id.insert(i);
            return i;
        }
    }

    return 0;
}

void PinManager::unusePin(uint32_t id)
{
    this->m_used_id.erase(id);
}
