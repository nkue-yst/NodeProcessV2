/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/07/18
 **********/

#ifndef __MEDIA_NODE_H__
#define __MEDIA_NODE_H__

#include <string>

#include "Node.h"

class MediaNode : public Node
{
protected:
    virtual bool loadData(std::string file_path) = 0;
};

#endif
