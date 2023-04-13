/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/04/09
 **********/

#include "Node.h"

#include "imnodes.h"

#include "Pin.h"

Node::Node()
    : m_id(0)
    , m_name("none")
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

    /////////////////////
    ///// Draw pins /////
    /////////////////////
    this->drawInPins();
    this->drawOutPins();

    /////////////////////////////
    ///// Draw node content /////
    /////////////////////////////
    this->drawContent();

    ImNodes::EndNode();
}

void Node::drawInPins()
{
    for (auto pin : this->m_in_pins)
    {
        ImNodes::BeginInputAttribute(pin->m_id);
        ImGui::TextUnformatted(pin->m_name);
        ImNodes::EndInputAttribute();
    }
}

void Node::drawOutPins()
{
    for (auto pin : this->m_out_pins)
    {
        ImNodes::BeginOutputAttribute(pin->m_id);
        ImGui::TextUnformatted(pin->m_name);
        ImNodes::EndOutputAttribute();
    }
}
