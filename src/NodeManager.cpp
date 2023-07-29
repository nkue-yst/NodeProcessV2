/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/06
 * Edited:  2023/07/29
 **********/

#include "NodeManager.h"

#include <iostream>

#include "Logger.h"
#include "Node.h"

NodeManager::NodeManager()
{
    LOG("Initialize NodeManager.");
}

NodeManager::~NodeManager()
{
    LOG("Destroy NodeManager.");

    this->deleteAllNode();
}

void NodeManager::addNode(Node* node)
{
    node->m_id = this->m_node_list.size();
    this->m_node_list.push_back(node);

    DEBUG("Created node. (id: " + std::to_string(node->m_id) + ", name: " + node->m_name + ")");
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

void NodeManager::deleteAllNode()
{
    for (auto node : this->m_node_list)
    {
        DEBUG("Destroy node. (id: " + std::to_string(node->m_id) + ", name: " + node->m_name + ")");

        delete node;
    }
}
