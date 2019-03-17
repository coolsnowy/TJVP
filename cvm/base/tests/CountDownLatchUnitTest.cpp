#include "CountDownLatch.h"
#include <thread>
#include <functional>
#include <vector>
#include <iostream>

void func(CountDownLatch &cdl)
{
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    cdl.countDown();
    std::cout << "Count Down " << cdl.getCounts() << std::endl;
}

int main()
{
    const int num = 10;
    CountDownLatch cdl(num);

    std::vector<std::thread> threads;
    threads.reserve(num);
    for (int i=0; i<num; i++) {
        threads[i] = std::thread(std::bind(func, std::ref(cdl)));
        threads[i].detach();
    }

    cdl.wait();
    std::cout << cdl.getCounts() << std::endl;

    return 0;
}
