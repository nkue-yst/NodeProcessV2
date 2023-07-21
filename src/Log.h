/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/21
 * Edited:  2023/07/21
 **********/

#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <string>

enum class LogType
{
    LOG,
    WARNING,
    ERROR,
};

// 簡易ログ出力関数
static void log(LogType type, std::string message)
{
    std::string type_str;

    if (type == LogType::LOG)          type_str = "[LOG]: ";
    else if (type == LogType::WARNING) type_str = "[WARNING]: ";
    else if (type == LogType::ERROR)   type_str = "[ERROR]: ";

    std::cout << type_str << message << std::endl;
}

#endif
