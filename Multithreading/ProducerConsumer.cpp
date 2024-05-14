#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::vector<int> buffer;
int maxBufferSize = 50;

void Producer(int x)
{
    while (x)
    {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, [] {
            return buffer.size() < maxBufferSize ? true : false;
            });
        buffer.push_back(x);
        std::cout << "Produced " << x << std::endl;
        x--;
        ul.unlock();
        cv.notify_one();
    }
}
void Consumer()
{
    while (1)
    {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, [] {
            return buffer.size() > 0 ? true : false;
            });
        int value = buffer.back();
        buffer.pop_back();
        std::cout << "Consumed " << value << std::endl;
        ul.unlock();
        cv.notify_one();
    }
}

int main()
{
    std::thread th1(Producer, 51);
    std::thread th2(Consumer);
    th1.join();
    th2.join();
    return 0;
}


/***********************************************************************************************
*                                             OUTPUT:
************************************************************************************************/
/*
* At first producer should create something, then consuiming and producing should start parallally
* Once All the consumption is done, the program should stuck, as Consumer is ready to consume for
* iternity, while producer has only 51 items to be produced.
*/
/*
* By: Nilkantha Bhattacharjee (www.linkedin.com/in/nilkanthab)
*/