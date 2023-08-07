/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/07
 * Edited:  2023/08/07
 **********/

#include "Constant.h"

#include "NodeGui.h"

ConstantInt::ConstantInt()
    : Node(NodeType_Constant)
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "ConstValue";

    // Output pin
    this->m_out_pins.push_back(NodeGui::get().m_pin_manager->newPin(this, Pin::Type::VALUE, "IntVal"));
}

void ConstantInt::drawContent()
{
    ImGui::PushID(this->m_id);
    ImGui::PushItemWidth(this->m_node_width);

    if (ImGui::DragInt("", &this->m_content->m_value, 1.f, INT32_MIN, INT32_MAX))
    {
        this->setDirtyFlag();
    }

    ImGui::PopItemWidth();
    ImGui::PopID();
}
