#include <iostream>
#include <memory>
#include "timer/timer_wheel.hpp"
#include "thread_pool/pool.hpp"
#include "thread_pool/executor_token.h"

using namespace muse::pool;
using namespace muse::timer;

int main() {
    std::shared_ptr<ThreadPool>  pool = std::make_shared<ThreadPool>(
            4 , 8 , 1024 ,
                     ThreadPoolType::Flexible ,
                     ThreadPoolCloseStrategy::WaitAllTaskFinish ,
                     2500ms
    );

    TimerWheel wheel;
    wheel.inject_thread_pool(pool);
    wheel.setInterval(1000ms,[](){
        std::cout << "task1 run: " << std::this_thread::get_id() << "\n";
    });
    wheel.setInterval(600ms,[](){
        std::cout << "task2 run: " << std::this_thread::get_id() << "\n";
    });
    std::cin.get();
    return 0;
}
