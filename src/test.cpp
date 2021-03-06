#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stack>
#include <math.h>
#include <stdlib.h>
#include "test.h"

/*---------------------------------------
Constructor
PARAMETER(S): NONE
POSTCONDITION(S): initializes everything to 0
---------------------------------------*/
test::test()
{
    wizName = "";
    wizFlat = 0;
    wizPercentage = 0.0;
    toPeeveOrNotToPeeve = false;
    trapAdded = false;
    bladeAdded = false;
    resistAdded = false;
    wizPierce = 0.0;
    criticalValue = 0.0;
    critPassed = false;
}
/*---------------------------------------
FUNCTION NAME: newWiz
PARAMETER(S): int, int
RETURN TYPE: void
POSTCONDITION(S): creates a new wizard
---------------------------------------*/
void test::newWiz(std::string wizardName, int damagePercent, int damageFlat, std::string choice, int daPierce)
{

    //std::setprecision(2);
    wizName = wizardName;
    wizPercentage = (double)damagePercent / 100;
    //std::cout << std::setprecision(2) << std::fixed << wizPercentage << std::endl;
    wizFlat = damageFlat;
    wizPierce = (double)daPierce / 100;
    if (choice == "pvp")
    {
        toPeeveOrNotToPeeve = true;
    }
    else
    {
        toPeeveOrNotToPeeve = false;
    }
}

/*---------------------------------------
FUNCTION NAME: getArgs
PARAMETER(S): yes
RETURN TYPE: BOOl
POSTCONDITION(S): passes in arguements and if all
arguements are valid returns true, else returns
error messsage and false.
---------------------------------------*/
bool test::getArgs(int argc, char *argv[], std::string &test)
{

    std::stringstream myStream;

    bool fFlag = false;

    // usage print
    if (argc == 1)
    {
        std::cout << "Usage: ./test -gf <filename>";
        std::cout << std::endl;
        return false;
    }

    // if we have more than 3 arguments, error
    if (argc > 3)
    {
        std::cout << "Error, invalid command line options." << std::endl;
        return false;
    }

    // for loop, set up to loop through all argc
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-gf")
        {
            if (!fFlag)
            {
                myStream << argv[i + 1];
                myStream >> test;
                myStream.clear();
                fFlag = true;
            }
        }
    }

    // if never changed the fFlag to true, error
    if (!fFlag)
    {
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
bool test::readText(const std::string inputFile)
{
    std::ifstream inFile;
    std::stringstream reader;
    std::string wizName, damageNumbers;
    std::string theName;
    int damagePercent, damageFlat, damagePierce;
    std::string pvpOrPve, choice;

    inFile.open(inputFile);
    if (inFile.is_open())
    {
        getline(inFile, wizName, '\n');
        theName = wizName;

        getline(inFile, damageNumbers, '\n');
        damagePercent = stoi(damageNumbers);

        // can't have negative damage smh
        if (damagePercent < 0)
        {
            std::cout << "Error, invalid damage percent."
                      << "\n";
            return false;
        }

        getline(inFile, damageNumbers, '\n');
        damageFlat = stoi(damageNumbers);

        // can't have negative flat damage smh
        if (damageFlat < 0)
        {
            std::cout << "Error, invalid flat damage."
                      << "\n";
            return false;
        }

        // get pierce
        getline(inFile, damageNumbers, '\n');
        damagePierce = stoi(damageNumbers);

        if (damagePierce < 0)
        {
            std::cout << "Error, invalid pierce."
                      << "\n";
            return false;
        }

        // get the PVP or PVE choice and make it all lowercase
        getline(inFile, pvpOrPve, '\n');
        for (size_t i = 0; i < pvpOrPve.length(); i++)
        {
            // stores in string to be sent to newWiz
            choice += tolower(pvpOrPve[i]);
        }

        newWiz(theName, damagePercent, damageFlat, choice, damagePierce);

        inFile.close();
    }
    return true;
}

/*---------------------------------------------------------------
FUNCTION NAME: calculateDamage
PARAMETER(S): int, bool
RETURN TYPE: int
POSTCONDITION(S): calculates the total damage output from the spell.
if showCrit = true, will return the critical damage output, based
on if the user is in PVP or PVE, from what user entered in their
text file. 
---------------------------------------------------------------*/
double test::calculateDamge(int spellDamage, bool showCrit)
{
    double totalDamage = 0.0;
    double critValue = 0.0;
    //bool isShield = false; // if shield, we can check if we need to use pierce

    //Multiply by percentage
    totalDamage = (double)spellDamage;

    if (showCrit)
    {

        if (critPassed)
        {
            // set the critical value to the one we passed
            std::cout << "Applying passed in crit...x" << criticalValue << "\n";
            critValue = criticalValue;
        }
        else
        {
            //else we do historical values of 1.33 and 2x

            // if we crit then we do 2x damage in pve and 1.33 in pvp
            if (toPeeveOrNotToPeeve == false)
            {
                std::cout << "Applying PVE crit...x2\n";
                critValue = 2.0;
            }
            else
            {
                std::cout << "Applying PVP crit...x1.33\n";
                critValue = 1.33;
            }
        }

        totalDamage *= critValue;
        totalDamage += totalDamage * wizPercentage;
    }
    else
    {
        // damage is additive so its damage + (damage x %school)
        totalDamage += spellDamage * wizPercentage;
    }

    totalDamage = floor(totalDamage);

    if (bladeAdded)
    {
        double blade;
        double printPercentage;
        std::cout << "\n";

        for (std::queue<double> printQ = qu; !printQ.empty(); printQ.pop())
        {
            blade = printQ.front();
            if (blade > 0)
            {
                std::cout << "Q^Q Blade +";
            }
            else
            {
                std::cout << "Q.Q Blade ";
            }
            printPercentage = blade * 100;
            std::cout << printPercentage << "%\n";

            totalDamage += totalDamage * (double)blade;
            totalDamage = floor(totalDamage);
        }
    }

    //add flat Damage
    totalDamage += wizFlat;

    // if there were traps added, add to the calculation
    if (trapAdded)
    {
        double trap;
        double printPer;
        std::cout << "\n";
        // make a dummy stack to copy the contents of the current stack to pop
        for (std::stack<double> dump = st; !dump.empty(); dump.pop())
        {
            trap = dump.top();
            if (trap > 0)
            {
                std::cout << "^-^ Trap   +";
            }
            else
            {
                // if the wizard has pierce
                if (wizPierce > 0.0)
                {
                    std::cout << "*^* Pierce  +";
                    printPer = wizPierce * 100;
                    std::cout << printPer << "%"
                              << "\n";
                }
                // since shields are negative
                // we add a positive pierce
                trap += wizPierce;

                std::cout << ":-; Shield ";
                // isShield = true;
            }
            printPer = trap * 100;
            std::cout << printPer << "%"
                      << "\n";

            // EX: D = 120 + (120 x 25%)
            totalDamage += totalDamage * (double)trap;
            totalDamage = floor(totalDamage);
            //std::cout << totalDamage << "\n";
        }
    }

    // Resist
    if (resistAdded)
    {
        std::cout << "\n";
        double printPer;
        double theResist = rez.at(0);
        // resist has to follow pierce as well
        // we are assuming universal pierce
        if (wizPierce > 0)
        {
            std::cout << "*^* Pierce  +";
            printPer = wizPierce * 100;
            std::cout << printPer << "%"
                      << "\n";

            // since resist is negative
            // we add the pierce
            theResist += wizPierce;
        }
        // we have no pierce calculate normally
        printPer = theResist * 100;
        std::cout << "`~` Resist  ";
        std::cout << printPer << "%"
                  << "\n";

        totalDamage += totalDamage * (double)theResist;
        totalDamage = floor(totalDamage);
    }

    // TODO: Flat Resist

    return totalDamage;
}
/*---------------------------------------------------------------
FUNCTION NAME: addTrap
PARAMETER(S): int - percentage that Trap takes in, or 
the shield decreases
RETURN TYPE: void
POSTCONDITION(S): Pushes the trap into a stack (LIFO)
Prints out the trap that was just added. 
---------------------------------------------------------------*/
void test::addTrap(int addOrSub)
{

    double trapDec = (double)addOrSub / 100;

    // adds the value on top of the stack
    st.push(trapDec);

    if (addOrSub > 0)
    {
        std::cout << "\tThe trap   +";
    }
    else
    {
        std::cout << "\tThe shield ";
    }

    std::cout << addOrSub << "% was added"
              << "\n";
    trapAdded = true;
}
/*---------------------------------------------------------------
FUNCTION NAME: addBlade
PARAMETER(S): int (pos/neg)
RETURN TYPE: void
POSTCONDITION(S): pushes blade onto a queue (FIFO), prints out
the blade that was just added.  
---------------------------------------------------------------*/
void test::addBlade(int myBlade)
{
    double bladeDecimal = (double)myBlade / 100;

    qu.push(bladeDecimal);

    std::cout << "\tThe blade ";
    if (myBlade > 0)
    {
        std::cout << " +";
    }
    else
    {
        std::cout << " ";
    }

    std::cout << myBlade << "% was added"
              << "\n";
    bladeAdded = true;
}
/*---------------------------------------------------------------
FUNCTION NAME: addResist
PARAMETER(S): int
RETURN TYPE: void
POSTCONDITION(S): adds resist to the boss always. 
---------------------------------------------------------------*/
void test::addResist(int enemyResist)
{
    double resistDecimal = (double)enemyResist / 100;

    rez = {resistDecimal};

    std::cout << "\tAdded enemy " << enemyResist << "% resist"
              << "\n";

    resistAdded = true;
}

/*---------------------------------------------------------------
FUNCTION NAME: printWiz
PARAMETER(S): 
RETURN TYPE: void
POSTCONDITION(S): if it exists, prints out the current wizard
---------------------------------------------------------------*/
void test::printWiz()
{

    double actualPercentage = 0.0;

    std::cout << " Wizard Name: ";
    std::cout << wizName << std::endl;

    std::cout << " --> Damage Percentage: ";
    actualPercentage = wizPercentage * 100;
    std::cout << actualPercentage << "%" << std::endl;

    std::cout << " --> Damage Flat: ";
    std::cout << wizFlat << std::endl;

    std::cout << " --> Pierce Percentage: ";
    actualPercentage = wizPierce * 100;
    std::cout << actualPercentage << "%" << std::endl;

    std::cout << std::endl;
}

/*---------------------------------------------------------------
FUNCTION NAME: checkNumber
PARAMETER(S): string
RETURN TYPE: bool
POSTCONDITION(S): checks to make sure the string read in is a int
---------------------------------------------------------------*/
bool test::checkNumber(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
        {
            // if it's a negative we check the rest
            if (str[0] == '-')
            {
                continue;
            }

            return false;
        }
    return true;
}
/*---------------------------------------------------------------
FUNCTION NAME: setCrit
PARAMETER(S): double 
RETURN TYPE: void
POSTCONDITION(S): sets the crit value. Should be the number 
that the player sees when hovering over a spell.
---------------------------------------------------------------*/
void test::setCrit(double criticalValuePassedIn)
{
    criticalValue = criticalValuePassedIn;
    critPassed = true;
    std::cout << "\tThe crit value x" << criticalValuePassedIn << "% was added!"
              << "\n";
}

/*---------------------------------------------------------------
FUNCTION NAME: checkDouble
PARAMETER(S): string
RETURN TYPE: bool
POSTCONDITION(S): checks if the string read in is a double. 
---------------------------------------------------------------*/
bool test::checkDouble(std::string str)
{
    char *end;
    strtod(str.c_str(), &end);
    if (end == str.c_str() || *end != '\0')
    {
        return false;
    }
    return true;
}

// empty function desc for future
/*---------------------------------------------------------------
FUNCTION NAME: 
PARAMETER(S): 
RETURN TYPE: 
POSTCONDITION(S): 
---------------------------------------------------------------*/