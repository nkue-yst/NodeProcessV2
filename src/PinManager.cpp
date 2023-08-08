/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/08/07
 **********/

#include "PinManager.h"

#include "Logger.h"
#include "Node.h"

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

Pin* PinManager::getPin(int32_t pin_id)
{
    auto pin = std::find_if(
        this->m_pins.begin(),
        this->m_pins.end(),
        [pin_id](Pin* pin)
        {
            return pin->m_id == pin_id;
        }
    );

    return (pin != this->m_pins.end()) ? *pin : nullptr;
}

Pin* PinManager::getPair(int32_t pin_id)
{
    Pin* pair_pin = nullptr;

    for (auto link : this->m_links)
    {
        if (link.first == pin_id)
        {
            pair_pin = this->getPin(link.second);
            break;
        }
        else if (link.second == pin_id)
        {
            pair_pin = this->getPin(link.first);
            break;
        }
    }

    return pair_pin;
}

void PinManager::getLinkedId(const int32_t link_id, int32_t *start_id, int32_t *end_id)
{
    *start_id = this->m_links.at(link_id).first;
    *end_id = this->m_links.at(link_id).second;
}

int32_t PinManager::getLinkId(const int32_t pin_id)
{
    //for (auto link : this->m_links)
    int32_t link_num = this->m_links.size();
    for (int32_t i = 0; i < link_num; ++i)
    {
        if (this->m_links.at(i).first == pin_id || this->m_links.at(i).second == pin_id)
        {
            return i;
        }
    }

    return -1;
}

bool PinManager::addLink(std::pair<int32_t, int32_t> new_link)
{
    ////////////////////////////////////////////////////////
    ///// Check if it is a connectable pin combination /////
    ////////////////////////////////////////////////////////
    Pin* parent_pin = this->getPin(new_link.first);
    Pin* child_pin = this->getPin(new_link.second);

    if (!parent_pin->canConnect(*child_pin))
    {
        return false;
    }

    /////////////////////////////////////////////////
    ///// If already linked, break the old link /////
    /////////////////////////////////////////////////
    while (true)
    {
        int32_t old_link_id = this->getLinkId(new_link.second);

        if (old_link_id >= 0)
        {
            this->disableLink(old_link_id);
            continue;
        }

        break;
    }

    //////////////////////////////
    ///// Set connected pins /////
    //////////////////////////////
    parent_pin->m_connected_pins.push_back(child_pin);
    child_pin->m_connected_pins.push_back(parent_pin);

    // Add to list
    this->m_links.push_back(new_link);

    return true;
}

void PinManager::disableLink(const int32_t link_id)
{
    int32_t parent_pin_id, child_pin_id;
    this->getLinkedId(link_id, &parent_pin_id, &child_pin_id);

    /////////////////////////////
    ///// Disable child pin /////
    /////////////////////////////
    Pin* pin = this->getPin(parent_pin_id);
    auto iter = std::find_if(pin->m_connected_pins.begin(), pin->m_connected_pins.end(),[child_pin_id](Pin* pin_iter)
    {
        return child_pin_id == pin_iter->m_id;
    });
    pin->m_connected_pins.erase(iter);

    //////////////////////////////
    ///// Disable parent pin /////
    //////////////////////////////
    pin = this->getPin(child_pin_id);
    iter = std::find_if(pin->m_connected_pins.begin(), pin->m_connected_pins.end(),[parent_pin_id](Pin* pin_iter)
    {
        return parent_pin_id == pin_iter->m_id;
    });
    pin->m_connected_pins.erase(iter);

    // Remove from list
    this->m_links.at(link_id).first  = -1;
    this->m_links.at(link_id).second = -1;
}
