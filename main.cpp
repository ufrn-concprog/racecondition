#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

int counter = 0;

void incrementCounter() {
    for (int i = 1; i <= 1000; i++) {
        counter++;
    }
}

int main() {
    srand(time(NULL));

    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final value of counter: " << counter << std::endl;

    return 0;
}
