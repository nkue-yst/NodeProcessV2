/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/22
 * Edited:  2023/07/28
 **********/

#include "FileDialog.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include "GL/gl.h"
#include "ImGuiFileDialog.h"

#include "ImageNode.h"
#include "Logger.h"
#include "NodeGui.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

FileDialog::FileDialog()
{
    LOG("Initialize FileDialog Manager.");

    ///////////////////////////////////////////
    ///// Initialize file dialog settings /////
    ///////////////////////////////////////////
    ImGuiFileDialog::Instance()->SetCreateThumbnailCallback([](IGFD_Thumbnail_Info *vThumbnail_Info) -> void
    {
        if (vThumbnail_Info && 
            vThumbnail_Info->isReadyToUpload && 
            vThumbnail_Info->textureFileDatas)
        {
            GLuint textureId = 0;
            glGenTextures(1, &textureId);
            vThumbnail_Info->textureID = (void*)(intptr_t)textureId;

            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                (GLsizei)vThumbnail_Info->textureWidth, (GLsizei)vThumbnail_Info->textureHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, vThumbnail_Info->textureFileDatas);
            glFinish();
            glBindTexture(GL_TEXTURE_2D, 0);

            delete[] vThumbnail_Info->textureFileDatas;
            vThumbnail_Info->textureFileDatas = nullptr;

            vThumbnail_Info->isReadyToUpload = false;
            vThumbnail_Info->isReadyToDisplay = true;
        }
    });

    ImGuiFileDialog::Instance()->SetDestroyThumbnailCallback([](IGFD_Thumbnail_Info* vThumbnail_Info)
    {
        if (vThumbnail_Info)
        {
            GLuint texID = (GLuint)(intptr_t)vThumbnail_Info->textureID;
            glDeleteTextures(1, &texID);
            glFinish();
        }
    });
}

FileDialog::~FileDialog()
{
    LOG("Destroy FileDialog Manager.");
}

void FileDialog::draw()
{
    ///////////////////////////
    ///// Dialog settings /////
    ///////////////////////////
    ImGuiFileDialog::Instance()->ManageGPUThumbnails();

    ImVec2 dialog_max_size = ImVec2((float)NodeGui::get().m_win_width, (float)NodeGui::get().m_win_height);
    ImVec2 dialog_min_size = ImVec2((float)NodeGui::get().m_win_width * 0.5f, (float)NodeGui::get().m_win_height * 0.5f);

    ////////////////////////////////////////////
    ///// Draw dialog to select image file /////
    ////////////////////////////////////////////
    if (ImGuiFileDialog::Instance()->Display("SelectImageDlgkey", ImGuiWindowFlags_NoCollapse, dialog_min_size, dialog_max_size))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string file_path = ImGuiFileDialog::Instance()->GetFilePathName();

            Node* new_node = new ImageNode(file_path);
            NodeGui::get().m_node_manager->addNode(new_node);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}
