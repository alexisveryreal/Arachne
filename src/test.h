#ifndef H_test
#define H_test

#include <stack>
#include <queue>
#include <array>

class test{
public:
    test();
    void newWiz(std::string, int, int, std::string, int);
    bool getArgs(int, char*[], std::string&);
    bool readText(const std::string);
    double calculateDamge(int, bool);
    void addTrap(int);
    void addBlade(int);
    void addResist(int);
    void printWiz();
    bool checkNumber(std::string);
    
private:
    std::string wizName;
    double wizPercentage;
    int wizFlat;
    bool toPeeveOrNotToPeeve;
    double wizPierce;

    bool resistAdded;
    std::array<double, 1> rez;
    // stack for our traps
    std::stack<double> st;
    bool trapAdded;
    
    // queue for blades
    std::queue<double> qu;
    bool bladeAdded;
};

#endif
