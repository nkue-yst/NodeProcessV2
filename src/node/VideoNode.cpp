/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/04
 * Edited:  2023/08/07
 **********/

 #include "VideoNode.h"

 #include "Logger.h"

VideoNode::VideoNode(std::string file_path)
    : m_playing(true)
{
    ///////////////////////////
    ///// Initialize Node /////
    ///////////////////////////
    this->m_name = "Video Source";
    this->m_type = NodeType_VideoSource;

    ///////////////////////////
    ///// Initialize Pins /////
    ///////////////////////////
    Pin* new_pin = nullptr;

    // Output pins
    new_pin = NodeGui::get().m_pin_manager->newPin(this, Pin::Type::RGB, "RGB");
    this->m_out_pins.push_back(new_pin);

    ///////////////////////////
    ///// Load image data /////
    ///////////////////////////
    if (!this->loadData(file_path))
    {
        WARNING("Failed to load: \"" + file_path + "\"");
    }
}

void VideoNode::drawContent()
{
    // Update frame image
    if (this->m_playing)
    {
        this->m_video.read(this->m_content->m_image);
        if (this->m_content->m_image.empty())
        {
            this->m_video.set(cv::CAP_PROP_POS_FRAMES, 0);
            this->m_video.read(this->m_content->m_image);
        }

        glDeleteTextures(1, &this->m_gl_texture);
        this->m_gl_texture = convert_func(&this->m_content->m_image);

        this->setDirtyFlag();
    }

    ImGui::Image((void*)(uintptr_t)this->m_gl_texture, ImVec2(this->m_width, this->m_height));

    // Playing button
    if (this->m_playing)
    {
        if (ImGui::Button(" Stop "))
        {
            this->m_playing = false;
        }
    }
    else
    {
        if (ImGui::Button(" Play "))
        {
            this->m_playing = true;
        }
    }
}

bool VideoNode::loadData(std::string file_path)
{
    // When `file_path` is null, generate and set empty image
    if (file_path.empty())
    {
        this->m_content->m_image = cv::Mat::zeros(100, 100, CV_8UC3);
        return true;
    }

    // Load video data
    this->m_video.open(file_path);
    if (!this->m_video.isOpened())
    {
        return false;
    }

    // Set drawing size
    float resize_rate = 100.f / std::max(this->m_width, this->m_height);
    this->m_width *= resize_rate;
    this->m_height *= resize_rate;

    this->m_need_update = true;

    return true;
}
