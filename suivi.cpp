#include <mbed.h>
#include <robot.hpp>
#include <ihm.hpp>
#include <time.h>

#define SPEED 75
#define KP 35
#define KD 60

void suivi(Robot& goofyBot) {

    int etat = 0;
    float error = 0;
    float last_error = 0;
    float integral = 0;
    float derivative = 0;
    float PID_value, e, errorD, errorG;

    while(true) {
        goofyBot.jackVal = goofyBot.jack.read();
        goofyBot.fcVal = goofyBot.finCourse.read();
        goofyBot.dIntVal = goofyBot.captLigneDroiteInt.read();
        goofyBot.dExtVal = goofyBot.captLigneDroiteExt.read()*3.3;
        goofyBot.gIntVal = goofyBot.captLigneGaucheInt.read();
        goofyBot.gExtVal = goofyBot.captLigneGaucheExt.read()*3.3;
    
        e = ((goofyBot.gIntVal*3.3) - (goofyBot.dIntVal*3.3));

        error = (goofyBot.gIntVal - goofyBot.dIntVal);

        errorD = (goofyBot.dExtVal - goofyBot.gIntVal);
        errorG = (goofyBot.gExtVal - goofyBot.dIntVal);

        derivative = error - last_error;
        last_error = error;
        PID_value = (KP*error) + (KD*derivative);
        
        if(goofyBot.fcVal == 0) {
            etat = 69;
        }

        switch(etat) {
            case 0:
                if(goofyBot.jackVal == 1) {
                    etat = 1; //suivi
                } 
                break;
            
            case 1:
                if(e <= -0.05 || e <= 0.05) {
                    etat = 2;
                }
                break;

            case 2:
                if(goofyBot.dExtVal <= 1 || goofyBot.gExtVal < 1) { //case extreme
                    etat = 3;
                }
                break;
                if (e <= 0.15 && e >= -0.15) {
                    etat = 1;
                }
                break;

            case 3: 
                if (e <= 0.02 && e >= -0.02) {
                    etat = 1;
                }
                break;
                if(e <= -0.10 || e >= 0.10) {
                    etat = 2;
                }
                break;
        }

        switch(etat) {
            case 0:
                if(e <= 0.03 && e >= -0.03) {
                    goofyBot.IHM_Led3.write(1);    
                } else {
                    goofyBot.IHM_Led3.write(0);
                }
                goofyBot.move(0,0);
                break;

            case 1:
                goofyBot.move(50,50);
                break;

            case 2:
                goofyBot.move(SPEED + PID_value, SPEED - PID_value);
                break;

            case 3:
                if(goofyBot.dExtVal < 0.7 || e >= 0.85) {
                    PID_value = (KP*errorD) + (KD*derivative);
                    goofyBot.move(SPEED + 10 + PID_value,0);
                }
                if(goofyBot.gExtVal < 0.7 || e >= 0.85) {
                    PID_value = (KP*errorG) + (KD*derivative);
                    goofyBot.move(0, SPEED + 10 + PID_value);
                }
                break;

            case 69: 
                goofyBot.move(0,0);
                break;
            }
        wait_us(2500);
    }
}