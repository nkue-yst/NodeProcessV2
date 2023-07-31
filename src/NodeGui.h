/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/07/31
 **********/

#pragma once

#include <memory>

#include "SDL.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"
#include "ImGuiFileDialog.h"
#include "implot.h"

#include "FileDialog.h"
#include "NodeManager.h"
#include "PinManager.h"

#include "Logger.h"
#include "TimeProfiler.h"

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

    SDL_Window* m_win;
    SDL_GLContext m_gl_context;
    SDL_Renderer* m_renderer;

    ImGuiContext* m_imgui_context;
    ImNodesContext* m_imnodes_context;
    ImPlotContext* m_implot_context;

    ImVec4 m_bg_color;

    MenuBar* m_menu_bar;

    FileDialog* m_file_dialog;

public:
    int32_t m_win_width;
    int32_t m_win_height;

    class NodeManager* m_node_manager;
    class PinManager* m_pin_manager;

    std::unique_ptr<class Logger> m_logger;
    std::unique_ptr<class TimeProfiler> m_time_profiler;
};
