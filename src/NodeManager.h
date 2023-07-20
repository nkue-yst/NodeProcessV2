/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/06
 * Edited:  2023/07/20
 **********/

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
    std::vector<class Node*> m_node_list;
};
