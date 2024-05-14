#include <iostream>
#include <mutex>
#include <condition_variable>

int bank_balance = 0;
std::condition_variable cv;
std::mutex m;

void deposit(int money)
{
    /* unique_lock is not required here, we can use lock_guard or normal mutex. */
    std::unique_lock<std::mutex> ul(m);
    bank_balance = bank_balance + money;
    std::cout << "Deposit Done\n";

    /* This is notifying one thread. cv.notify_all() is the method to notify all other thread*/
    cv.notify_one();
}

void withdraw(int money)
{
    std::unique_lock<std::mutex> ul(m);
    /* This is the lambda function without passing the money variable.
    * cv.wait(ul, [] {return (bank_balance > 0) ? true : false; });
    * If this lambda function returns true, that means program will proceed.
    */
    cv.wait(ul, [money] {return (bank_balance >= money) ? true : false; });
    bank_balance = bank_balance - money;
    std::cout << "Withdraw Done\n";
}

int main()
{
    std::thread th1(deposit, 400);
    std::thread th2(withdraw, 300);
    /* Deposit will always happen before withdraw. 
    * if (deposit 100), (withdraw 200) is there, the program will hang after 'deposit' print.
    * if (deposit 100), (withdraw 200), (deposit 100) is there, it will print 'd, d, w' print.
    */
    th1.join();
    th2.join();
    return 0;
}


/***********************************************************************************************
*                                             OUTPUT:
************************************************************************************************/
/*
* The output will Deposit, withdraw.
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/