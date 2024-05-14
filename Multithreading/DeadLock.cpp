#include<iostream>
/* thread1 is locking m1 to access the CS1, and once it is done, it is going to lock m2 to access CS2,
* But, in the same time, thread2 is locking m2, and going to wait for m1's release. Eighter of them
* is not possible. So, Deadlock will appear here.
*
* We can see, the locking order is changed here. To Avoid DeadLock WE SHOULD NOT CHANGE LOCKING ORDER.
*/

#include <mutex>
#include <thread>

std::mutex m1;
std::mutex m2;

int criticalSection1 = 0;
int criticalSection2 = 0;

void function1()
{
    m1.lock();
    std::cout << "thread1 locked the mutex m1\n";
    for (int i = 0; i < 100000; i++)
    {
        criticalSection1++;
    }
    std::cout << "thread1 is waiting for mutex m2\n";
    m2.lock();
    std::cout << "thread1 locked the mutex m2\n";
    for (int i = 0; i < 100000; i++)
    {
        criticalSection2++;
    }
    m1.unlock();
    m2.unlock();
}

void function2()
{
    m2.lock();
    std::cout << "thread2 locked the mutex m2\n";
    for (int i = 0; i < 100000; i++)
    {
        criticalSection2++;
    }
    std::cout << "thread2 is waiting for mutex m1\n";
    m1.lock();
    std::cout << "thread2 locked the mutex m1\n";
    for (int i = 0; i < 100000; i++)
    {
        criticalSection1++;
    }
    m2.unlock();
    m1.unlock();
}

/* We can use std::lock() to avoid deadlock.
* 
* std::lock() will take so many mutex arguments.
* example:
* std::lock(m1, m2, m3, m4, m5, ........)
* 
* If m1 is locked by some other thread during execution, then in the std::lock method, m1 will go at the end
* of the locking list.
* 

*/


int main()
{
    std::thread th1(function1);
    std::thread th2(function2);
    th1.join();
    th2.join();
    return 0;
}


/***********************************************************************************************
*                                             OUTPUT:
************************************************************************************************/
/*
* thread1 locked the mutex m1
* thread2 locked the mutex m2
* thread1 is waiting for mutex m2
* thread2 is waiting for mutex m1
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/