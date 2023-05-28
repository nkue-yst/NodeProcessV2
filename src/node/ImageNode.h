/**********
 * Author:  Y.Nakaue
 * Created: 2023/05/26
 * Edited:  2023/05/26
 **********/

#include "MediaNode.h"

class ImageNode : public MediaNode
{
private:
    void drawContent() override;
    bool loadData(const char* file_path) override;

    int32_t m_width  = 100;
    int32_t m_height = 100;
};
