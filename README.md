## [muse-timer](#)
一个使用 C++ 11 实现的两个定时器timer，提供了两个毫秒级定时器类,由于本人经常做前端，所有使用了JavaScript的定时器接口名称。

----
* **TimerTree** 使用红黑树使用的单线程非线程安全的的定时器
* **TimerWheel** 使用时间轮算法实现的五层时间轮毫秒级定时器，支持时间精度损失自动修复、支持结合线程池。

```shell
#linux/windows install、安装需要使用到CMAKE。
cmake -S . -B build
cmake --build build
cd build 
sudo make install #需要管理员权限 ubuntu 例子
```

### [1. TimerTree 使用例子](#)
基于红黑树的定时器一般配合 epoll或者 poll之类的使用。

创建定时器
```c++
TimerTree tree;
```

#### 1.1 添加定时任务
支持任意方法，可以函数指针、lambda、函数符、成员函数指针。
```cpp
Normal normal(14, "remix");
// 添加一个类成员函数指针，时间刻度是毫秒，此处是1000毫秒
tree.setTimeout(1000, &Normal::setValueAndGetName, &normal, 76);
// 添加一个lambda
tree.setTimeout(1000, [](){
    printf("run me");
});
```

#### 1.2 查看最近的任务还要多久才会支持
使用checkTimeout将会返回一个毫秒数，表示最近的任务还需要多久才会执行，没有任务返回 `-1`。
```c++
time_t t = tree.checkTimeout();
```

#### 1.3 执行任务
所有到期的任务都会逐一执行完成。
```c++
tree.runTaskLoop();
```
执行一个已经到期的任务
```c++
tree.runTask();
```

#### 1.4 取消定时任务
所有到期的任务都会逐一执行完成
```c++
auto token = tree.setTimeout(1000, &Normal::setValueAndGetName, &normal, 76);

tree.clearTimeout(token);
```

### [2. TimerWheel 使用](#)
TimerWheel 会自动启动一个线程去运行指针，**使用该类应该了解时间轮算法的基本原理**。

#### 2.1 添加一个超时任务
```c++
TimerWheel timer; //此处会后台启动一个线程推动时间指针前进

timer.setTimeout(1000ms, [](int value){
    std::cout << "logger: " << value << std::endl;
}, 500);
```

#### 2.2 添加一个循环定时任务
使用setInterval接口，下面的函数会每隔1000毫秒执行一次。
```c++
timer.setInterval(1000ms, [](int value){
    std::cout << "logger: " << value << std::endl;
}, 500);
```

#### 2.3 取消超时任务
使用静态方法 clearTimeout 即可。
```c++
auto token = timer.setTimeout(1000ms, [](int value){
    std::cout << "logger: " << value << std::endl;
}, 500);

TimerWheel::clearTimeout(token);
```

#### 2.4 取消定时任务
使用静态方法 clearInterval 即可。
```c++
auto token = timer.setInterval(1000ms, [](int value){
    std::cout << "logger: " << value << std::endl;
}, 500);

TimerWheel::clearInterval(token); //取消任务
```

#### 2.5 将定时器任务交给线程池执行  
默认情况下定时器任务会直接在定时器线程中执行，如果需要将任务交给线程池执行，可以使用 inject_thread_pool 方法注入一个线程池。
```cpp
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
```