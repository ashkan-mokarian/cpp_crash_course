/*
* Polymorphism allows to reuse code -> better maintainability
* if you know the type type at runtime -> runtime polymorphism
* For example for a logger class that logs in different environments, e.g. logging
* to a server, logging locally on a file, or sending logs to a printer. and it is
* decided at runtime which interface to use. Foe example an administrator wishes
* to log locally to troubleshoot the server problem, while the server is running.
*/

#include <cstdio>
#include <stdexcept>

// We have different types of loggers
// Console logger
struct ConsoleLogger
{
    void log_transfer(long from, long to, double amount) const {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};
// File logger
struct FileLogger
{
    void log_transfer(long from, long to, double amount) const {
        printf("[file] %ld -> %ld: %g\n", from, to, amount);
    }
};

/*
* Naive way of choosing at runtime
*/
enum class LoggerType {
    Console,
    File,
};

// This class doesn't want to deal with logging nuances, but the actual bank transfers
struct Bank {
    Bank() : type{ LoggerType::Console } {}
    void set_logger(LoggerType new_type) {
        type = new_type;
    }
    void make_transfer(long from, long to, double amount) {
        // snip: make transactions
        switch (type)
        {
        case LoggerType::Console: {
            consoleLogger.log_transfer(from, to, amount);
            break;
        } case LoggerType::File: {
            fileLogger.log_transfer(from, to, amount);
            break;
        } default: {
            throw std::logic_error("Invalid logger type");
            break;
        }
        }
    }
private:
    ConsoleLogger consoleLogger;
    FileLogger fileLogger;
    LoggerType type;
};

int main() {
    Bank bank;
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.00);
    bank.set_logger(LoggerType::File);
    bank.make_transfer(3000, 2000, 75.00);
}

/* TAKEAWAY:
* To make a new logger type, you have to do a lot of stuff:
* - create a new logger class
* - add the new logger type to the enum class
* - add a new switch case to the Bank class
* - add the new logging class member to bank class
* maintaining and extending this code is very difficult
* ---->>>>> Interfaces:
* 'interface' is a shared boundary that contains no data or code. It defines
* 'function signatures' that all implementations of the interface agree to support.
* An 'implementation' is code or data that declares support for an interface. 
* You can think of interfaces as a contract between the class that implements
* the interface and the user ('consumer') of that class. the 'consumer' doesn't
* need to know about the implementation of ConsoleLogger for example. They only
* need to know the contract. The Bank class only needs to know that for logging
* it needs to use log_transfer.
*/