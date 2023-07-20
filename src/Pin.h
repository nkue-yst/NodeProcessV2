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
    enum class Type
    {
        RGB,         // カラー情報
    
        UNDEFINED    // 未定義
    };

    Pin(Type type, std::string name);
    ~Pin();

    bool operator==(const Type rhs) const
    {
        return this->m_type == rhs;
    }

    bool operator!=(const Type rhs) const
    {
        return this->m_type != rhs;
    }

    uint32_t m_id;
    std::string m_name;
    Type m_type;

    std::vector<class Node*> m_connected_nodes;
};
