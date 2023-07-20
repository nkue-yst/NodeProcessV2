/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/07/20
 **********/

#include "NodeGui.h"

#include <cstdlib>
#include <iostream>
#include <memory>

bool NodeGui::init()
{
    std::cout << "[INFO]: Initializing components..." << std::endl;

    this->m_done = false;

    this->m_win_width = 1280;
    this->m_win_height = 720;
    this->m_bg_color = ImVec4(0.4f, 0.4f, 0.4f, 1.f);

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

    // Setup menu bar
    this->m_menu_bar = new MenuBar();

    // Setup components
    this->m_node_manager = new NodeManager();
    this->m_pin_manager = new PinManager();

    std::cout << "[INFO]: Components initializaion complete." << std::endl;

    return true;
}

void NodeGui::loop()
{
    // Font settings
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Build();

    while (!this->m_done)
    {
        // Process terminate input
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            ImGui_ImplSDL2_ProcessEvent(&ev);

            if (ev.type == SDL_QUIT)
            {
                this->m_done = true;
            }
            else if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_CLOSE && ev.window.windowID == SDL_GetWindowID(this->m_win))
            {
                this->m_done = true;
            }
        }

        // Update main window size
        SDL_GetWindowSize(this->m_win, &this->m_win_width, &this->m_win_height);

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Start drawing window
        ImGui::SetNextWindowSize(ImVec2(this->m_win_width, this->m_win_height), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::Begin("NodeEditor", nullptr, ImGuiWindowFlags_MenuBar);

        /////////////////////////
        ///// Draw menu bar /////
        /////////////////////////
        this->m_menu_bar->draw();

        /////////////////////
        //// Draw nodes /////
        /////////////////////
        ImNodes::BeginNodeEditor();
        this->m_node_manager->drawAll();
        ImNodes::EndNodeEditor();

        // End drawing window
        ImGui::End();

        /////////////////
        /// Rendering ///
        /////////////////
        ImGui::Render();

        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(
            this->m_bg_color.x * this->m_bg_color.w,
            this->m_bg_color.y * this->m_bg_color.w,
            this->m_bg_color.z * this->m_bg_color.w,
            this->m_bg_color.w
        );
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(this->m_win);
    }
}

void NodeGui::abort()
{
    this->cleanup();

    std::cerr << "[ERROR]: An error occurred and the program will now terminate." << std::endl;
    std::exit(1);
}

void NodeGui::quit()
{
    this->m_done = true;
}

void NodeGui::cleanup()
{
    std::cout << "[INFO]: Clean up components..." << std::endl;

    // Clean up components
    delete this->m_menu_bar;
    delete this->m_node_manager;

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
        "NodeProcessing-V2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
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

    // Set style
    ImGui::StyleColorsDark();
    ImNodes::SetNodeGridSpacePos(1, ImVec2(200.f, 200.f));
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
}
