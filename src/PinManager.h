/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/21
 **********/

#include <algorithm>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

#include "Node.h"
#include "Pin.h"

class PinManager
{
public:
    PinManager();
    ~PinManager();

    [[nodiscard]]
    Pin* newPin(Node* owner, Pin::Type type, std::string name);

    void unusePin(int32_t id);

    Pin* getPin(int32_t id)
    {
        auto pin = std::find_if(
            this->m_pins.begin(),
            this->m_pins.end(),
            [id](Pin* pin)
            {
                return pin->m_id == id;
            }
        );

        return (pin != this->m_pins.end()) ? *pin : nullptr;
    }

    Pin* getPair(int32_t id)
    {
        Pin* pair_pin = nullptr;

        for (auto link : this->m_links)
        {
            if (link.first == id)
            {
                pair_pin = this->getPin(link.second);
                break;
            }
            else if (link.second == id)
            {
                pair_pin = this->getPin(link.first);
                break;
            }
        }

        return pair_pin;
    }

    void addLink(std::pair<int32_t, int32_t> new_link)
    {
        ///////////////////////////
        ///// Set parent node /////
        ///////////////////////////
        Node* parent_node = this->getPin(new_link.first)->m_owner;
        this->getPin(new_link.second)->m_connected_nodes.push_back(parent_node);

        //////////////////////////
        ///// Set child node /////
        //////////////////////////
        Node* child_node = this->getPin(new_link.second)->m_owner;
        this->getPin(new_link.first)->m_connected_nodes.push_back(child_node);

        // Add to list
        this->m_links.push_back(new_link);
    }

    std::vector<Pin*> m_pins;                            // Pin list
    std::vector<std::pair<int32_t, int32_t>> m_links;    // Pin link list

    std::set<int32_t> m_used_id;
};
