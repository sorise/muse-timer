#include <iostream>
#include <memory>
#include "timer/timer_wheel.hpp"
#include "thread_pool/pool.hpp"
#include "thread_pool/executor_token.h"
#include "timer/timer_tree.hpp"

using namespace muse::pool;
using namespace muse::timer;

int test_fun1(int value){
    int i  = 10;
    int r = i + value;
    std::cout << "return: " << r << "\n";
    return r;
};

int main() {
    muse::timer::TimerTree tree;

    tree.setInternal(1000, [](int value)->void {
        printf("return: %d\n",value);
    },10);

    tree.setInternal(1500, [](int value)->void {
        printf("return: %d\n",value);
    },15);

    int i = 0;

    while (i++ < 10){
        tree.runTaskLoop();
        std::this_thread::sleep_for(std::chrono::milliseconds (1000));
    }

    std::cout << "main thread exit" << std::endl;

//
//    std::shared_ptr<ThreadPool>  pool = std::make_shared<ThreadPool>(
//            4 , 8 , 1024 ,
//                     ThreadPoolType::Flexible ,
//                     ThreadPoolCloseStrategy::WaitAllTaskFinish ,
//                     2500ms
//    );
//
//    TimerWheel wheel;
//    wheel.inject_thread_pool(pool);
//    wheel.setInterval(1000ms,[](){
//        std::cout << "task1 run: " << std::this_thread::get_id() << "\n";
//    });
//    wheel.setInterval(600ms,[](){
//        std::cout << "task2 run: " << std::this_thread::get_id() << "\n";
//    });
    std::cin.get();
    return 0;
}
