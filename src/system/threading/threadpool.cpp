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

#include "threadpool.h"

ThreadPool::ThreadPool(int numThreads)
    : m_Stop(false)
{
    for (int i = 0; i < numThreads; ++i)
    {
        m_Threads.emplace_back([this] { ThreadMain(*this); });
    }
}

ThreadPool::~ThreadPool()
{
    m_Stop = true;
    m_Condition.notify_all();

    for (std::thread& thread : m_Threads)
        thread.join();
}

void ThreadPool::ThreadMain(ThreadPool& pool)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Condition.wait(lock, [&pool] { return pool.m_Stop || !pool.m_Tasks.empty(); });

        if (ShouldStop() && !HasTasksLeft())
            return;

        auto nextTask = pool.PopNextTask();
        lock.unlock();

        nextTask();
    }
}

std::function<void()> ThreadPool::PopNextTask()
{
    auto nextTask = m_Tasks.top().m_Task;
    m_Tasks.pop();
    return nextTask;
}
