/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/04/05
 **********/

#include "SDL.h"
#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"
#include "ImGuiFileDialog.h"

class NodeGui
{
public:
    NodeGui();
    ~NodeGui();

    // Initialize systems
    bool init();

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
    uint32_t m_win_width;
    uint32_t m_win_height;

    SDL_Window* m_win;
    SDL_GLContext m_gl_context;
    SDL_Renderer* m_renderer;

    ImGuiContext* m_imgui_context;
    ImNodesContext* m_imnodes_context;
};
