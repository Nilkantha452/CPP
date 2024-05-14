#include <iostream>
#include <thread>
#include <mutex>

int critical_section = 0;

std::mutex m;

void criticalSectionAccess()
{
    /* std::unique_lock is a wrapper class for mutex just like lock_guard. In mutex, we explicitly
    * call unlock() method when calling of critical section is over, when we create an object
    * of unique_lock, at the end of the method the mutex will be unlocked automatically.
    * We donot need to call the unlock() method seperately.
    * Apart from this std::unique_lock has much more extra functionalities.
    *       1. Locking Stratergies ---> a. std::defer_lock,  b. std::try_to_lock  c. adapt_lock
    * When defer_lock is used we need to call ul.lock() seperately. But unlock() is not needed in anyof them.
    *       2. condition_variable
    */
    std::unique_lock<std::mutex> ul(m, std::defer_lock); 
    // Since I've used defer_lock, I've called lock() method.
    ul.lock();
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