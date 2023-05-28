/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/05
 * Edited:  2023/05/28
 **********/

#include <memory>

#include "NodeGui.h"

int main(int argc, char** argv)
{
    //////////////////////////////
    ///// Initialize systems /////
    //////////////////////////////
    if (!NodeGui::get().init())
    {
        NodeGui::get().abort();
    }
    NodeGui::get().createWindow();
    NodeGui::get().createRenderer();
    NodeGui::get().setupImGui();

    /////////////////////
    ///// Main loop /////
    /////////////////////
    NodeGui::get().loop();

    ////////////////
    ///// Quit /////
    ////////////////
    NodeGui::get().cleanup();
}
