/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/07
 * Edited:  2023/08/07
 **********/
 
#pragma once

#include "opencv2/opencv.hpp"

#include "Logger.h"

///////////////////////////////////////////////
///// Structure that stores               /////
///// the contents contained in each node /////
///////////////////////////////////////////////
struct NodeContent
{
public:
    NodeContent();
    ~NodeContent();

    cv::Mat m_image;
    int32_t m_value;
};
