/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/21
 **********/

#include <cstdint>
#include <string>
#include <vector>

class Pin
{
public:
    Pin(std::string name);
    ~Pin();

    bool operator==(const std::string rhs) const
    {
        return this->m_name == rhs;
    }

    uint32_t m_id;
    std::string m_name;

    std::vector<class Node*> m_connected_nodes;
};
