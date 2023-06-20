#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <mbed.h>
#include <SRF05.h>
#include <Grove_LCD_RGB_Backlight.h>

#define WAITING_MODE 0
#define DEBUG_MODE 1
#define CONFETTIS_MODE 2
#define LINE_FOLLOWING_MODE 3
#define SQUARE_MODE 4

class Robot {

public:
    Robot();
    int mode;

    SRF05 captGauche;
    SRF05 captDroit;
    Grove_LCD_RGB_Backlight LCD;
    DigitalIn ir;
    DigitalIn bp;

    DigitalIn jack;
    DigitalIn finCourse;
    AnalogIn mesureBatterie;
    AnalogIn captLigneDroiteInt;
    AnalogIn captLigneDroiteExt;
    AnalogIn captLigneGaucheInt;
    AnalogIn captLigneGaucheExt;

    PwmOut moteurDroit;
    PwmOut moteurGauche;
    DigitalOut moteurDroitSens;
    DigitalOut moteurGaucheSens;

    InterruptIn A_mot2;
    DigitalIn B_mot2;
    InterruptIn A_mot1;
    DigitalIn B_mot1;

    Serial com;

    int jackVal;
    int fcVal;
    double mbVal;
    double dIntVal;
    double dExtVal;
    double gIntVal;
    double gExtVal;

    /** Fonction de debug du robot
     *  Affiche les valeurs des capteurs sur le port série.
     * 
     *  @note Teste les capteurs de ligne, de fin de course, de batterie et le jack et 
     *  démarre en même temps le mode débug de l'IHM.
     * 
     *  @warning Le robot doit être connecté à un ordinateur pour afficher les valeurs sur le port série.
     */
    void debugMode();

    /** Déplace le robot en fonction des PWMs des moteurs gauche et droit et des sens des moteurs
     *
     *  @param pwmGauche Valeur du PWM du moteur gauche entre -100 et 100 (reverse et forward)
     *  @param pwmDroit Valeur du PWM du moteur droit entre -100 et 100 (reverse et forward)
     */
    void move(float pwmGauche, float pwmDroit);
};

#endif