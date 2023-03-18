#ifndef IHM_HPP
#define IHM_HPP

#include <robot.hpp>

/** Permet de lancer le mode Debug de la carte IHM. Ce mode permet de tester les boutons et les LEDs
 *  du panneau IHM. En appuyant sur un bouton, la LED correspondante s'allume.
 *
 *  @param goofyBot 
 *  L'objet Robot qui contient les informations sur le robot et les capteurs
 */
void ihmDebug(Robot& goofyBot);

/** Permet de sélectionner le programme à lancer par le robot en appuyant sur les boutons
 *  du panneau IHM. Il faut appuyer sur le bouton 1 pour lancer le programme Confettis, sur le
 *  bouton 2 pour lancer le programme Suiveur de Ligne, sur le bouton 3 pour lancer le programme
 *  Carré et sur le bouton 4 pour lancer le mode Debug.  
 *
 *  @param goofyBot 
 *  L'objet Robot qui contient les informations sur le robot et les capteurs
 */
void ihmBoot(Robot& goofyBot);

/** Permet de sélectionner la longueur du carré à réaliser par le robot
 *
 *  @returns
 *  La longueur du carré à réaliser par le robot entre 60 et 200 cm    
 *
 *  @param goofyBot 
 *  L'objet Robot qui contient les informations sur le robot et les capteurs
 */
int ihmSel(Robot& goofyBot);

/** Juste un petit effet de boot pour l'IHM
 *
 *  @param goofyBot 
 *  L'objet Robot qui contient les informations sur le robot et les capteurs
 */
void ihmBruh(Robot& goofyBot);

#endif