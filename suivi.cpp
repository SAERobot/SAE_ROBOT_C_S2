#include <mbed.h>
#include <robot.hpp>

#include <audio.hpp>

#define SPEED 30
#define KP 45
#define KD 60

Timer t;

void suivi(Robot &goofyBot, int couleur, int follow) {
  int etat = 0;
  float error = 0.0;
  float last_error = 0.0;
  float integral = 0.0;
  float derivative = 0.0;
  float PID_value, e, errorD, errorG;
  char tab[17];

  while (true) {
    goofyBot.jackVal = goofyBot.jack.read();
    goofyBot.fcVal = goofyBot.finCourse.read();

    if (couleur == 1) { // ligne noire sur fond blanc
      goofyBot.dIntVal = 1 - goofyBot.captLigneDroiteInt.read();
      goofyBot.dExtVal = 1 - goofyBot.captLigneDroiteExt.read();
      goofyBot.gIntVal = 1 - goofyBot.captLigneGaucheInt.read();
      goofyBot.gExtVal = 1 - goofyBot.captLigneGaucheExt.read();
    } else { // ligne blanche sur fond noir
      goofyBot.dIntVal = goofyBot.captLigneDroiteInt.read();
      goofyBot.dExtVal = goofyBot.captLigneDroiteExt.read();
      goofyBot.gIntVal = goofyBot.captLigneGaucheInt.read();
      goofyBot.gExtVal = goofyBot.captLigneGaucheExt.read();
    }

    e = (goofyBot.gIntVal - goofyBot.dIntVal);

    error = (goofyBot.gIntVal - goofyBot.dIntVal);

    errorD = (goofyBot.dExtVal - goofyBot.gIntVal);
    errorG = (goofyBot.gExtVal - goofyBot.dIntVal);

    derivative = error - last_error;
    last_error = error;
    PID_value = (KP * error) + (KD * derivative);

    if (goofyBot.fcVal == 0) {
      etat = 69;
    }

    if (follow == 1) {
        if (goofyBot.captDroit.read() < 30) {
            change(goofyBot, 6);
            goofyBot.move(0, 0);
        }
    }

    switch (etat) {
    case 0:
      if (goofyBot.jackVal == 1) {
          if(couleur == 1) {
              change(goofyBot, 10);
          }
          if (couleur == 0) {
              change(goofyBot, 1);
          }
        etat = 1; // suivi
      }
      break;

    case 1:
      if (goofyBot.fcVal == 0) {
        etat = 69;
      }
      break;

    case 69:
      break;
    }

    switch (etat) {
    case 0:
      if (e <= 0.1 && e >= -0.1) {
        sprintf(tab, "-? ? LIGNE ? ?- ");
        goofyBot.LCD.locate(0, 1);
        goofyBot.LCD.print(tab);
      } else {
        sprintf(tab, "-LIGNE DETECTEE-");
        goofyBot.LCD.locate(0, 1);
        goofyBot.LCD.print(tab);
      }
      goofyBot.move(0, 0);
      break;

    case 1:
      goofyBot.move(SPEED + PID_value, SPEED - PID_value);
      break;

    case 69:
      goofyBot.move(0, 0);
        t.start();
      if (t.read() < 0.5) {
          change(goofyBot, 4);
        goofyBot.move(-30, -30);
      } else {
        goofyBot.move(0, 0);
        t.stop();
      }
      break;
    }
  }
}