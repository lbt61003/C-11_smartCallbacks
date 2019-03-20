// Example program
#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;
using namespace std::placeholders;


typedef std::function<void(uint32_t)> cb_t;


class Client {
public:
    void func(uint32_t v) const
    {
        printf("instance member callback: %u\n", v);
    }
};

typedef std::function<void(Client&, uint32_t)> cb2_t;

std::vector<cb_t> callbacks_;
std::vector<cb2_t> callbacks2_;

// Register a callback.
void register_callback(const cb_t &cb)
{
    // add callback to end of callback list
    callbacks_.push_back(cb);
}

// Register a callback.
void register_callback(const cb2_t &cb)
{
    // add callback to end of callback list
    callbacks2_.push_back(cb);
}

int main()
{
    Client c;
    register_callback(std::bind(&Client::func, &c, std::placeholders::_1));
    
    std::function<void(Client&, uint32_t)> cbX = &Client::func;
    
    register_callback(cbX);
    
    for (auto &cb : callbacks_) {
        cb(__LINE__);   
    }
    
    for (auto &cb : callbacks2_) {
        cb(c, __LINE__);   
    }
}
