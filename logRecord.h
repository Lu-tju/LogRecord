//
// Created by lu on 2024/9/6.
//

#ifndef LOGRECORD_H
#define LOGRECORD_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class LogRecord {
public:
    LogRecord(const std::string& directoryPath, const std::string& fileHeader) {
        std::string fileName = generateFileName();
        filePath_ = directoryPath + "/" + fileHeader + fileName +  + ".csv";

        logFile_.open(filePath_, std::ios::out | std::ios::trunc);
        if (!logFile_) {
            std::cerr << "无法创建或打开文件: " << filePath_ << std::endl;
        }
    }

    LogRecord(const std::string& directoryPath) {
        std::string fileName = generateFileName();
        filePath_ = directoryPath + "/" + fileName + ".csv";

        logFile_.open(filePath_, std::ios::out | std::ios::trunc);
        if (!logFile_) {
            std::cerr << "无法创建或打开文件: " << filePath_ << std::endl;
        }
    }

    ~LogRecord() {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }

    template<typename... Args>
    void record(const std::string& formatStr, Args... args) {
        if (logFile_.is_open()) {
            std::ostringstream oss;
            format(oss, formatStr, args...);
            logFile_ << "["<<generateFileName() <<"] ";
            logFile_ << oss.str() << std::endl;
        } else {
            std::cerr << "文件未打开: " << filePath_ << std::endl;
        }
    }

private:
    std::string filePath_;
    std::ofstream logFile_;

    std::string generateFileName() {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        std::ostringstream oss;
        oss << std::put_time(localTime, "%Y-%m-%d_%H-%M-%S");
        return oss.str();
    }

    template<typename... Args>
    void format(std::ostringstream& oss, const std::string& formatStr, Args... args) {
        int size = snprintf(nullptr, 0, formatStr.c_str(), args...) + 1;
        if (size <= 0) {
            throw std::runtime_error("Error during formatting.");
        }
        auto sizeBuffer = static_cast<size_t>(size);
        std::unique_ptr<char[]> buffer(new char[sizeBuffer]);
        snprintf(buffer.get(), sizeBuffer, formatStr.c_str(), args...);
        oss << buffer.get();
    }
};

#endif //LOGRECORD_H
