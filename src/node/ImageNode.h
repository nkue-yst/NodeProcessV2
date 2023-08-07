/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/08/08
 **********/

#pragma once

#include "GraphicsNode.h"

class ImageNode : public GraphicsNode
{
public:
    ImageNode(std::string file_path);

private:
    void drawContent() override;
    bool loadData(std::string file_path);
};
