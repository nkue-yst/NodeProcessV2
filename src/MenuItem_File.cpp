/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/21
 **********/

#include "MenuItem_File.h"

#include "imgui.h"

#include "ImageNode.h"
#include "Node.h"
#include "NodeGui.h"

void MenuItem_File::draw()
{
    if (ImGui::BeginMenu("File"))
    {
        // Open dialog to select image file
        if (ImGui::MenuItem("Open Image File"))
        {
            Node* new_node = new ImageNode("../sample/sample1.png");

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        // Open dialog to select video file
        if (ImGui::MenuItem("Open Video file"))
        {

        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Exit button
        if (ImGui::MenuItem("Exit"))
        {
            NodeGui::get().quit();
        }

        ImGui::EndMenu();
    }
}
