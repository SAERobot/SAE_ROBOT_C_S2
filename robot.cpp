#include <robot.hpp>

#define T 0.001

/*
// Initialisation des variables du moteur de gauche
int cptg = 0;
// Initialisation des variables du moteur de droite
int cptd = 90;

void encode2A() {cptg++;}
void encode1A() {cptd++;}
*/


// Constructeur
Robot::Robot() :
    jack(PTE20),
    finCourse(PTE21),
    mesureBatterie(A0),
    captLigneDroiteInt(A1),
    captLigneDroiteExt(A2),
    captLigneGaucheInt(A4),
    captLigneGaucheExt(A3),

    captGauche(D12, D13),
    captDroit(D5, D4),
    LCD(D14, D15),
    ir(PTE30),
    bp(A5),

    moteurDroit(D6),
    moteurGauche(D8),
    moteurDroitSens(D7),
    moteurGaucheSens(D9),

    A_mot2(D11),
    B_mot2(D10),
    A_mot1(D2),
    B_mot1(D3),

    com(PTE22, PTE23)
{
    mode = WAITING_MODE;
}

void Robot::debugMode() {
    // Debug mode - Affichage des valeurs des capteurs
    int choix, fdc;
    float valeur, valeur2, valeur3, valeur4, error;
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
        }

        switch(choix) {
            case 0: // menu
                printf("Bienvenu sur le programme Debug, veuillez choisir un mode. \n\r1 - Jack \n\r2 - Fin de course \n\r3 - Mesure batterie \n\r4 - Capteurs \n\r5 - Moteur avant \n\r6 - Moteur arriere \n\r8 - Custom moteur \n\r");
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
                valeur = (1-captLigneDroiteInt.read());
                valeur2 = (1-captLigneDroiteExt.read());
                valeur3 = (1-captLigneGaucheInt.read());
                valeur4 = (1-captLigneGaucheExt.read());
                error = (valeur3 - valeur); 
                printf("%.2f | %.2f | %.2f | %.2f | %.2f \n\r", valeur4, valeur3, valeur, valeur2, error);
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
        }
    }
}

/*
void Robot::movePID(float pwmGauche, float pwmDroit) {
    int SPEED = 30;
    int KP = 45;
    int KD = 55;

    A_mot1.rise(&encode1A);
    A_mot2.rise(&encode2A);
    moteurDroit.period(T);
    moteurGauche.period(T);
    float tordroite, torgauche;
    int e, last_error, derivative;
    float pid = 0.0;
    last_error = 1;
    tordroite = 0;
    torgauche = 0;

    tordroite = (float)cptd / 87.0;
    torgauche = (float)cptg / 55.0;
    e = (tordroite - torgauche);
    derivative = e - last_error;
    last_error = e;
    pid = (KP * e) + (KD * derivative);
    move(SPEED + pid + 1, SPEED - pid);
}
*/

void Robot::move(float pwmGauche, float pwmDroit) {

    if(pwmGauche >= 100) 
        pwmGauche = 100;

    if(pwmDroit >= 100)
        pwmDroit = 100;

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