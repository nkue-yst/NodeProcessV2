/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/07/22
 **********/

#include "NodeGui.h"

#include <cstdlib>
#include <memory>

#include "Log.h"
#include "Node.h"

bool NodeGui::init()
{
    log(LogType::LOG, "Initializing components...");

    this->m_done = false;

    this->m_win_width = 1280;
    this->m_win_height = 720;
    this->m_bg_color = ImVec4(0.4f, 0.4f, 0.4f, 1.f);

    // Initialize SDL system
    SDL_Init(SDL_INIT_VIDEO);

    /////////////////////////////
    ///// Initialize OpenGL /////
    /////////////////////////////
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //////////////////////
    ///// Setup menu /////
    //////////////////////
    this->m_menu_bar = new MenuBar();
    this->m_file_dialog = new FileDialog();

    ////////////////////////////
    ///// Setup components /////
    ////////////////////////////
    this->m_node_manager = new NodeManager();
    this->m_pin_manager = new PinManager();

    log(LogType::LOG, "Components initialization complete.");

    return true;
}

void NodeGui::loop()
{
    // Font settings
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Build();

    /////////////////////
    ///// Main loop /////
    /////////////////////
    while (!this->m_done)
    {
        ///////////////////////////////////
        ///// Process terminate input /////
        ///////////////////////////////////
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            ImGui_ImplSDL2_ProcessEvent(&ev);

            if (ev.type == SDL_QUIT)
            {
                this->m_done = true;
            }
            else if (
                ev.type == SDL_WINDOWEVENT &&
                ev.window.event == SDL_WINDOWEVENT_CLOSE &&
                ev.window.windowID == SDL_GetWindowID(this->m_win)
            )
            {
                this->m_done = true;
            }
        }

        // Update main window size
        SDL_GetWindowSize(this->m_win, &this->m_win_width, &this->m_win_height);

        /////////////////////////////////
        ///// Start new ImGui frame /////
        /////////////////////////////////
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ////////////////////////////////
        ///// Start drawing window /////
        ////////////////////////////////
        ImGui::SetNextWindowSize(ImVec2(this->m_win_width, this->m_win_height), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::Begin("NodeEditor", nullptr, ImGuiWindowFlags_MenuBar);

        /////////////////////////
        ///// Draw menu bar /////
        /////////////////////////
        this->m_menu_bar->draw();

        ////////////////////////////
        ///// Draw file dialog /////
        ////////////////////////////
        this->m_file_dialog->draw();

        ////////////////////////
        ///// Update links /////
        ////////////////////////
        {

            int32_t start_id, end_id;

            // New created link
            if (ImNodes::IsLinkCreated(&start_id, &end_id))
            {
                // Add new link to list
                this->m_pin_manager->addLink(std::make_pair(start_id, end_id));

                // Set dirty flag for all child nodes
                std::vector<Node*> node_list = this->m_pin_manager->getPin(start_id)->m_connected_nodes;
                for (Node* node : node_list)
                {
                    node->setDirtyFlag();
                }
            }

            // Disconnect link
            int32_t link_id;
            if (ImNodes::IsLinkDestroyed(&link_id))
            {
                // Disable disconnected link
                this->m_pin_manager->getLinkedId(link_id, &start_id, &end_id);
                this->m_pin_manager->disableLink(link_id);

                // Set dirty flag for all child nodes
                this->m_pin_manager->getPin(end_id)->m_owner->setDirtyFlag();
            }

        }

        /////////////////////////////////////
        ///// Begin drawing node editor /////
        /////////////////////////////////////
        ImNodes::BeginNodeEditor();

        /////////////////////
        //// Draw nodes /////
        /////////////////////
        this->m_node_manager->drawAll();

        //////////////////////
        ///// Draw links /////
        //////////////////////
        int32_t link_num = this->m_pin_manager->m_links.size();
        for (int32_t i = 0; i < link_num; ++i)
        {
            const std::pair<int32_t, int32_t> link = this->m_pin_manager->m_links.at(i);

            if (Link::isValid(link))
            {
                ImNodes::Link(i, link.first, link.second);
            }
        }

        ///////////////////////
        ///// End drawing /////
        ///////////////////////
        ImNodes::EndNodeEditor();
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

    log(LogType::ERROR, "An error occurred and the program will now terminate.");
    std::exit(1);
}

void NodeGui::quit()
{
    this->m_done = true;
}

void NodeGui::cleanup()
{
    log(LogType::LOG, "Clean up components...");

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
