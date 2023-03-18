/* 

    Projet SAE Robot
    goofyBot
    TEAM COOCHIE - IUT Nice Côte D'Azur 
    Licence MIT - 2023 

*/

#include <mbed.h>
#include <robot.hpp>
#include <ihm.hpp>

// Programmes
#include <confettis.hpp>
#include <carre.hpp>
#include <suivi.hpp>

Robot goofyBot;

int main() {
    ihmBoot(goofyBot);
    return 0;
}