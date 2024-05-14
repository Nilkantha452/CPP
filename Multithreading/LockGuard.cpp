#include <iostream>
#include <thread>
#include <mutex>

int critical_section = 0;

std::mutex m;

void criticalSectionAccess()
{
    /* std::lock_guard is a wrapper class for mutex. In mutex, we explicitly call unlock() method when
    * critical section calling is over, when we create an object of lock_guard, at the end of the method
    * the mutex will be unlocked automatically. We donot need to call the unlock() method seperately.
    */
    std::lock_guard<std::mutex> lock(m);
    for (int i = 0; i < 1000000; i++)
    {
        critical_section++;
    }
}

int main()
{
    std::thread th1(criticalSectionAccess);
    std::thread th2(criticalSectionAccess);
    th1.join();
    th2.join();
    std::cout << critical_section;
    return 0;
}

/***********************************************************************************************
*                                             OUTPUT:
************************************************************************************************/
/*
* The output will be defined, because lock_guard works just like mutex lock and unlock.
* The output will be 2000000.
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/