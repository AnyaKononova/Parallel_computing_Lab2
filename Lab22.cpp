#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::string sharedString = "x";
std::mutex wait;

void axWorker() {

    while (sharedString.size() < 30) {
        wait.lock();
        sharedString += "a";
        std::this_thread::sleep_for(std::chrono::nanoseconds(500000000));
        sharedString += "x";
        wait.unlock();
        std::cout << " " << sharedString << std::endl;
    }

}

int main() {

    std::thread aThread(axWorker);
    std::thread xThread(axWorker);
    aThread.join();
    xThread.join();

    std::cout << "Final string: " << sharedString << std::endl;

    return 0;
}
