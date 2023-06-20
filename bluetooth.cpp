#include <mbed.h>
#include <robot.hpp>

void bluetooth(Robot &goofyBot) {
  char cmd = 0;
  int fdc;
  char tab[17];
  goofyBot.com.baud(9600);
  while (true) {

    if (goofyBot.com.readable()) {
      sprintf(tab, "--- CONNECTE ---");
      goofyBot.LCD.locate(0, 1);
      goofyBot.LCD.print(tab);
    }

    if (goofyBot.com.readable()) {
      printf("Waiting command \n\r");
      cmd = goofyBot.com.getc();
    }

    if (cmd == 'a') {
      printf("%c", cmd);
    }

    if (cmd == 'b') {
      goofyBot.move(30, 30);
      cmd = 0;
    }

    if (cmd == 'c') { // back
      goofyBot.move(-30, -30);
      cmd = 0;
    }

    if (cmd == 'd') { // virage gauche
      for (float speed = 25; speed < 90; speed += 5) {
        goofyBot.move(speed, -70);
        wait_us(20000);
      }
      for (float speed = 100; speed > 90; speed -= 5) {
        goofyBot.move(speed, -70);
        wait_us(20000);
      }
      goofyBot.move(0, 0);
      cmd = 0;
    }

    if (cmd == 'e') { // virage droite
      for (float speed = 25; speed < 90; speed += 5) {
        goofyBot.move(-70, speed);
        wait_us(20000);
      }
      for (float speed = 100; speed > 90; speed -= 5) {
        goofyBot.move(-70, speed);
        wait_us(20000);
      }
      goofyBot.move(0, 0);
      cmd = 0;
    }

    if (cmd == 'f') { // stop
      goofyBot.move(0, 0);
      cmd = 0;
    }
  }
}