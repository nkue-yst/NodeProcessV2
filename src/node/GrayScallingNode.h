/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __GRAY_SCALLING_H__
#define __GRAY_SCALLING_H__

#include "ProcessingNode.h"

class GrayScallingNode : public ProcessingNode
{
public:
    GrayScallingNode();

protected:
    void drawContent() override;
    void process() override;
};

#endif
