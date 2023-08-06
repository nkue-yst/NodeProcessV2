/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/08/07
 **********/

#include "NodeGui.h"

#include <cstdlib>
#include <memory>

#include "Node.h"
#include "Pin.h"

#include "HistogramNode.h"
#include "ImageNode.h"

bool NodeGui::init()
{
    this->m_logger = std::make_unique<Logger>();
    this->m_time_profiler = std::make_unique<TimeProfiler>();

    LOG("Initialize NodeGui.");
    LOG("Initialize components...");

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

    ////////////////////////////
    ///// Setup components /////
    ////////////////////////////
    this->m_node_manager = new NodeManager();
    this->m_pin_manager = new PinManager();

    //////////////////////
    ///// Setup menu /////
    //////////////////////
    this->m_menu_bar = new MenuBar();
    this->m_file_dialog = new FileDialog();

    LOG("Components initialization complete.");

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
        ImGui::Begin("NodeEditor", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

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

            // Drag for new link
            if (ImNodes::IsLinkStarted(&start_id))
            {
                Pin* start_pin = this->m_pin_manager->getPin(start_id);
                uint32_t color = PIN_COLOR(start_pin->m_type);

                ImNodes::PushColorStyle(ImNodesCol_Link, color);
                ImNodes::PushColorStyle(ImNodesCol_LinkHovered, color);
                ImNodes::PushColorStyle(ImNodesCol_LinkSelected, color);
            }

            // Drop for new link
            if (ImNodes::IsLinkDropped(&start_id))
            {
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
            }

            // New created link
            if (ImNodes::IsLinkCreated(&start_id, &end_id))
            {
                // Add new link to list
                if (this->m_pin_manager->addLink(std::make_pair(start_id, end_id)))
                {
                    //////////////////////////////////////////////
                    ///// Set dirty flag for all child nodes /////
                    //////////////////////////////////////////////
                    Node* start_node = this->m_pin_manager->getPin(start_id)->m_owner;
                    std::vector<Pin*> pin_list = this->m_pin_manager->getPin(start_id)->m_connected_pins;

                    for (Pin* pin : pin_list)
                    {
                        pin->m_owner->setDirtyFlag(start_node->m_priority + 1);
                    }
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
                Pin* start_pin = this->m_pin_manager->getPin(link.first);
                uint32_t color = PIN_COLOR(start_pin->m_type);
                ImNodes::PushColorStyle(ImNodesCol_Link, color);
                ImNodes::PushColorStyle(ImNodesCol_LinkHovered, color);
                ImNodes::PushColorStyle(ImNodesCol_LinkSelected, color);

                ImNodes::Link(i, link.first, link.second);

                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
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

    ERROR("An error occurred and the program will now terminate.");
    std::exit(1);
}

void NodeGui::quit()
{
    this->m_done = true;
}

void NodeGui::cleanup()
{
    std::cout << "- - - - - - - - - - - - - - - - - - - -" << std::endl;
    LOG("Clean up components...");

    // Clean up components
    delete this->m_pin_manager;
    delete this->m_node_manager;

    delete this->m_file_dialog;
    delete this->m_menu_bar;

    // Clean up SDL
    SDL_DestroyRenderer(this->m_renderer);
    SDL_DestroyWindow(this->m_win);

    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImPlot::DestroyContext(this->m_implot_context);
    ImNodes::DestroyContext(this->m_imnodes_context);
    ImGui::DestroyContext(this->m_imgui_context);

    // Quit SDL system
    SDL_Quit();

    LOG("Destroy NodeGui.");
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
    this->m_imgui_context   = ImGui::CreateContext();
    this->m_imnodes_context = ImNodes::CreateContext();
    this->m_implot_context  = ImPlot::CreateContext();

    const char* glsl_version = "#version 130";

    ImGui_ImplSDL2_InitForOpenGL(this->m_win, this->m_gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Set style
    ImGui::StyleColorsDark();
    ImNodes::SetNodeGridSpacePos(1, ImVec2(200.f, 200.f));
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
}
