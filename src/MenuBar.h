/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/04/09
 **********/

#pragma once

#include <vector>

class MenuBar
{
public:
    MenuBar();
    ~MenuBar();

    void draw();

private:
    std::vector<class MenuItem*> m_menu_items;
};
