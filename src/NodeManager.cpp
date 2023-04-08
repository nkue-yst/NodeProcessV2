/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/06
 * Edited:  2023/04/06
 **********/

#include "NodeManager.h"

#include "Node.h"

NodeManager::NodeManager()
{
}

NodeManager::~NodeManager()
{
}

void NodeManager::addNode(Node* node)
{
    this->m_node_list.push_back(node);
}

void NodeManager::deleteNode()
{

}
