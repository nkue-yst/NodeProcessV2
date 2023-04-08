/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/06
 * Edited:  2023/04/08
 **********/

#include <vector>

class NodeManager
{
public:
    NodeManager();
    ~NodeManager();

private:
    std::vector<class Node*> m_node_list;
};
