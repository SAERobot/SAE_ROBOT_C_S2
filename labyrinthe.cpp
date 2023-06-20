#include <audio.hpp>
#include <mbed.h>
#include <robot.hpp>

void labyrinthe(Robot &goofyBot) {
  goofyBot.move(0, 0);
  int d1, d3, blanc, balise, etat;
  float temp;
  etat = 0;

  while (true) {
    d1 = goofyBot.captDroit.read();
    d3 = goofyBot.captGauche.read();

    temp = ((1 - goofyBot.captLigneGaucheInt.read()) +
            (1 - goofyBot.captLigneDroiteInt.read())) /
           2;

    if (temp > 0.5) {
      blanc = 0;
    } else {
      blanc = 1;
    }

    balise = goofyBot.ir.read();

    if (goofyBot.finCourse.read() == 0) {
      change(goofyBot, 2);
      goofyBot.move(0, 0);
      break;
    }

    switch (etat) {
    case 0:
      if (balise == 0)
        etat = 10;
      else if (balise > 0)
        etat = 10;
      break;
    case 10:
      if (blanc == 1)
        etat = 4;
      else if (d1 < 10)
        etat = 20;
      else if (d3 > 30)
        etat = 30;
      break;
    case 20:
      if (d1 >= 15)
        etat = 10;
      else
        etat = 0;
      break;
    case 30:
      if (d1 >= 15)
        etat = 10;
      else
        etat = 0;
      break;
    }

    switch (etat) {
    case 0:
      goofyBot.move(0, 0);
      break;

    case 10:
      goofyBot.move(32, 28);
      break;

    case 20:
      wait_us(1000000);
      goofyBot.move(0, 0);
      wait_us(45000);
      // augmentation et diminution progressive de la vitesse
      for (float speed = 25; speed < 90; speed += 5) {
        goofyBot.move(speed, -70);
        wait_us(20000);
      }
      for (float speed = 100; speed > 90; speed -= 5) {
        goofyBot.move(speed, -70);
        wait_us(20000);
      }
      goofyBot.move(0, 0);
      wait_us(1000000);
      break;

    case 30:
      wait_us(1000000);
      goofyBot.move(0, 0);
      wait_us(45000);
      // augmentation et diminution progressive de la vitesse
      for (float speed = 25; speed < 90; speed += 5) {
        goofyBot.move(-70, speed);
        wait_us(20000);
      }
      for (float speed = 100; speed > 90; speed -= 5) {
        goofyBot.move(-70, speed);
        wait_us(20000);
      }
      goofyBot.move(0, 0);
      wait_us(1000000);
      break;

    case 4:
      goofyBot.move(50, 50);
      wait_us(20000);
      goofyBot.move(50, 50);
      wait_us(20000);
      goofyBot.move(0, 0);
      break;
    }
  }
}