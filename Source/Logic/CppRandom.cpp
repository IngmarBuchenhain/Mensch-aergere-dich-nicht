
#ifndef MAEDN_RANDOM_HPP
#define MAEDN_RANDOM_HPP

// Used CppRandom.hpp from lecture and modified it for MAEDN

#include <random>
#include <iostream>

// Will be used to obtain a seed for the random number engine
std::random_device rd;

//Standard mersenne_twister_engine seeded with rd()
std::mt19937 gen(rd());

int getRandomNumberBetween(int lower, int upper){
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}

int main(){
    int values[7];
    for(int index = 0; index < 7; index++){
        values[index] = 0;
    }
    for(int i; i< 1000000; i++){
        values[getRandomNumberBetween(1, 6)] += 1;
    }

    std::cout << "Statistics:" << std::endl;
    std::cout << "1       2       3       4       5       6" << std::endl;
    std::cout << values[1] << " " << values[2] << " " << values[3] << " " << values[4] << " " << values[5] << " " << values[6] << std::endl;
}

#endif