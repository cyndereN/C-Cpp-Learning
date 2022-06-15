#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>

using std::cout;  using std::endl;
using std::string; using::vector;

const size_t kNumThreads = 10;

std::mutex mtx;
void greet(int id) { 
    // std::this_thread::sleep_for(std::chrono::seconds(5));  // won't print, because main func finishes first
    std::lock_guard<std::mutex> lg(mtx);
    // mtx.lock();
    cout << "Hello! My name is " << id << endl;
    // mtx.unlock();
}

int main() {
    cout << "Great from my threads.." << endl;
    std::thread thread1(greet, 1);
    std::thread thread2(greet, 2);

    thread1.join();
    thread2.join();

    vector<std::thread> threads;

    for(size_t i = 0; i<kNumThreads ; ++i) {
        threads.push_back(std::thread(greet, i));
        // threads[i].join(); // will sequenciall excecute
    }

    for (std::thread& t : threads) { // pass by reference
        t.join();
    }

    cout << "All greetings done!" << endl;
}