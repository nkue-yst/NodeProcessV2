/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/07/21
 **********/

#include "Node.h"

#include "imnodes.h"

#include "Pin.h"

Node::Node()
    : m_id(0)
    , m_name("undefined")
    , m_need_update(true)
{
}

Node::~Node()
{
}

void Node::draw()
{
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

    ImNodes::EndNode();
}

void Node::drawInPins()
{
    for (auto pin : this->m_in_pins)
    {
        ImNodes::BeginInputAttribute(pin->m_id);
        ImGui::TextUnformatted(pin->m_name.c_str());
        ImNodes::EndInputAttribute();
    }
}

void Node::drawOutPins()
{
    for (auto pin : this->m_out_pins)
    {
        ImNodes::BeginOutputAttribute(pin->m_id);
        const float label_width = ImGui::CalcTextSize(pin->m_name.c_str()).x;
        ImGui::Indent(95.f - label_width);
        ImGui::TextUnformatted(pin->m_name.c_str());
        ImNodes::EndOutputAttribute();
    }
}
