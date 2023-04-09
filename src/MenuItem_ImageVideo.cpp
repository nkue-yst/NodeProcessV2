/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/04/09
 **********/

#include "MenuItem_ImageVideo.h"

#include "imgui.h"

void MenuItem_ImageVideo::draw()
{
    if (ImGui::BeginMenu("Image/Video"))
    {
        // Create new ImageNode
        if (ImGui::MenuItem("ImageSource"))
        {

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
