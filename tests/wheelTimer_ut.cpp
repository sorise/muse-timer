#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "timer/timer_wheel.hpp"

using namespace muse::timer;

class Normal{
public:
    Normal(int _value, const std::string& _name)
            :value(_value), name( std::move(_name)){}

    std::string setValueAndGetName(int _new_value){
        this->value = _new_value;
        return this->name;
    }

    int getValue(){
        return this->value;
    }

private:
    int value;
    std::string name;
};

TimerWheel timer;

TEST_CASE("normal", "[TimerWheel]"){
    Normal normal(14, "remix");

    timer.setTimeout(1000ms, &Normal::setValueAndGetName, &normal, 76);

    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    REQUIRE(normal.getValue() == 76);
}


TEST_CASE("normal", "[TimerWheel]"){
    auto vk= timer.setInterval(1000ms, [](int value){
        std::cout << "logger: " << value << std::endl;
    },500);


    vk->cancel();

    TimerWheel::clearTimeout(vk);
}