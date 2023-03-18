#include <mbed.h>
#include <robot.hpp>

// Programme confettis

void fuckmypussy(Robot& goofyBot) {
    goofyBot.IHM_Led1.write(0);
    goofyBot.IHM_Led2.write(0);
    goofyBot.IHM_Led3.write(0);
    goofyBot.IHM_Led4.write(0);
    wait_us(50000);
    goofyBot.IHM_Led1.write(1);
    wait_us(50000);
    goofyBot.IHM_Led2.write(1);
    wait_us(50000);
    goofyBot.IHM_Led3.write(1);
    wait_us(50000);
    goofyBot.IHM_Led4.write(1);
    wait_us(50000);
    goofyBot.IHM_Led1.write(0);
    goofyBot.IHM_Led2.write(0);
    goofyBot.IHM_Led3.write(0);
    goofyBot.IHM_Led4.write(0);
}

void confettis(Robot& goofyBot) {
    int etat = 1;
    
    while (1) {
        goofyBot.jackVal = goofyBot.jack.read();
        goofyBot.dIntVal = goofyBot.captLigneDroiteInt.read() * 3.3;
        goofyBot.dExtVal = goofyBot.captLigneDroiteExt.read() * 3.3;
        goofyBot.gIntVal = goofyBot.captLigneGaucheInt.read() * 3.3;
        goofyBot.gExtVal = goofyBot.captLigneGaucheExt.read() * 3.3;

        switch(etat) {
            case 1:
                if (goofyBot.jackVal == 1) {
                    etat = 2;
                }
                break;
            
            case 2:
                if(goofyBot.dIntVal <= 0.5 && goofyBot.dExtVal <= 0.5 && goofyBot.gIntVal <= 0.5 && goofyBot.gExtVal <= 0.5) {
                    etat = 4;
                }
                break;
        }

        switch(etat) {
            case 2 :
                fuckmypussy(goofyBot);
                goofyBot.move(70,70);
                break;

            case 4 :
                wait_us(25000);
                goofyBot.move(0,0);
                break;
        }
    }
}