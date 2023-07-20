/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/18
 **********/

#include "MenuItem_ImageVideo.h"

#include "imgui.h"

#include "NodeGui.h"
#include "ImageNode.h"

void MenuItem_ImageVideo::draw()
{
    if (ImGui::BeginMenu("Image/Video"))
    {
        // Create new ImageNode
        if (ImGui::MenuItem("ImageSource"))
        {
            Node* new_node = new ImageNode("../sample/sample1.png");

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        // Create new VideoNode
        if (ImGui::MenuItem("VideoSource"))
        {

        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Create new BinariztionNode
        if (ImGui::MenuItem("Binarization"))
        {

        }

        // Create new EdgeDetectionNode
        if (ImGui::MenuItem("EdgeDetection"))
        {

        }

        // Create new GrayScalingNode
        if (ImGui::MenuItem("GrayScaling"))
        {

        }

        ImGui::EndMenu();
    }
}
