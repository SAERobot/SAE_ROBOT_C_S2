#include <mbed.h>
#include <robot.hpp>

#include <suivi.hpp>
#include <labyrinthe.hpp>
#include <balise.hpp>
#include <bluetooth.hpp>

#include <audio.hpp>

Timer tim;

void ihmBoot(Robot &goofyBot) {
  int etat = 0;
  int oldBp = 1;
  float valeur;
  char tab[17];
  tim.reset();
  tim.start();
  while (true) {
    switch (etat) {
        case 0: // bootup
          if (tim.read() > 2.0) {
            volume(goofyBot, 15);
            tim.stop();
            tim.reset();
            tim.start();
            goofyBot.LCD.clear();
            change(goofyBot, 9);
            etat = 1;
          }
          break;

        case 1: // debug mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);
            etat += 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            goofyBot.debugMode();
          }
          break;

        case 2: // black linefollow mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);              
            etat += 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            suivi(goofyBot, 1, 0);
          }
          break;

        case 3: // white linefollow mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);
            etat += 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            suivi(goofyBot, 0, 0);
          }
          break;

        case 4: // robot linefollow mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);
            etat += 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            suivi(goofyBot, 1, 1);
          }
          break;

        case 5: // labyrinthe mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);
            etat += 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            labyrinthe(goofyBot);
          }
          break;

        case 6: // balise mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);
            etat += 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            balise(goofyBot);
          }
          break;

        case 7: // bluetooth mode
          if (goofyBot.bp.read() == 0 && oldBp != goofyBot.bp.read()) {
            change(goofyBot, 12);
            etat = 1;
            oldBp = 1;
            goofyBot.LCD.clear();
            tim.reset();
            tim.start();
          }
          if (tim.read() > 3.0) {
            tim.stop();
            sprintf(tab, "[X]");
            goofyBot.LCD.locate(13, 1);
            goofyBot.LCD.print(tab);
            bluetooth(goofyBot);
          }
          break;
    }

    switch (etat) { // maj sorties
        case 0:
          goofyBot.LCD.clear();
          goofyBot.LCD.setRGB(255, 255, 255);
          sprintf(tab, "goofyBOT OS");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
    
          sprintf(tab, "Loading ...");
          goofyBot.LCD.locate(0, 1);
          goofyBot.LCD.print(tab);
          break;
    
        case 1:
          goofyBot.LCD.setRGB(128, 0, 0);
          sprintf(tab, "> Debug Mode");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
    
          valeur = goofyBot.mesureBatterie.read();
          valeur = valeur * 3.3 * ((12.0 + 47.0) / 12.0) + 0.6;
          sprintf(tab, "Bat. : %.2f V", valeur);
          goofyBot.LCD.locate(0, 1);
          goofyBot.LCD.print(tab);
          break;
    
        case 2:
          goofyBot.LCD.setRGB(255, 64, 0);
          sprintf(tab, "> LineFollow");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
    
          sprintf(tab, "BLACK");
          goofyBot.LCD.locate(0, 1);
          goofyBot.LCD.print(tab);
          break;
    
        case 3:
          goofyBot.LCD.setRGB(255, 255, 0);
          sprintf(tab, "> LineFollow");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
    
          sprintf(tab, "WHITE");
          goofyBot.LCD.locate(0, 1);
          goofyBot.LCD.print(tab);
          break;
    
        case 4:
          goofyBot.LCD.setRGB(0, 255, 0);
          sprintf(tab, "> LineFollow");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
    
          sprintf(tab, "ROBOT");
          goofyBot.LCD.locate(0, 1);
          goofyBot.LCD.print(tab);
          break;
    
        case 5:
          goofyBot.LCD.setRGB(0, 0, 255);
          sprintf(tab, "> Labyrinthe");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
          break;
    
        case 6:
          goofyBot.LCD.setRGB(0, 255, 255);
          sprintf(tab, "> Balise");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
          break;
    
        case 7:
          goofyBot.LCD.setRGB(255, 0, 255);
          sprintf(tab, "> Bluetooth");
          goofyBot.LCD.locate(0, 0);
          goofyBot.LCD.print(tab);
          break;
    }

    wait_us(500000);
  }
}