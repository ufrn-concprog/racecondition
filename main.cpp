#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

int counter = 0;

void incrementCounter() {
  for (int i = 1; i <= 1000; i++) {
    int time = rand() % 10 + 1;
    int temp = counter;
    // Random delay to make it easier to observe the effects of race conditions in practice
    std::this_thread::sleep_for(std::chrono::microseconds(time));
    temp = temp + 1;
    counter = temp;
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
