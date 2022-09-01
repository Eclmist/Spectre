/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
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
#include <future>
#include <queue>

class ThreadPool
{
public:
    ThreadPool(int numThreads);
    ~ThreadPool();

    template <typename Task, typename... Args>
    void ScheduleTask(double priority, Task&& task, Args&&... args);

public:
    inline bool HasTasksLeft() const { return !m_Tasks.empty(); }
    inline bool ShouldStop() const { return m_Stop; }

private:
    void ThreadMain(ThreadPool& pool);
    std::function<void()> PopNextTask();

private:
    struct ThreadTask
    {
        ThreadTask(double priority, std::function<void()> task)
            : m_Task(task)
            , m_Priority(priority) {}

        inline bool operator<(const ThreadTask& t) const { return t.m_Priority > m_Priority; }

        std::function<void()> m_Task;
        double m_Priority;
    };

private:
    std::mutex m_Mutex;

    std::priority_queue<ThreadTask> m_Tasks;
    std::condition_variable m_Condition;
    std::vector<std::thread> m_Threads;
    std::atomic_bool m_Stop;
};

template <typename Task, typename... Args>
void ThreadPool::ScheduleTask(double priority, Task&& task, Args&&... args)
{
    std::unique_lock<std::mutex> lock(m_Mutex);

    if (m_Stop)
        throw std::runtime_error("Task enqueued on a stopped ThreadPool!");

    auto taskFunc = [=]() { task(args...); };
    m_Tasks.emplace(priority, taskFunc);
    m_Condition.notify_one();
}

