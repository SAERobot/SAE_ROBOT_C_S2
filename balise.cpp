#include <mbed.h>
#include <robot.hpp>

void balise(Robot &goofyBot) {
  int isFound;
  while (true) {
    isFound = goofyBot.ir.read();
    /*
    if (goofyBot.captDroit.read() < 30) {
        isFound = 2;
        goofyBot.move(-20, 20);
    }
    if (goofyBot.captGauche.read() < 30) {
        isFound = 2;
        goofyBot.move(20, -20);
    }
    */

    switch (isFound) {
    case 0: // pas de balise trouvée
      goofyBot.move(-30, 30);
      break;

    case 1: // balise trouvée
      goofyBot.move(32, 30);
      break;

    case 2: // gonnabuss mode !!!
      break;
    }
    wait_us(50000);
  }
}