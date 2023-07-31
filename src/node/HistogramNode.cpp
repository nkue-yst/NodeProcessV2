/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/31
 * Edited:  2023/07/31
 **********/

#include "HistogramNode.h"

#include <algorithm>

#include "implot.h"

#include "GraphicsNode.h"
#include "NodeGui.h"

#define HIST_WIDTH  250
#define HIST_HEIGHT 150

HistogramNode::HistogramNode()
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Histgram";

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Input pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "Input");
    this->m_in_pins.push_back(new_pin);
}

void HistogramNode::drawContent()
{
    if (this->m_need_update)
    {
        cv::Mat input_image;
        Pin* pair_pin = NodeGui::get().m_pin_manager->getPair(this->m_in_pins.at(0)->m_id);

        if (pair_pin)
        {
            GraphicsNode* connected_node = dynamic_cast<GraphicsNode*>(pair_pin->m_owner);

            if (connected_node)
            {
                input_image = connected_node->getContent(Pin::Type::RGB);
            }
        }
        else
        {
            input_image = cv::Mat::zeros(100, 100, CV_8UC3);
        }

        ////////////////////////////////
        ///// Create histgram data /////
        ////////////////////////////////
        cv::cvtColor(input_image, input_image, cv::COLOR_BGR2GRAY);
        cv::resize(input_image, input_image, cv::Size(100, 100));

        int32_t size = sizeof(this->m_data) / sizeof(this->m_data[0]);
        for (int i = 0; i < size; ++i)
        {
            this->m_data[i] = 0;
        }
        
        for (int y = 0; y < input_image.size().height; ++y)
        {
            for (int x = 0; x < input_image.size().width; ++x)
            {
                uint32_t value = static_cast<uint32_t>(input_image.at<uint8_t>(y, x));
                this->m_data[value]++;
            }
        }

        this->m_need_update = false;
    }

    ////////////////////////////////////
    ///// Create and draw histgram /////
    ////////////////////////////////////
    if (ImPlot::BeginPlot("##Histgram", ImVec2(HIST_WIDTH, HIST_HEIGHT), ImPlotFlags_NoInputs | ImPlotFlags_NoChild))
    {
        this->m_max_value = *std::max_element(std::begin(this->m_data), std::end(this->m_data));
        
        ImPlot::SetNextFillStyle(ImVec4(0.7f, 0.7f, 0.7f, 1.f));
        ImPlot::SetupAxes(0, 0, ImPlotAxisFlags_None, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0.f, this->m_max_value, ImPlotCond_Always);
        
        ImPlot::PlotBars("", this->m_data, sizeof(this->m_data) / sizeof(this->m_data[0]));

        ImPlot::EndPlot();
    }
}
