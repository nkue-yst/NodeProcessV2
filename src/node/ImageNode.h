/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/08/06
 **********/

#pragma once

#include "GraphicsNode.h"

class ImageNode : public GraphicsNode
{
public:
    ImageNode(std::string file_path);

    template<typename T>
    T getContent(Pin::Type pin_type)
    {
        if (pin_type == Pin::m_type::RGB)
            return this->m_content->m_image;
    }

private:
    void drawContent() override;
    bool loadData(std::string file_path);
};
