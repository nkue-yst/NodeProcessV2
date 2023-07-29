/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/29
 **********/

#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include <iostream>

class MenuItem
{
public:
    virtual ~MenuItem() = default;

    virtual void draw() = 0;
};

#endif
