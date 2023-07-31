/**********
 * Author:  Y.Nakaue
 * Created: 2023/07/31
 * Edited:  2023/07/31
 **********/

#pragma once

#include <chrono>
#include <string>
#include <unordered_map>

#include "Logger.h"

class TimeProfiler
{
private:
    struct Task
    {
    public:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
        double pre_elapsed_time;
    };

public:
    TimeProfiler()
    {
    }

    ~TimeProfiler()
    {
        for (auto iter = this->m_task.begin(); iter != this->m_task.end(); ++iter)
        {
            delete (*iter).second;
        }
    }

    void start(const std::string& task_id)
    {
        bool is_exist = false;
        for (auto iter = this->m_task.begin(); iter != this->m_task.end(); ++iter)
        {
            if ((*iter).first == task_id)
            {
                is_exist = true;
                break;
            }
        }

        if (!is_exist)
        {
            this->m_task[task_id] = new Task();
        }

        Task* task = this->m_task.at(task_id);
        task->m_start_time = std::chrono::high_resolution_clock::now();
    }

    double stop(const std::string& task_id)
    {
        Task* task = this->m_task.at(task_id);
        
        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end_time - task->m_start_time).count();

        // Weighted average
        task->pre_elapsed_time = (task->pre_elapsed_time + elapsed) / 2;

        // Low-pass filter
        const double smoothing_factor = 0.1f;
        elapsed = (smoothing_factor * elapsed) + ((1.f - smoothing_factor) * task->pre_elapsed_time);

        return task->pre_elapsed_time;    // microseconds
    }

private:
    std::unordered_map<std::string, Task*> m_task;
};
