/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/08/09
 **********/

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "imgui.h"

class Pin
{
public:
    // Pin type for input or output data
    enum Type
    {
        RGB,         // Color data
        Red,         // Color data (red)
        Green,       // Color data (green)
        Blue,        // Color data (blue)
        VALUE,       // Number value
    
        UNDEFINED,   // 未定義
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

    bool canConnect(Pin& pair_pin);

    void drawAsInput();
    void drawAsOutput();

    int getShape();

    int32_t m_id;
    std::string m_name;
    Type m_type;

    std::vector<class Pin*> m_connected_pins;

    class Node* m_owner;
};
