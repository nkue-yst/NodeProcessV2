/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/05/28
 **********/

#include "MenuItem_File.h"

#include "imgui.h"

#include "NodeGui.h"

void MenuItem_File::draw()
{
    if (ImGui::BeginMenu("File"))
    {
        // Open dialog to select image file
        if (ImGui::MenuItem("Open Image File"))
        {

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
