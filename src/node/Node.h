/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/07/21
 **********/

#pragma once

#include <string>
#include <vector>

class Node
{
public:
    Node();
    ~Node();

    void draw();

private:
    void drawInPins();
    void drawOutPins();

protected:
    virtual void drawContent() = 0;

public:
    uint32_t m_id;
    std::string m_name;

    std::vector<class Pin*> m_in_pins;
    std::vector<class Pin*> m_out_pins;

    bool m_need_update;
};
