/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/04/05
 **********/

#pragma once

#include "NodeManager.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"
#include "ImGuiFileDialog.h"

#include "MenuBar.h"

class NodeGui
{
public:
    NodeGui();
    ~NodeGui();

    // Initialize systems
    bool init();

    // Main loop
    void loop();

    // Error and quit
    void abort();

    // Normal termination
    void quit();

    // Create main editor window
    void createWindow();

    // Create renderer for main window
    void createRenderer();

    // Setup ImGui systems
    void setupImGui();

private:
    int32_t m_win_width;
    int32_t m_win_height;

    SDL_Window* m_win;
    SDL_GLContext m_gl_context;
    SDL_Renderer* m_renderer;

    ImGuiContext* m_imgui_context;
    ImNodesContext* m_imnodes_context;

    ImVec4 m_bg_color;

    MenuBar* m_menu_bar;

    NodeManager* m_node_manager;
};
