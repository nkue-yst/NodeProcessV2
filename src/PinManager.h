/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/29
 **********/

#ifndef __PIN_MANAGER_H__
#define __PIN_MANAGER_H__

#include <algorithm>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

#include "Node.h"
#include "Pin.h"

struct Link
{
public:
    static bool isValid(std::pair<int32_t, int32_t> link)
    {
        return !(link.first < 0 && link.second < 0);
    }
};

class PinManager
{
public:
    PinManager();
    ~PinManager();

    [[nodiscard]]
    Pin* newPin(Node* owner, Pin::Type type, std::string name);

    void unusePin(int32_t id);

    Pin* getPin(int32_t pin_id);
    Pin* getPair(int32_t pin_id);
    void getLinkedId(const int32_t link_id, int32_t *start_id, int32_t *end_id);

    void addLink(std::pair<int32_t, int32_t> new_link);
    void disableLink(const int32_t link_id);

    std::vector<Pin*> m_pins;                            // Pin list
    std::vector<std::pair<int32_t, int32_t>> m_links;    // Pin link list

    std::set<int32_t> m_used_id;
};

#endif
