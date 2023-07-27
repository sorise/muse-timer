#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "timer/timer_tree.hpp"
#include <thread>

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

int test_fun1(int value){
    int i  = 10;
    return i + value;
};


TEST_CASE("normal", "[timer_tree]"){
    TimerTree tree;

    tree.setTimeout(1000, test_fun1, 25);

    std::this_thread::sleep_for(std::chrono::milliseconds(1700));

    REQUIRE_NOTHROW(tree.runTask());

}

TEST_CASE("class number pointer", "[timer_tree]"){
    TimerTree tree;
    Normal normal(14, "remix");

    auto token = tree.setTimeout(1000, &Normal::setValueAndGetName, &normal, 76);

    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    tree.runTask();
    tree.clearTimeout(token);

    REQUIRE(normal.getValue() == 76);
}


