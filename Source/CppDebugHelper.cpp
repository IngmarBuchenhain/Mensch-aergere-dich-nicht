#include<iostream>

#include "CppDebugHelper.hpp"

extern const bool DEBUG = true;

void printDebug(std::string message){
    if(DEBUG){
        std::cout << std::endl << "DEBUG: " << message;
    }
}

void printError(std::string message){
    std::cout << std::endl << "ERROR: " << message;
}