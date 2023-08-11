/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/11
 * Edited:  2023/08/11
 **********/

#include "ColorBlendNode.h"

ColorBlendNode::ColorBlendNode()
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Color Blend";
    this->m_type = NodeType_Utility;

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Input pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::Red, "Red");
    this->m_in_pins.push_back(new_pin);

    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::Green, "Green");
    this->m_in_pins.push_back(new_pin);

    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::Blue, "Blue");
    this->m_in_pins.push_back(new_pin);

    // Output pin
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);

    /****************************************************************************
     *** Since it is known that there is a bug in the image display process,  ***
     *** a warning statement should be output at the time of node generation. ***
     ****************************************************************************/
    WARNING(this->m_name + " Node: This node has a bug in the image display process.");
}

void ColorBlendNode::drawContent()
{
    if (this->m_need_update)
    {
        ///////////////////////////////
        ///// Input from RGB pins /////
        ///////////////////////////////
        auto pin_iter = this->m_in_pins.begin();
        Pin* pin, *pair_pin;

        cv::Mat mat_rgb[3];
        for (auto& mat : mat_rgb)
        {
            pin = *(pin_iter++);
            pair_pin = NodeGui::get().m_pin_manager->getPair(pin->m_id);

            if (pair_pin)
            {
                Node* node = pair_pin->m_owner;
                mat = node->getContent<cv::Mat>(pair_pin->m_type);
            }
            else
            {
                mat = cv::Mat::zeros(this->m_initial_node_width, this->m_initial_node_width, CV_8UC3);
            }
        }

        ////////////////////////////////////////////////////////
        ///// Blend red image, green image and blue image. /////
        ////////////////////////////////////////////////////////
        int32_t max_width  = std::max({ mat_rgb[0].cols, mat_rgb[1].cols, mat_rgb[2].cols });
        int32_t max_height = std::max({ mat_rgb[0].rows, mat_rgb[1].rows, mat_rgb[2].rows });

        for (auto& mat : mat_rgb)
        {
            int32_t width_blank  = max_width - mat.cols;
            int32_t height_blank = max_height - mat.rows;

            cv::copyMakeBorder(mat, mat, height_blank / 2, height_blank / 2, width_blank / 2, width_blank / 2, cv::BORDER_CONSTANT);
        }

        this->m_content->m_image.release();
        this->m_content->m_image = cv::Mat::zeros(max_height, max_width, CV_8UC3);

        for (int32_t y = 0; y < max_height; ++y)
        {
            for (int32_t x = 0; x < max_width; ++x)
            {
                uchar r = (mat_rgb[0]).at<cv::Vec3b>(y, x)[2];
                uchar g = (mat_rgb[1]).at<cv::Vec3b>(y, x)[1];
                uchar b = (mat_rgb[2]).at<cv::Vec3b>(y, x)[0];

                cv::Vec3b* data = this->m_content->m_image.ptr<cv::Vec3b>(y);
                data[x] = cv::Vec3b(b, g, r);
            }
        }

        for (auto& mat : mat_rgb)
        {
            mat.release();
        }

        this->resizeFrame();

        cv::Mat mat = this->m_content->m_image.clone();

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = this->convert_func(&mat);

        this->m_need_update = false;
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));
}
