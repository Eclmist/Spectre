/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <condition_variable>
#include <mutex>
#include <future>
#include <queue>

struct ThreadTask
{
    template <typename Func, typename... Args>
    ThreadTask(double priority, Func&& func, Args&&... args)
    {
        m_Task = [=]() { func(std::forward<Args>(args)...); };
        m_Priority = priority;
    };

    inline bool operator<(const ThreadTask& t) const { return t.m_Priority < m_Priority; }

    std::function<void()> m_Task;
    double m_Priority;
};

class ThreadPool
{
public:
    ThreadPool(int numThreads)
        : m_Stop(false)
    {
        for (int i = 0; i < numThreads; ++i)
        {
            m_Threads.emplace_back([this, i]
            {
                while (true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->m_QueueMutex);
                        this->m_Condition.wait(lock, [this] { return this->m_Stop || !this->m_Tasks.empty(); });

                        if (this->m_Stop && this->m_Tasks.empty())
                            break;

                        task = std::move(this->m_Tasks.top().m_Task);
                        this->m_Tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_Stop = true;
        }

        m_Condition.notify_all();

        for (std::thread& thread : m_Threads)
            thread.join();
    };

    template <typename Task, typename... Args>
    void ScheduleTask(double priority, Task&& task, Args&&... args)
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);

        if (m_Stop)
            throw std::runtime_error("Task enqueued on a stopped ThreadPool!");

        m_Tasks.emplace(priority, std::forward<Task>(task), std::forward<Args>(args)...);
        m_Condition.notify_one();
    };

private:
    std::priority_queue<ThreadTask> m_Tasks;
    std::mutex m_QueueMutex;
    std::condition_variable m_Condition;
    std::vector<std::thread> m_Threads;
    bool m_Stop;
};

