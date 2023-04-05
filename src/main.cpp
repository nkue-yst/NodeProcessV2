/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/04/05
 **********/

#include <memory>

#include "NodeGui.h"

int main(int argc, char** argv)
{
    std::unique_ptr<NodeGui> node_gui(new NodeGui);

    //////////////////////////////
    ///// Initialize systems /////
    //////////////////////////////
    if (!node_gui->init())
    {
        node_gui->abort();
    }
    node_gui->createWindow();
    node_gui->createRenderer();
    node_gui->setupImGui();

    node_gui->loop();

    node_gui->quit();
}
