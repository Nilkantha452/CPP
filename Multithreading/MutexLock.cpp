/* This file will explain the working of threads.
* Threads will reduce the system time required to finish a job with multiple processes.
*/

#include <iostream>
#include <thread>
#include <mutex>

int criticalSection = 0;
std::mutex mtx;
void AccessCriticalSec()
{
    for (int i = 0; i < 1000000; i++)
    {
        mtx.lock();
        /* Here we can use Mutex to avoid race conditions. mutex is a c++ class which has rich methods.
        * lock() is one of them. Before accessing the critical section we can use mutex lock() to prevent
        * other thread to access it.
        */
        criticalSection++;
        /* After accessing the critical section, we need to unlock the mutex using unlock,
        * otherwise program will not continue.
        */
        mtx.unlock();
    }
}

int main()
{
    std::thread th1(AccessCriticalSec); // This is a way to create a thread.

    /* If a method is void Function(param1, param2, param3), then if we want to create a thread of function
    * "Function", then it will be like:
    * std::thread th(Function, param1, param2, param3);
    *
    * Now if a method Fun(param1, param2) is defined in class fffd.
    * And an object is created of class fffd as x. i.e. fffd x;
    * Then thread creation will be:
    * std::thread th(&fffd::Fun, &x, param1, param2);
    */
    std::thread th2(AccessCriticalSec);
    if (th1.joinable())
    {
        th1.join();
    }
    /* If we use join method, then the parent threads i.e. main, will wait for the child thread
    * to be finished first.
    * If we donot want that, we can use th.detach(). In this case, the main thread will exit when it is done
    * with its job. It will not for the child threads. Which will give incomplete results.
    */
    if (th2.joinable())
    {
        th2.join();
    }
    std::cout << criticalSection;
    return 0;
}


/***********************************************************************************************
*                                             OUTPUT:
************************************************************************************************/
/*
* The output will be defined in this case. Since we've used mutex to guard the critical section,
* The output will be 2000000 always.
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/