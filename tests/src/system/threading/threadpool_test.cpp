/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
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

#include "gtest.h"
#include "system/threading/threadpool.h"

TEST(ThreadPoolTest, CanBeCreated)
{
    const int NumThreads = 4;
    ASSERT_NO_THROW(ThreadPool pool(NumThreads));
}

TEST(ThreadPoolTest, HasDefaultValues)
{
    const int NumThreads = 4;
    ThreadPool pool(NumThreads);

    ASSERT_FALSE(pool.HasTasksLeft());
    ASSERT_FALSE(pool.ShouldStop());
}

TEST(ThreadPoolTest, CanScheduleTasks)
{
    const int NumThreads = 4;

    {
        ThreadPool pool(NumThreads);
        for (int i = 0; i < 3; ++i) {
            pool.ScheduleTask(0, []() {});
        }
    }

    {
        ThreadPool pool(NumThreads);
        for (int i = 0; i < 4; ++i) {
            pool.ScheduleTask(0, []() {});
        }
    }

    {
        ThreadPool pool(NumThreads);
        for (int i = 0; i < 5; ++i) {
            pool.ScheduleTask(0, []() {});
        }
    }
}

TEST(ThreadPoolTest, WillJoinThreadsOnDestroy)
{
    const int NumThreads = 4;
    std::atomic_int numInvokes = 0;

    {
        ThreadPool pool(NumThreads);
        for (int i = 0; i < 100; ++i) {
            pool.ScheduleTask(0, [&]() { numInvokes++; });
        }
    }

    EXPECT_EQ(numInvokes, 100);
}

TEST(ThreadPoolTest, ThreadTasksAreUnique)
{
    const int NumThreads = 1;

    std::mutex mutex;
    int numInvokes = 0;

    {
        ThreadPool pool(NumThreads);

        for (int i = 0; i < 20; ++i)
        {
            auto func = [i, &numInvokes, &mutex]()
            {
                std::lock_guard<std::mutex> lock(mutex);
                numInvokes += i;
            };

            pool.ScheduleTask(i, func);
        }

    }

    EXPECT_EQ(numInvokes, 190);
}

TEST(ThreadPoolTest, TaskCanAcceptArgs)
{
    const int NumThreads = 1;
    int* myInt = new int();
    *myInt = -1;

    {
        ThreadPool pool(NumThreads);
        pool.ScheduleTask(0, [](int* myInt) { *myInt = 99; }, myInt);
    }

    EXPECT_EQ(*myInt, 99);
}

TEST(ThreadPoolTest, TaskCanHavePriority)
{
    const int NumThreads = 1;

    std::queue<int> order;
    std::mutex mutex;
    mutex.lock();

    {
        ThreadPool pool(NumThreads);

        // Lockup first thread to give time to adding other tasks
        pool.ScheduleTask(99999, [&]()
        {
            mutex.lock();
            mutex.unlock();
        });

        for (int i = 0; i < 20; ++i)
            pool.ScheduleTask(i, [&order](int i) { order.emplace(i); }, i);

        // Allow first thread to exit making space for the subsequent 100 prioritized tasks
        mutex.unlock();
    }

    for (int i = 19; i > 0; --i)
    {
        EXPECT_EQ(order.front(), i);
        order.pop();
    }
}

