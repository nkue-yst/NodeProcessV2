/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/20
 **********/

#include <cstdint>
#include <string>
#include <vector>

class Pin
{
public:
    Pin(std::string name);
    ~Pin();

    uint32_t m_id;
    std::string m_name;

    std::vector<class Node*> m_connected_nodes;
};
