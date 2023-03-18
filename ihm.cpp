#include <mbed.h>
#include <robot.hpp>

#include <confettis.hpp>
#include <carre.hpp>
#include <suivi.hpp>

void ihmDebug(Robot& goofyBot) {
    while(true) {
        if(goofyBot.IHM_Btn1.read() == 0) {
            goofyBot.IHM_Led1.write(1);
        }
        else {
            goofyBot.IHM_Led1.write(0);
        }
        if(goofyBot.IHM_Btn2.read() == 0) {
            goofyBot.IHM_Led2.write(1);
        }
        else {
            goofyBot.IHM_Led2.write(0);
        }
        if(goofyBot.IHM_Btn3.read() == 0) 
        {
            goofyBot.IHM_Led3.write(1);
        }
        else {
            goofyBot.IHM_Led3.write(0);
        }
        if(goofyBot.IHM_Btn4.read() == 0) {
            goofyBot.IHM_Led4.write(1);
        }
        else {
            goofyBot.IHM_Led4.write(0);
        }
    }
    return;
}

void ihmBoot(Robot& goofyBot) {
    int b1;
    int b2;
    int b3;
    int b4;


    // Petit effet de boot pour l'IHM
    // il faut controler le niveau de la batterie
    for(int i = 0; i < 3; i++) {
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
    }
    goofyBot.IHM_Led1.write(0);
    goofyBot.IHM_Led2.write(0);
    goofyBot.IHM_Led3.write(0);
    goofyBot.IHM_Led4.write(0);

    goofyBot.IHM_Btn1.mode(PullNone);
    goofyBot.IHM_Btn2.mode(PullNone);
    goofyBot.IHM_Btn3.mode(PullNone);
    goofyBot.IHM_Btn4.mode(PullNone);

    // Après démarrage de l'IHM, on attend que le programme soit sélectionné
    while(true) {        
        b1 = goofyBot.IHM_Btn1.read();
        b2 = goofyBot.IHM_Btn2.read();
        b3 = goofyBot.IHM_Btn3.read();
        b4 = goofyBot.IHM_Btn4.read();

        if(b1 == 1) {
            goofyBot.IHM_Led1.write(1);
            confettis(goofyBot);
        }
        else if(b2 == 1) {
            goofyBot.IHM_Led2.write(1);
            suivi(goofyBot);
        }
        else if(b3 == 1) {
            goofyBot.IHM_Led3.write(1);
            carre(goofyBot);
        }
        else if(b4 == 1) {
            goofyBot.IHM_Led4.write(1);
            goofyBot.debugMode();
        }
    }
}

int ihmSel(Robot& goofyBot) {
    // Taille en CM du carré (entre 60 et 200)
    int res = 0;
    while(goofyBot.IHM_Btn4.read() == 0) {
        goofyBot.IHM_Led2.write(0);
        if (goofyBot.IHM_Btn1.read() == 1) {
            // Ajout dizaines
            res += 10;
            wait_us(1000000);
        }
        else if (goofyBot.IHM_Btn2.read() == 1) {
            // Ajout centaines
            res += 100;
            wait_us(1000000);

        }
        else if (goofyBot.IHM_Btn3.read() == 1) {
            // Reset
            res = 0;
            wait_us(1000000);
        }
        
    }
    if(res > 200 || res < 60) {
        res = 0;
        for(int i = 0; i < 5; i++) {
            goofyBot.IHM_Led4.write(0);
            wait_us(100000);
            goofyBot.IHM_Led4.write(1);
            wait_us(100000);
        }
    }

    goofyBot.IHM_Led2.write(1);

    for(int i = 0; i < 5; i++) {
        goofyBot.IHM_Led1.write(0);
        wait_us(500000);
        goofyBot.IHM_Led1.write(1);
        wait_us(500000);
    }

    goofyBot.IHM_Led2.write(0);

    return res;
}