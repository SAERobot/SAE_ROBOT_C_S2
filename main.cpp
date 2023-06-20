/* 

    Projet SAE Robot S2
    goofyBot
    TEAM noName - IUT Nice Côte D'Azur 
    Licence MIT - 2023 

*/

#include <mbed.h>
#include <robot.hpp>
#include <ihm.hpp>
#include <audio.hpp>

#define T 0.001

Robot goofyBot;

int main() {
    goofyBot.moteurDroit.period(T);
    goofyBot.moteurGauche.period(T);
    ihmBoot(goofyBot);
    return 0;
}