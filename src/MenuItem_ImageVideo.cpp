/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/31
 **********/

#include "MenuItem_ImageVideo.h"

#include "imgui.h"

#include "NodeGui.h"
#include "BinarizationNode.h"
#include "GrayScallingNode.h"
#include "HistogramNode.h"
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
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "PROCESSING");

        // Create new GrayScalingNode
        if (ImGui::MenuItem("GrayScaling"))
        {
            Node* new_node = new GrayScallingNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        // Create new BinarizationNode
        if (ImGui::MenuItem("Binarization"))
        {
            Node* new_node = new BinarizationNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "ANALYZE");

        // Create new HistgramNode
        if (ImGui::MenuItem("Histgram"))
        {
            Node* new_node = new HistogramNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        ImGui::EndMenu();
    }
}
