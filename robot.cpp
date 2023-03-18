#include <robot.hpp>

#define T 0.001

// Constructeur
Robot::Robot() :
    jack(PTE20),
    finCourse(PTE21),
    mesureBatterie(A0),
    captLigneDroiteInt(A1),
    captLigneDroiteExt(A2),
    captLigneGaucheInt(A4),
    captLigneGaucheExt(A3),

    IHM_Led1(D15),
    IHM_Led2(D14),
    IHM_Led3(D13),
    IHM_Led4(D12),
    IHM_Btn1(D4),
    IHM_Btn2(D5),
    IHM_Btn3(A5),
    IHM_Btn4(PTE30),

    moteurDroit(D6),
    moteurGauche(D8),
    moteurDroitSens(D7),
    moteurGaucheSens(D9),

    bluetooth(PTE22, PTE23)
{
    mode = WAITING_MODE;
}

void Robot::debugMode() {
    // Debug mode - Affichage des valeurs des capteurs
    int choix, fdc;
    char rxCommand, oldRX;
    float valeur, valeur2, valeur3, valeur4;
    float droite, gauche;
    droite = gauche = 0.0;
    choix = 0;
    while (1) {
        fdc = finCourse.read();
        switch(choix) {
            case 0:
                break;

            case 1:
                if(fdc == 0)
                    choix = 7;
                break;
            
            case 2:
                break;

            case 3:
                if(fdc == 0)
                    choix = 7;
                break;
            
            case 4:
                if(fdc == 0)
                    choix = 7;
                break;

            case 5:
                if(fdc == 0)
                    choix = 7;
                break;
            
            case 6:
                if(fdc == 0)
                    choix = 7;
                break;
                
            case 7:
                break;

            case 8:
                scanf("%f", &droite);
                scanf("%f", &gauche);
                if(fdc == 0)
                    choix = 7;
                break;

            case 9:
                printf("Bluetooth prêt, envoyez commande.");
                if(fdc == 0)
                    choix = 7;
                if(rxCommand != oldRX) {
                    choix = 10;
                }
                break;

            case 10:
                if(fdc == 0)
                    choix = 7;
                choix = 9;
                break;

        }

        switch(choix) {
            case 0: // menu
                printf("Bienvenu sur le programme Debug, veuillez choisir un mode. \n\r1 - Jack \n\r2 - Fin de course \n\r3 - Mesure batterie \n\r4 - Capteurs \n\r5 - Moteur avant \n\r6 - Moteur arriere \n\r8 - Custom moteur \n\r9 - Bluetooth");
                scanf("%d", &choix);
                break;

            case 1: // afficher jack
                valeur = jack.read();
                printf("%.0f \n\r", valeur);
                wait_us(500000);
                break;
            
            case 2: // afficher fdc
                valeur = finCourse.read();
                printf("%.0f \n\r", valeur);
                wait_us(500000);
                break;

            case 3: // afficher batterie
                valeur = mesureBatterie.read();
                valeur = valeur * 3.3 * ((12.0 + 47.0) / 12.0) + 0.6;
                printf("%.2f \n\r", valeur);
                wait_us(500000);
                break;
            
            case 4: // afficher 4 capteurs
                valeur = captLigneDroiteInt.read()*3.3;
                valeur2 = captLigneDroiteExt.read()*3.3;
                valeur3 = captLigneGaucheInt.read()*3.3;
                valeur4 = captLigneGaucheExt.read()*3.3;
                printf("%.2f | %.2f | %.2f | %.2f \n\r", valeur, valeur2, valeur3, valeur4);
                wait_us(500000);
                break;

            case 5: // avancer mot avant
                move(50, 50);
                wait_us(3000000);
                move(0, 0);
                wait_us(3000000);
                move(99, 99);
                wait_us(3000000);
                move(0, 0);
                wait_us(3000000);
                break;
            
            case 6: // avancer mot arrière
                move(-50, -50);
                wait_us(3000000);
                move(0, 0);
                wait_us(3000000);
                move(-99, -99);
                wait_us(3000000);
                move(0, 0);
                wait_us(3000000);
                break;

            case 7: // annuler et retour accueil
                move(0, 0);
                choix = 0;
                break;

            case 8:
                move(droite, gauche);
                break;

            case 9:
                rxCommand = bluetooth.getc();
                break;

            case 10:
                oldRX = rxCommand;
                move((int)rxCommand, (int)rxCommand);
                choix = 9;
                break;
        }
    }
}

void Robot::move(float pwmGauche, float pwmDroit) {
    moteurDroit.period(T);
    moteurGauche.period(T);

    if(pwmGauche >= -100.0 && pwmGauche < 0) {
        moteurGaucheSens = 0;
        pwmGauche = pwmGauche * -1.0;
        pwmGauche = pwmGauche / 100.0; // On divise par 100 pour avoir un pwm entre 0 et 1
    } else if (pwmGauche <= 100 && pwmGauche > 0) {
        moteurGaucheSens = 1;
        pwmGauche -= 100.0;
        pwmGauche = pwmGauche * -1.0;
        pwmGauche = pwmGauche / 100.0;
    } else if (pwmGauche == 0) {
        moteurGaucheSens = 1;
        pwmGauche = 1;
    }

    if(pwmDroit >= -100.0 && pwmDroit < 0) {
        moteurDroitSens = 0;
        pwmDroit = pwmDroit * -1.0;
        pwmDroit = pwmDroit / 100.0; // On divise par 100 pour avoir un pwm entre 0 et 1
    } else if (pwmDroit <= 100 && pwmDroit > 0) {
        moteurDroitSens = 1;
        pwmDroit = pwmDroit - 100.0;
        pwmDroit = pwmDroit * -1.0;
        pwmDroit = pwmDroit / 100.0; // On divise par 100 pour avoir un pwm entre 0 et 1
    } else if (pwmDroit == 0) {
        moteurDroitSens = 1;
        pwmDroit = 1;
    }

    moteurDroit.pulsewidth(T * pwmDroit);
    moteurGauche.pulsewidth(T * pwmGauche);
}  