/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/07
 * Edited:  2023/08/07
 **********/

#include "MenuItem_Other.h"

#include "Constant.h"
#include "NodeGui.h"

void MenuItem_Other::draw()
{
    if (ImGui::BeginMenu("Other"))
    {
        // Create const value node
        if (ImGui::MenuItem("ConstInt"))
        {
            NodeGui::get().m_node_manager->addNode(new ConstantInt());
        }

        ImGui::EndMenu();
    }
}
