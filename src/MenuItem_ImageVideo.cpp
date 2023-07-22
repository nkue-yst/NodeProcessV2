/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/22
 **********/

#include "MenuItem_ImageVideo.h"

#include "imgui.h"

#include "NodeGui.h"
#include "GrayScallingNode.h"
#include "ImageNode.h"

void MenuItem_ImageVideo::draw()
{
    if (ImGui::BeginMenu("Image/Video"))
    {
        // Create new ImageNode
        if (ImGui::MenuItem("ImageSource"))
        {
            const char* filters = "Image files (*.png *.jpg *.jpeg){.png,.jpg,.jpeg}";
            ImGuiFileDialog::Instance()->OpenDialog("SelectImageDlgkey", "Select Image File", filters, ".");
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Create new GrayScalingNode
        if (ImGui::MenuItem("GrayScaling"))
        {
            Node* new_node = new GrayScallingNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        ImGui::EndMenu();
    }
}
