/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/07/30
 **********/

#include "Node.h"

#include <string>

#include "imnodes.h"

#include "Logger.h"
#include "NodeGui.h"
#include "TimeProfiler.h"

Node::Node()
    : m_id(0)
    , m_name("undefined")
    , m_priority(-1)
    , m_need_update(false)
{
}

Node::~Node()
{
}

void Node::draw()
{
    // Start time profiler
    NodeGui::get().m_time_profiler->start("Draw " + this->m_name + ": " + std::to_string(this->m_id));

    //////////////////////////
    ///// Set node style /////
    //////////////////////////
    ImNodesStyle& style = ImNodes::GetStyle();
    style.Colors[ImNodesCol_TitleBar]         = IM_COL32(this->m_color.r, this->m_color.g, this->m_color.b, 255);
    style.Colors[ImNodesCol_TitleBarHovered]  = IM_COL32(this->m_color.r * 1.2, this->m_color.g * 1.2, this->m_color.b * 1.2, 255);
    style.Colors[ImNodesCol_TitleBarSelected] = IM_COL32(this->m_color.r * 1.5, this->m_color.g * 1.5, this->m_color.b * 1.5, 255);

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
    ImGui::Dummy(ImVec2(0.f, 10.f));

    /////////////////////
    ///// Draw pins /////
    /////////////////////
    this->drawInPins();
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

int Node::getPinShape(Pin::Type pin_type)
{
    ImNodesPinShape pin_shape;

    switch (pin_type)
    {
    case Pin::Type::RGB:
        pin_shape = ImNodesPinShape_CircleFilled;
        break;

    default:
        pin_shape = ImNodesPinShape_Circle;
        break;
    }

    return pin_shape;
}

void Node::drawInPins()
{
    for (auto pin : this->m_in_pins)
    {
        ImNodes::BeginInputAttribute(pin->m_id, this->getPinShape(pin->m_type));
        ImGui::TextUnformatted(pin->m_name.c_str());
        ImNodes::EndInputAttribute();
    }
}

void Node::drawOutPins()
{
    for (auto pin : this->m_out_pins)
    {
        ImNodes::BeginOutputAttribute(pin->m_id, this->getPinShape(pin->m_type));
        const float label_width = ImGui::CalcTextSize(pin->m_name.c_str()).x;
        ImGui::Indent(95.f - label_width);
        ImGui::TextUnformatted(pin->m_name.c_str());
        ImNodes::EndOutputAttribute();
    }
}
