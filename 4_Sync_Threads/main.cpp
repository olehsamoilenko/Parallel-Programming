#include <thread>
#include <iostream>
#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>

int main()
{
    std::mutex m;
    std::condition_variable cv;
    bool printHello = true;

    std::promise<bool> exitSignal;
    std::future<bool> futureObj = exitSignal.get_future();

    std::thread threadHello([&]{
        while (futureObj.wait_for(std::chrono::milliseconds(500)) 
                   != std::future_status::ready) {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [&]{return printHello;});

            std::cout << "Hello " << std::flush;

            printHello = false;
            cv.notify_one();
        }
    });

    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();
    do {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [&]{return !printHello;});

        std::cout << "World " << std::endl << std::flush;

        printHello = true;
        cv.notify_one();
    /* finishing loop after 5 sec */
    } while (std::chrono::duration_cast<std::chrono::duration<double>>(
      std::chrono::high_resolution_clock::now() - start).count() < 5.0);

    /* finishing thread */
    exitSignal.set_value(true);
    threadHello.join();
}