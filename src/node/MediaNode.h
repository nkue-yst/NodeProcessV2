/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/05/26
 **********/

#include <iostream>

#include "Node.h"
#include "Media.h"

class MediaNode : public Node
{
public:
    MediaNode(const char* file_path)
    {
        if (!this->loadData(file_path))
        {
            std::cerr << "[INFO]: Failed to load: \"" << file_path << "\"" << std::endl;
        }
    }

protected:
    virtual bool loadData(const char* file_path)
    {
        std::cerr << "[DEBUG]: Not implemented." << ": MediaNode::loadData()" << std::endl;

        return false;
    }

    Media* m_content;
};
