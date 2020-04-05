/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.cpp
 Auteur(s)   : Oliveira da Costa Dany, Pozniakoff Lev, Vallon Axel
 Date        : 10.04.2020
 But         : -

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTIONIMPL_H
#define FRACTIONIMPL_H

#include "fraction.h"

template<typename T>
Fraction<T>::operator float() const {
   return numerateur / (float)denominateur;
}

template<typename T>
Fraction<T>::operator double() const {
   return numerateur / (double)denominateur;
}

/**
 * Détermine le plus grand diviseur commun de deux entiers a et b
 */
 template<typename T>
T plusGrandDiviseurCommun(T a, T b) {
   if (!b)
      return a;
   return plusGrandDiviseurCommun(b, a % b);
}

template<typename T>
Fraction<T> Fraction<T>::simplifier() const {
   T gdc = plusGrandDiviseurCommun(numerateur, denominateur);
   return Fraction<T>(numerateur / gdc, denominateur / gdc);
}

template<typename T>
bool Fraction<T>::identite(const Fraction<T> &f) const {
   return numerateur == f.numerateur && denominateur == f.denominateur;
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T> &rhs) const {
   return (float)*this == (float)rhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator+=(const Fraction<T> &rhs) {
   // Attention aux débordements !
   // 1. Essayer d'additionner les deux membres
   // 2. Si débordement, essayer de simplifier le membre de droite
   // 3. Si après simplification, toujours débordement => exception
   // 12 / 5 += 12 / 4 => pgdc(5, 4) : 1
   // 12 / 8 += 12 / 4 => pgdc(8, 4) : 4 => 4 * 8/4

   // Les deux dénominateurs sont identiques, on peut facilement effectuer
   // l'addition
   if(denominateur == rhs.denominateur) {
      // TODO : débordement
      numerateur += rhs.numerateur;
      return *this;
   // Les dénominateur sont multiples l'un de l'autre, on peut ajuster un pour
   // ensuite additionner l'autre
   } else if(plusGrandDiviseurCommun(denominateur, rhs.denominateur) != 1) {
      // multiplier celui qui a le plus petit denominateur
      if(denominateur == std::min(denominateur, rhs.denominateur)) {
         T facteur = rhs.denominateur / denominateur;
         numerateur *= facteur;
         denominateur *= facteur;
         numerateur += rhs.numerateur;
      } else {
         T facteur = denominateur / rhs.denominateur;
         numerateur += rhs.numerateur * facteur;
      }
   // Les dénominateurs ne sont pas multiples l'un de l'autre, il faut ajuster
   // les deux membres
   } else {
      numerateur *= rhs.denominateur;
      numerateur += rhs.numerateur * denominateur;
      denominateur *= rhs.denominateur;
   }
   return *this;
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const Fraction<T>& rhs) {
   os << rhs.numerateur << " / " << rhs.denominateur;
   return os;
}



#endif
