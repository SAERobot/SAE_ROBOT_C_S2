#include <mbed.h>
#include <robot.hpp>
#include <ihm.hpp>

// Programme carré

void carre(Robot& goofyBot) {
    int longueur = ihmSel(goofyBot);

    for(int i = 0; i < 4; i++) {
        goofyBot.move(42,46);
        wait_us ((longueur / 45.5) * 1000000) ;
        goofyBot.move(0,0);
        wait_us(45000);
        // augmentation et diminution progressive de la vitesse
        for(float speed = 25; speed < 90; speed += 5) {
            goofyBot.move(speed, -70);
            wait_us(20000);
        }
        for(float speed = 100; speed > 90; speed -= 5) {
            goofyBot.move(speed, -70);
            wait_us(20000);
        }
    }

    goofyBot.move(0,0);
}