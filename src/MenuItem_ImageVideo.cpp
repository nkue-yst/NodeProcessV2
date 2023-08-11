/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/08/11
 **********/

#include "MenuItem_ImageVideo.h"

#include "imgui.h"

#include "NodeGui.h"

#include "BinarizationNode.h"
#include "BreakRGBNode.h"
#include "ColorBlendNode.h"
#include "EdgeDetectionNode.h"
#include "GrayScallingNode.h"
#include "HistogramNode.h"
#include "ImageNode.h"
#include "PreviewNode.h"

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

        // Create new VideoNode
        if (ImGui::MenuItem("VideoSource"))
        {
            const char* filters = "Video files (*.mp4 *.mov){.mp4,.mov}";
            ImGuiFileDialog::Instance()->OpenDialog("SelectVideoDlgkey", "Select Video File", filters, ".");
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.f), "PROCESSING");

        // Create new BinarizationNode
        if (ImGui::MenuItem("Binarization"))
        {
            Node* new_node = new BinarizationNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        // Create new EdgeDetectionNode
        if (ImGui::MenuItem("EdgeDetection"))
        {
            Node* new_node = new EdgeDetectionNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        // Create new GrayScalingNode
        if (ImGui::MenuItem("GrayScaling"))
        {
            Node* new_node = new GrayScallingNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.f), "ANALYZE");

        // Create new HistgramNode
        if (ImGui::MenuItem("Histgram"))
        {
            Node* new_node = new HistogramNode();

            NodeGui::get().m_node_manager->addNode(new_node);
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.f), "UTILITY");

        // Create preview node
        if (ImGui::MenuItem("Preview"))
        {
            NodeGui::get().m_node_manager->addNode(new PreviewNode());
        }

        // Create break rgb node
        if (ImGui::MenuItem("Break RGB"))
        {
            NodeGui::get().m_node_manager->addNode(new BreakRGBNode());
        }

        // Create color blend node
        if (ImGui::MenuItem("Color Blend"))
        {
            NodeGui::get().m_node_manager->addNode(new ColorBlendNode());
        }

        ImGui::EndMenu();
    }
}
