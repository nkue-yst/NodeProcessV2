/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/04/09
 **********/

#include <cstdint>
#include <vector>

#include "Node.h"

class Pin
{
public:
    Pin();
    ~Pin();

    uint32_t m_id;
    const char* m_name;

    std::vector<class Node*> m_connected_nodes;
};
