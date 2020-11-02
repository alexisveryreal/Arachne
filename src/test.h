#ifndef H_test
#define H_test


class test{
public:
    test();
    void newWiz(std::string, int, int);
    bool getArgs(int, char*[], std::string&);
    bool readText(const std::string);
    double calculateDamge(int);
    void printWiz();
    bool checkNumber(std::string);
    
private:
    std::string wizName;
    double wizPercentage;
    int wizFlat;
};

#endif
