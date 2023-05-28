/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/05/26
 **********/

#include "ImageNode.h"

#include <opencv2/opencv.hpp>

#include "Image.h"

void ImageNode::drawContent()
{

}

bool ImageNode::loadData(const char* file_path)
{
    // When `file_path` is null, generate and set empty image
    if (!file_path)
    {
        static_cast<Image*>(this->m_content)->m_data = cv::Mat::zeros(100, 100, CV_8UC3);
        return true;
    }

    // Load image data
    static_cast<Image*>(this->m_content)->m_data = cv::imread(file_path);

    // Set drawing size
    float resize_rate = 100.f / std::max(this->m_width, this->m_height);
    this->m_width *= resize_rate;
    this->m_height *= resize_rate;

    return true;
}
