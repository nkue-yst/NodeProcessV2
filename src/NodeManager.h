/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/06
 * Edited:  2023/07/29
 **********/

#ifndef __NODE_MANAGER_H__
#define __NODE_MANAGER_H__

#include <vector>

class NodeManager
{
public:
    NodeManager();
    ~NodeManager();

    void addNode(class Node* node);
    void deleteNode();

    void drawAll();

private:
    void deleteAllNode();

    std::vector<class Node*> m_node_list;
};

#endif
