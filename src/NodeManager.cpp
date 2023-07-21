/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/06
 * Edited:  2023/07/20
 **********/

#include "NodeManager.h"

#include <iostream>

#include "Node.h"

NodeManager::NodeManager()
{
    std::cout << "[INFO]: Initializing NodeManager..." << std::endl;
    std::cout << "[INFO]: NodeManager: Creating empty list of nodes..." << std::endl;
}

NodeManager::~NodeManager()
{
    std::cout << "[INFO]: Terminating NodeManager..." << std::endl;
}

void NodeManager::addNode(Node* node)
{
    node->m_id = this->m_node_list.size();
    this->m_node_list.push_back(node);
}

void NodeManager::deleteNode()
{

}

void NodeManager::drawAll()
{
    for (Node* node : this->m_node_list)
    {
        node->draw();
    }
}
