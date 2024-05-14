/* Promise and Future are like something is getting returned from a thread. */

#include <iostream>
#include <future>
#include <chrono>

void function(std::promise<int>&& ans)
{
    /* This can be used to sleep the thread for sometimes */
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ans.set_value(10);
}

int main()
{
    /* We've declared a promise of int type, when the thread used ans.set_value, through the
    * future created by the promise in the next line we can get the value, using get() method.
    *
    * Order:
    * Create promise
    * Create future from the promise
    * generate the thread.
    * Use set_value() method on the promise to write.
    * Use get() method to get the value.
    */
    std::promise<int> ans;
    std::future<int> fut = ans.get_future();
    std::thread th(function, std::move(ans));
    std::cout << fut.get();
    th.join();
    return 0;
}


/***********************************************************************************************
*                                             OUTPUT:
************************************************************************************************/
/*
* 10
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/
