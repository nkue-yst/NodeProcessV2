/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/05/28
 **********/

#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"
#include "ImGuiFileDialog.h"

#include "NodeManager.h"
#include "PinManager.h"
#include "MenuBar.h"

class NodeGui
{
private:
    NodeGui() = default;
    ~NodeGui() = default;

public:
    NodeGui(const NodeGui&) = delete;
    NodeGui& operator=(const NodeGui&) = delete;
    NodeGui(NodeGui&&) = delete;
    NodeGui& operator=(NodeGui&&) = delete;

    // Getter for singleton instance
    static inline NodeGui& get()
    {
        static NodeGui instance_;
        return instance_;
    }

    PinManager& getPinManager() const { return *this->m_pin_manager; }

    // Initialize systems
    bool init();

    // Main loop
    void loop();

    // Error and quit
    void abort();

    // Set quit flag
    void quit();

    // Cleanup for normal termination
    void cleanup();

    // Create main editor window
    void createWindow();

    // Create renderer for main window
    void createRenderer();

    // Setup ImGui systems
    void setupImGui();

private:
    bool m_done;

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
    PinManager* m_pin_manager;
};
