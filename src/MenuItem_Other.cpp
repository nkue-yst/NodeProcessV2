/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/07
 * Edited:  2023/08/10
 **********/

#include "MenuItem_Other.h"

#include "BreakRGBNode.h"
#include "Constant.h"
#include "NodeGui.h"
#include "PreviewNode.h"

void MenuItem_Other::draw()
{
    if (ImGui::BeginMenu("Other"))
    {
        // Create preview node
        if (ImGui::MenuItem("Preview"))
        {
            NodeGui::get().m_node_manager->addNode(new PreviewNode());
        }

        // Create const value node
        if (ImGui::MenuItem("ConstInt"))
        {
            NodeGui::get().m_node_manager->addNode(new ConstantInt());
        }

        // Create break rgb node
        if (ImGui::MenuItem("Break RGB"))
        {
            NodeGui::get().m_node_manager->addNode(new BreakRGBNode());
        }

        ImGui::EndMenu();
    }
}
