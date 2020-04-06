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

#include <limits>

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
   return plusGrandDiviseurCommun(b, T(a % b));
}

// TODO : ne simplifie pas comme il faut les fractions avec des négatifs
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
bool debordementAddition(T a, T b) {
   T res = a + b;
   if(a > 0 && b > 0 && res < 0)
      return true;
   return a < 0 && b < 0 && res > 0;
}

template<typename T>
bool debordementMultiplication(T a, T b) {
   if (a == 0 || b == 0)
      return false;
   T res = a * b;
   return !(a == res / b);
}

template<typename T>
Fraction<T> Fraction<T>::operator+(const Fraction<T> &rhs) const {
   Fraction<T> tmp = *this;
   return tmp += rhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator+=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();
   // Les deux dénominateurs sont identiques, on peut facilement effectuer
   // l'addition en additionnant leur numérateurs
   if(tmpMembreDroite.denominateur == tmpMembreGauche.denominateur) {
      // Débordement lors de l'addition des numérateurs
      if(debordementAddition(tmpMembreDroite.numerateur, tmpMembreGauche.numerateur))
         throw std::out_of_range("Il y a debordement lors de l'addition des "
                                 "numerateurs");
   } else
   // Les dénominateur sont multiples l'un de l'autre, on peut ajuster un pour
   // ensuite additionner l'autre
   if(plusGrandDiviseurCommun(tmpMembreDroite.denominateur, tmpMembreGauche
   .denominateur) != 1) {
      // le plus petit dénominateur est le membre de gauche
      if(tmpMembreGauche.denominateur  == std::min(tmpMembreGauche.denominateur,
            tmpMembreDroite.denominateur)) {
         T facteur = tmpMembreDroite.denominateur / tmpMembreGauche.denominateur;
         if(debordementMultiplication(tmpMembreGauche.numerateur, facteur))
            throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                    "numerateur de l'operande de gauche");
         tmpMembreGauche.numerateur *= facteur;
         if(debordementMultiplication(tmpMembreGauche.denominateur, facteur))
            throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                    "denominateur de l'operande de gauche");
         tmpMembreGauche.denominateur *= facteur;
      // le plus petit dénominateur est le membre de droite
      } else {
         T facteur = tmpMembreGauche.denominateur / tmpMembreDroite.denominateur;
         if(debordementMultiplication(tmpMembreDroite.numerateur, facteur))
            throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                    "numerateur de l'operande de droite");
         tmpMembreDroite.numerateur *= facteur;
         if(debordementMultiplication(tmpMembreDroite.denominateur, facteur))
            throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                    "denominateur de l'operande de droite");
         tmpMembreDroite.denominateur *= facteur;
      }
   // Les dénominateurs ne sont pas multiples l'un de l'autre, il faut ajuster
   // les deux membres
   } else {
      if(debordementMultiplication(tmpMembreGauche.numerateur, tmpMembreDroite.denominateur))
         throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                 "numerateur de l'operande de gauche");
      tmpMembreGauche.numerateur *= tmpMembreDroite.denominateur;
      if(debordementMultiplication(tmpMembreDroite.numerateur, tmpMembreGauche.denominateur))
         throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                 "numerateur de l'operande de droite");
      tmpMembreDroite.numerateur *= tmpMembreGauche.denominateur;
      if(debordementMultiplication(tmpMembreGauche.denominateur, tmpMembreDroite.denominateur))
         throw std::out_of_range("Il y a debordement lors de l'ajustement du "
                                 "denominateur");
      tmpMembreGauche.denominateur *= tmpMembreDroite.denominateur;
      tmpMembreDroite.denominateur = tmpMembreGauche.denominateur;
   }
   if(debordementAddition(tmpMembreGauche.numerateur, tmpMembreDroite.numerateur))
      throw std::out_of_range("Il y a debordement lors de l'addition des "
                              "numerateurs");
   *this = { T(tmpMembreGauche.numerateur + tmpMembreDroite.numerateur),
            tmpMembreDroite.denominateur };
   return *this = simplifier();
}

template<typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T> &rhs) const {
   Fraction<T> tmp = *this;
   return tmp *= rhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator*=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();

   if(debordementMultiplication(tmpMembreGauche.numerateur, tmpMembreDroite.numerateur))
      throw std::out_of_range("Il y a debordement lors de la multiplication des "
                              "numerateurs");
   tmpMembreGauche.numerateur *= tmpMembreDroite.numerateur;
   if(debordementMultiplication(tmpMembreGauche.denominateur, tmpMembreDroite.denominateur))
      throw std::out_of_range("Il y a debordement lors de la multiplication des "
                              "denominateurs");
   tmpMembreGauche.denominateur *= tmpMembreDroite.denominateur;
   *this = tmpMembreGauche;
   return *this = simplifier();
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const Fraction<T>& rhs) {
   os << (long long)rhs.numerateur << " / " << (long long)rhs.denominateur;
   return os;
}


#endif
