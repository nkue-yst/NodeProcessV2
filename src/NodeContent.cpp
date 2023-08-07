/**********
 * Author:  Y.Nakaue
 * Created: 2023/08/07
 * Edited:  2023/08/07
 **********/

#include "NodeContent.h"

NodeContent::NodeContent()
    : m_value(0)
{
    DEBUG("Initialize node content.");

    this->m_image = cv::Mat();
}

NodeContent::~NodeContent()
{
    this->m_image.release();

    DEBUG("Release node content.");
}
