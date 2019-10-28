#include <iostream>
using namespace std;

//#define TEST

#ifdef TEST
    bool test_1() {

    }
#else
    int run() {

    }
#endif

int main() {
    #ifdef TEST
        if (!test_1()) {
            return -1;
        }
        return 0;
    #else 
        return run();
    #endif
}