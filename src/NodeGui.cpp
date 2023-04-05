/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/04/05
 **********/

#include "NodeGui.h"

#include <cstdlib>
#include <iostream>

NodeGui::NodeGui()
    : m_win_width(1280)
    , m_win_height(720)
{
}

NodeGui::~NodeGui()
{
}

bool NodeGui::init()
{
    // Initialize SDL system
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    return true;
}

void NodeGui::abort()
{
    this->quit();

    std::cerr << "[NPV2]: An error occurred and the program will now terminate." << std::endl;
    std::exit(1);
}

void NodeGui::quit()
{
    // Clean up SDL
    SDL_DestroyRenderer(this->m_renderer);
    SDL_DestroyWindow(this->m_win);

    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    // Quit SDL system
    SDL_Quit();
}

void NodeGui::createWindow()
{
    SDL_WindowFlags win_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    this->m_win = SDL_CreateWindow(
        "NodeProcessing",
        100,
        100,
        this->m_win_width,
        this->m_win_height,
        win_flags
    );
}

void NodeGui::createRenderer()
{
    // Setup OpenGL
    this->m_gl_context = SDL_GL_CreateContext(this->m_win);
    SDL_GL_MakeCurrent(this->m_win, this->m_gl_context);
    SDL_GL_SetSwapInterval(1);

    // Create main renderer
    this->m_renderer = SDL_CreateRenderer(
        this->m_win,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
}

void NodeGui::setupImGui()
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    this->m_imgui_context = ImGui::CreateContext();
    this->m_imnodes_context = ImNodes::CreateContext();

    const char* glsl_version = "#version 130";

    ImGui_ImplSDL2_InitForOpenGL(this->m_win, this->m_gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
