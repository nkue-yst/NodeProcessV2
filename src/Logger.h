/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/29
 **********/

#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "NodeGui.h"

enum class LogType
{
    DEBUG,
    LOG,
    WARNING,
    ERROR,
};

// ログ出力用クラス
class Logger
{
public:
    Logger()
    {
        this->ofs.open("NodeProcessingV2.log");

        if (!this->ofs)
        {
            this->log(LogType::ERROR, "Failed to open log file.");
        }

        this->log(LogType::LOG, "Initialize Logger.");
    }

    ~Logger()
    {
        this->log(LogType::LOG, "Destroy Logger.");

        this->ofs.close();
    }

    // 簡易ログ出力関数
    void log(LogType type, std::string message)
    {
        std::string type_str;

        if      (type == LogType::DEBUG)   type_str = "[DEBUG]: ";
        else if (type == LogType::LOG)     type_str = "[LOG]: ";
        else if (type == LogType::WARNING) type_str = "[WARNING]: ";
        else if (type == LogType::ERROR)   type_str = "[ERROR]: ";

        auto now_clock = std::chrono::system_clock::now();
        auto now_time  = std::chrono::system_clock::to_time_t(now_clock);
        std::string now_str = std::ctime(&now_time);
        now_str.pop_back();

        this->ofs << now_str << ": " << type_str << message << std::endl;

        if (type != LogType::DEBUG)
        {
            std::cout << type_str << message << std::endl;
        }
    }

private:
    std::ofstream ofs;
};

#define DEBUG(message)   NodeGui::get().m_logger->log(LogType::DEBUG, message)
#define LOG(message)     NodeGui::get().m_logger->log(LogType::LOG, message)
#define WARNING(message) NodeGui::get().m_logger->log(LogType::WARNING, message)
#define ERROR(message)   NodeGui::get().m_logger->log(LogType::ERROR, message)
