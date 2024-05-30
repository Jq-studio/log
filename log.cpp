#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <stdarg.h>
#include <fstream>


enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

std::string TimeStamp()
{
    char str[32]{};
    time_t a = time(nullptr);
    struct tm time_info;
    if (localtime_s(&time_info, &a) == 0) strftime(str, sizeof(str), "(%d.%m.%y | %H:%M:%S)", &time_info);
    return str;
}

class Logger {
public:
    Logger(LogLevel level) : level(level) {
        buffer.resize(10000);
        
    }
    void log(LogLevel messageLevel, const char * fmt, ...) {
        va_list args;
        va_start(args, fmt);
        if (messageLevel >= level) {
            switch (messageLevel) {
            case TRACE:
                sprintf_s(buffer.data(), buffer.size(), "[TRACE] %s \n", fmt);
                break;

            case DEBUG:
                sprintf_s(buffer.data(), buffer.size(), "[DEBUG] %s \n", fmt);
                break;

            case INFO:
                sprintf_s(buffer.data(), buffer.size(), "[INFO] %s \n", fmt);
                break;

            case WARNING:
                sprintf_s(buffer.data(), buffer.size(), "[WARNING] %s \n", fmt);
                break;

            case ERROR:
                sprintf_s(buffer.data(), buffer.size(), "[ERROR] %s \n", fmt);
                break;
            }
            
        vprintf(buffer.data(), args);
         }


         va_end(args);
    }
        

private:
    LogLevel level;
    std::vector<char> buffer;
 
};

#define TRACE(logger, message) logger ## .log(TRACE, "%s %s: line: %d %s", TimeStamp().c_str() ,  __FILE__ , __LINE__, message)
#define DEBUG(logger, message) logger ## .log(DEBUG, "%s %s: line: %d %s", TimeStamp().c_str() ,  __FILE__ , __LINE__, message)
#define INFO(logger, message) logger ## .log(INFO, "%s %s: line: %d %s", TimeStamp().c_str() ,  __FILE__ , __LINE__, message)
#define WARNING(logger, message) logger ## .log(WARNING, "%s %s: line: %d %s", TimeStamp().c_str() ,  __FILE__ , __LINE__, message)
#define ERROR(logger, message) logger ## .log(ERROR, "%s %s: line: %d %s", TimeStamp().c_str() ,  __FILE__ , __LINE__, message)


int main() {
    
    Logger logger(TRACE);
    TRACE(logger, "etedgdfg");
    
   return 0;
}