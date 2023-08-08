/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/09
 * Edited:  2023/08/09
 **********/
 
#pragma once

#include "Node.h"

class BreakRGBNode : public Node
{
public:
    BreakRGBNode();

private:
    void drawContent() override;
};
