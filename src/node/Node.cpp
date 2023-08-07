/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/08/06
 **********/

#include "Node.h"

#include <algorithm>
#include <string>

#include "imnodes.h"

#include "Logger.h"
#include "NodeGui.h"
#include "TimeProfiler.h"

Node::Node(NodeType type)
    : m_id(0)
    , m_name("undefined")
    , m_priority(-1)
    , m_need_update(false)
    , m_type(type)
{
    this->m_content = new NodeContent();
}

Node::~Node()
{
    delete this->m_content;
}

void Node::draw()
{
    // Start time profiler
    NodeGui::get().m_time_profiler->start("Draw " + this->m_name + ": " + std::to_string(this->m_id));

    //////////////////////////
    ///// Set node style /////
    //////////////////////////
    ImNodesStyle& style = ImNodes::GetStyle();
    uint32_t base_color = NODE_COLOR(this->m_type);
    style.Colors[ImNodesCol_TitleBar]         = base_color;
    style.Colors[ImNodesCol_TitleBarHovered]  = multiplyIM_COL(base_color, 1.1);
    style.Colors[ImNodesCol_TitleBarSelected] = multiplyIM_COL(base_color, 1.2);

    base_color = IM_COL32(94, 95, 90, 200);
    style.Colors[ImNodesCol_NodeBackground]         = base_color;;
    style.Colors[ImNodesCol_NodeBackgroundHovered]  = multiplyIM_COL(base_color, 1.1);
    style.Colors[ImNodesCol_NodeBackgroundSelected] = multiplyIM_COL(base_color, 1.2);

    ImNodes::BeginNode(this->m_id);

    ///////////////////////////
    ///// Draw node title /////
    ///////////////////////////
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(this->m_name.c_str());
    ImNodes::EndNodeTitleBar();
    
    /////////////////////////////
    ///// Draw node content /////
    /////////////////////////////
    this->drawContent();

    /////////////////////////////////
    ///// Draw pins and options /////
    /////////////////////////////////
    this->drawInPins();
    ImGui::Spacing();
    this->drawOutPins();
    ImGui::Spacing();

    // Stop time profiler
    ImGui::Text(
        "%.2fms",
        NodeGui::get().m_time_profiler->stop("Draw " + this->m_name + ": " + std::to_string(this->m_id)) / 1000.f
    );

    ImNodes::EndNode();
}

void Node::setDirtyFlag(int32_t new_priority)
{
    //DEBUG("Set update flag. (node id: " + std::to_string(this->m_id) + ", node name: " + this->m_name + ")");

    this->m_need_update = true;

    if (this->m_priority < new_priority || new_priority == -1)
    {
        this->m_priority = new_priority;
    }

    for (Pin* out_pin : m_out_pins)
    {
        for (Pin* connected_pin : out_pin->m_connected_pins)
        {
            connected_pin->m_owner->setDirtyFlag(this->m_priority + 1);
        }
    }
}

void Node::drawInPins()
{
    for (auto pin : this->m_in_pins)
    {
        pin->drawAsInput();
    }
}

void Node::drawOutPins()
{
    for (auto pin : this->m_out_pins)
    {
        pin->drawAsOutput();
    }
}
