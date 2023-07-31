/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/31
 * Edited:  2023/07/31
 **********/

#pragma once

#include "GraphicsAnalyzeNode.h"

class HistogramNode : public GraphicsAnalyzeNode
{
public:
    HistogramNode();

protected:
    void drawContent() override;

private:
    int32_t m_data[256] = { 0 };
    int32_t m_max_value = 0.f;
};
