/*
* We already know how to implement interface -> 'pure virtual class' (remember virtual destructor)
*
* now we want to use them as 'consumer' via: 
* 1. 'Constructor injection'
* 2. 'Property injection'
*/

#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[cons] %ld->%ld: %f\n", from, to, amount);
    }
};

struct FileLogger : Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

// Constructor injection. logger type decided at construction of Bank class. References cannot be reseated.
struct Bank {
    Bank(Logger& logger) : logger{ logger } {};
    void make_transfer(long from, long to, double amount) const {
        logger.log_transfer(from, to, amount);
    }
private:
    Logger& logger;
};

// Property injection. Declare a pointer to point to the interface object.
// Declare a method to set the logger. Pointer can be reseated.
struct Bank2 {
    // This is regarding the point at the file's end description
    Bank2(Logger* logger) : logger{ logger } {}
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        if (logger) logger->log_transfer(from, to, amount);
    }
private:
    Logger* logger;
};


int main() {
    printf("=== With constructor injection ===\n");
    ConsoleLogger consoleLogger;
    Bank bank{ consoleLogger };
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 3000, 20.00);

    printf("\n=== With property injection ===\n");
    FileLogger fileLogger;
    Bank2 bank2{ nullptr };
    bank2.set_logger(&consoleLogger);
    bank2.make_transfer(1000, 2000, 49.95);
    bank2.set_logger(&fileLogger);
    bank2.make_transfer(2000, 3000, 20.00);
}

/* TAKEAWAY
* Using either depends on the task. If the underlying interface object does not
* change in the course of its lifecycle -> constructor injection.
* However, if it is needed to change the underlying object's member -> Property injection, with pointers.
* However, this flexibility comes at a price. You need to check if the property is valied
* by making sure that it is not assigned nullptr, or each time you use the property, check
* if it is valid and not nullptd (typical problem with pointers because they can be reseated).
* Another issue is that you have to think ahead how to initialize it. You could intialize as nullptr
* or a better way is to provide constructor initialization, but remember to use pointer for it.
*/