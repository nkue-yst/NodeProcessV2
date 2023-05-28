/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/05/26
 **********/

#include <opencv2/opencv.hpp>

#include "Media.h"

class Image : public Media
{
public:
    void draw() override;

    // Image data for processing
    cv::Mat m_data;
};
