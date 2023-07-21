/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/21
 **********/

#ifndef __PIN_H__
#define __PIN_H__

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

    Pin(class Node* owner, int32_t id, Type type, std::string name);
    ~Pin();

    bool operator==(const Type rhs) const
    {
        return this->m_type == rhs;
    }

    bool operator!=(const Type rhs) const
    {
        return this->m_type != rhs;
    }

    int32_t m_id;
    std::string m_name;
    Type m_type;

    std::vector<class Node*> m_connected_nodes;

    class Node* m_owner;
};

#endif
