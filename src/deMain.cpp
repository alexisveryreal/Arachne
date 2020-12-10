#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits>

#include "test.h"

int main(int argc, char*argv[]){

    // ------------------------------------------------------------------
    //  Declare variables and display some cute headers...

    std::string stars, bars, dashes;
    std::string fName = "";
    const char	*bold = "\033[1m";
	const char	*unbold = "\033[0m";

    dashes.append(40,'-');
	stars.append(65, '*');
	bars.append(65, '=');

    test myTest;

    if(!myTest.getArgs(argc, argv, fName))
        exit(1);
    
    std::cout << stars << std::endl << bold << "Wizard 101 damage calculator" << std::endl;
    std::cout << std::endl;
    std::cout << bars << std::endl;
    std::cout << bold << "Current Wizards" << unbold << std::endl << std::endl;


    //logic here
    if(myTest.readText(fName)){
        myTest.printWiz();
    } else {
        std::cout << "Main: Error reading " << fName << "." << std::endl;
    }

    std::string spellVal = "";
    int spellDamage = 0;
    double damageOutput = 0.0;
    //bool isBlade = false;
    bool isTrap = false;

    while(true){
        std::cout << "Enter a spell damage value (t# for traps/shields) OR 'q' to quit: ";
        if(std::cin >> spellVal && spellVal != "q" ) {
            if(spellVal[0] == 't'){
                //its a trap value
                isTrap = true;

                // erase the "t"
                spellVal.erase(0, 1);
            } 
            // check to make sure the rest of the string is purely digits
            if(!myTest.checkNumber(spellVal)){
                std::cout << "\t Error! Please only enter integers for spell values" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            spellDamage = stoi(spellVal);
            if(isTrap){
                myTest.addTrap(spellDamage);
                // reset the boolean for next input
                isTrap = false;
                std::cout << std::endl;
            } else {
                //std::cout << "Spell damage: " << spellDamage << std::endl;
                damageOutput = myTest.calculateDamge(spellDamage);
                std::cout << bars << std::endl;
                std::cout <<  bold << "Damage output: " << damageOutput << unbold << std::endl << std::endl;

            }
            
        } else {
            break;
        }
    }

    std::cout << std::endl;


    std::cout << std::endl << stars << std::endl << "Game over, thank you for playing." << std::endl;

    return 0;
}