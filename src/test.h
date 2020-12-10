#ifndef H_test
#define H_test

#include <stack>

class test{
public:
    test();
    void newWiz(std::string, int, int);
    bool getArgs(int, char*[], std::string&);
    bool readText(const std::string);
    double calculateDamge(int);
    void addBlade(int);
    void printWiz();
    bool checkNumber(std::string);
    
private:
    std::string wizName;
    double wizPercentage;
    int wizFlat;
    // stack for our blades
    std::stack<int> st;
};

#endif
