#ifndef IHM_HPP
#define IHM_HPP

#include <robot.hpp>

/** Permet de sélectionner le programme à lancer par le robot en appuyant sur les boutons
 *  du panneau IHM.
 *
 *  @param goofyBot 
 *  L'objet Robot qui contient les informations sur le robot et les capteurs
 */
void ihmBoot(Robot& goofyBot);

#endif