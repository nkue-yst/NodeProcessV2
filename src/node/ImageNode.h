/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/07/21
 **********/

#ifndef __IMAGE_NODE_H__
#define __IMAGE_NODE_H__

#include "MediaNode.h"

class ImageNode : public MediaNode
{
public:
    ImageNode(std::string file_path);

    NodeContent& getContent(Pin::Type pin_type) override;

private:
    void drawContent() override;
    bool loadData(std::string file_path) override;
};

#endif
