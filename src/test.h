#ifndef H_test
#define H_test

#include <stack>
#include <queue>

class test{
public:
    test();
    void newWiz(std::string, int, int, std::string);
    bool getArgs(int, char*[], std::string&);
    bool readText(const std::string);
    double calculateDamge(int, bool);
    void addTrap(int);
    void printWiz();
    bool checkNumber(std::string);
    
private:
    std::string wizName;
    double wizPercentage;
    int wizFlat;
    bool toPeeveOrNotToPeeve;
    // stack for our traps
    std::stack<double> st;
    bool trapAdded;
    // save the stack by pushing into a queue
    std::stack<double> stSave;
};

#endif
