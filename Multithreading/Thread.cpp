/* This file will explain the working of threads.
* Threads will reduce the system time required to finish a job with multiple processes.
*/

#include <iostream>
#include <thread>

int criticalSection = 0;

void AccessCriticalSec()
{
    for (int i = 0; i < 1000000; i++)
    {
        criticalSection++;
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
        /* We can not join the same thread twice. It will stuck the program, hence we can use joinable
        * method of thread.
        */
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
* The output will be undefined. As Context switch will occur. And Race condition will hit.
* Therefore, the output will be sometimes 20000000, sometimes 1772211, sometimes 1992112 etc.
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/