/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/07
 * Edited:  2023/08/07
 **********/

#pragma once

#include "Node.h"

class ConstantInt : public Node
{
public:
    ConstantInt();

    void drawContent() override;
};
