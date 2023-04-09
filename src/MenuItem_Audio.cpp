/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/04/09
 **********/

#include "MenuItem_Audio.h"

#include "imgui.h"

void MenuItem_Audio::draw()
{
    if (ImGui::BeginMenu("Audio"))
    {
        // Create new AudioNode
        if (ImGui::MenuItem("AudioSource"))
        {

        }

        ImGui::EndMenu();
    }
}
