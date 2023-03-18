#ifndef CARRE_HPP
#define CARRE_HPP

#include <robot.hpp>
#include <ihm.hpp>

/** Programme carré qui permet au robot de réaliser un carré de la longueur choisie
 *  au préalable par l'utilisateur grâce au panneau IHM.
 * 
 *  @note Pour savoir comment utiliser le panneau IHM, voir la documentation de la librairie IHM.
 *
 *  @param goofyBot 
 *  L'objet Robot qui contient les informations sur le robot et les capteurs
 */
void carre(Robot& goofyBot);

#endif