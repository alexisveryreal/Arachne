#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include "test.h"

/*---------------------------------------
Constructor
PARAMETER(S): NONE
POSTCONDITION(S): initializes everything to 0
---------------------------------------*/
test::test(){
    wizName = "";
    wizFlat = 0;
    wizPercentage = 0.0;
}

/*---------------------------------------
FUNCTION NAME: newWiz
PARAMETER(S): int, int
RETURN TYPE: void
POSTCONDITION(S): creates a new wizard
---------------------------------------*/
void test::newWiz(std::string wizardName, int damagePercent, int damageFlat){

    //std::setprecision(2);
    wizName = wizardName;
    wizPercentage = (double) damagePercent / 100;
    //std::cout << std::setprecision(2) << std::fixed << wizPercentage << std::endl;
    wizFlat = damageFlat;
}

/*---------------------------------------
FUNCTION NAME: getArgs
PARAMETER(S): yes
RETURN TYPE: BOOl
POSTCONDITION(S): passes in arguements and if all
arguements are valid returns true, else returns
error messsage and false.
---------------------------------------*/
bool test::getArgs(int argc, char* argv[], std::string& test){

    std::stringstream myStream;

    bool fFlag = false;

    // usage print
    if(argc == 1){
        std::cout << "Usage: ./test -gf <filename>";
        std::cout << std::endl;
        return false;
    }

    // if we have more than 3 arguments, error
    if(argc > 3){
        std::cout << "Error, invalid command line options." << std::endl;
        return false;
    }

    // for loop, set up to loop through all argc
    for(int i = 1; i < argc; i++){
        if(std::string(argv[i]) == "-gf"){
            if(!fFlag){
                myStream << argv[i+1];
                myStream >> test;
                myStream.clear();
                fFlag = true;
            }
        }
    }

    // if never changed the fFlag to true, error
    if(!fFlag){
        std::cout << "Error, invalid test file specifier." << std::endl;
        return false;
    }

    // if we get here everything read in correctly
    return true;
}

/*---------------------------------------
FUNCTION NAME: readText
PARAMETER(S): Yes
RETURN TYPE: bool
POSTCONDITION(S): read a text file,
File includes: title, damagePercent, damageFlat
if valid: creates a new wiz using newWiz
function and adding their damages
---------------------------------------*/
bool test::readText(const std::string inputFile){
    std::ifstream inFile;
    std::stringstream reader;
    std::string wizName, damageNumbers;
    std::string theName;
    int damagePercent, damageFlat;

    inFile.open(inputFile);
    if(inFile.is_open()){
        getline(inFile, wizName, '\n');
        theName = wizName;

        getline(inFile, damageNumbers, '\n');
        damagePercent = stoi(damageNumbers);
        
        // can't have negative damage smh
        if(damagePercent < 0){
            std::cout << "Error, invalid damage percent." << std::endl;
            return false;
        }
        
        getline(inFile, damageNumbers, '\n');
        damageFlat = stoi(damageNumbers);
        
        // can't have negative flat damage smh
        if(damageFlat < 0){
            std::cout << "Error, invalid flat damage." << std::endl;
            return false;
        }


        newWiz(theName, damagePercent, damageFlat);

        inFile.close();
    }
    return true; 


}
/*---------------------------------------------------------------
FUNCTION NAME: calculateDamage
PARAMETER(S): int
RETURN TYPE: int
POSTCONDITION(S): calculates the total damage output from the spell
---------------------------------------------------------------*/
double test::calculateDamge(int spellDamage){
    double totalDamage = 0;

    //Multiply by percentage
    totalDamage = (double) spellDamage;

    // damage is additive so its damage + (damage x %school)
    totalDamage += spellDamage * wizPercentage;
    totalDamage = floor(totalDamage);

    //add flat Damage
    totalDamage += wizFlat;

    return totalDamage;
}

/*---------------------------------------------------------------
FUNCTION NAME: printWiz
PARAMETER(S): 
RETURN TYPE: void
POSTCONDITION(S): if it exists, prints out the current wizard
---------------------------------------------------------------*/
void test::printWiz(){
    
    double actualPercentage = 0.0;

    std::cout << " Wizard Name: ";
    std::cout << wizName << std::endl;

    std::cout << " --> Damage Percentage: ";
    actualPercentage = wizPercentage * 100;
    std::cout << actualPercentage << "%" << std::endl;
    
    std::cout << " --> Damage Flat: ";
    std::cout << wizFlat << std::endl;

    std::cout << std::endl;
}
/*---------------------------------------------------------------
FUNCTION NAME: checkNumber
PARAMETER(S): string
RETURN TYPE: bool
POSTCONDITION(S): checks to make sure the string read in is a int
---------------------------------------------------------------*/
bool test::checkNumber(std::string str){
    for (size_t i = 0; i < str.length(); i++)
    if (isdigit(str[i]) == false)
        return false;
    return true;
}