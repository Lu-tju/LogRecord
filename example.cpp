//
// Created by lu on 2024/9/6.
//

#include "logRecord.h"
#include <chrono>
#include <thread>
#include <ctime>

int main() {
    std::string filename = "行为树日志" + std::to_string(1) + "-";
    LogRecord logger("/home/lu/4.swarm_mission/logRecord", filename);

    auto start = std::chrono::high_resolution_clock::now();

    // your code here
    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double time = elapsed.count();

    std::cout << time << std::endl;
    logger.record("行为树 %d 耗时: %f s", 1, time);

    return 0;
}
