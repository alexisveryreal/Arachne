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
     
private:
    std::string wizName;
    double wizPercentage;
    int wizFlat;
};

#endif
