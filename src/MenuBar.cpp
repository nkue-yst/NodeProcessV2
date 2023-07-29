/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/07/28
 **********/

#include "MenuBar.h"

#include "imgui.h"

#include "Logger.h"
#include "MenuItem.h"
#include "MenuItem_File.h"
#include "MenuItem_ImageVideo.h"
#include "MenuItem_Audio.h"

MenuBar::MenuBar()
{
    LOG("Initialize MenuBar.");

    MenuItem* menu_file = new MenuItem_File();
    MenuItem* menu_image_video = new MenuItem_ImageVideo();
    MenuItem* menu_audio = new MenuItem_Audio();

    this->m_menu_items.push_back(menu_file);
    this->m_menu_items.push_back(menu_image_video);
    this->m_menu_items.push_back(menu_audio);
}

MenuBar::~MenuBar()
{
    LOG("Destroy MenuBar.");

    for (auto item : this->m_menu_items)
    {
        delete item;
    }
}

void MenuBar::draw()
{
    if (ImGui::BeginMenuBar())
    {
        for (MenuItem* menu_item : this->m_menu_items)
        {
            menu_item->draw();
        }

        ImGui::EndMenuBar();
    }
}
