#include <iostream>
#include <future>

#include "threadpool.h"

int main()
{
    using namespace std::chrono_literals;
    std::vector<std::future<int> > futures;
    {
        ThreadPool pool(4);

        for (int i = 0; i < 8; ++i) {
            futures.emplace_back(pool.exec([](int i){
                std::this_thread::sleep_for(1s);
                return i;
            }, i));
        }
    }
    for (auto &future : futures) {
        std::cout << future.get();
    }
    return 0;
}
