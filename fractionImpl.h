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
#include <stdexcept>

#include "fraction.h"

template<typename T>
Fraction<T>::Fraction(T n, T d) try : numerateur(n), denominateur(d) {
   if(d < 0)
      throw std::invalid_argument("Le denominateur ne peut pas etre negatif");
   if(d == 0)
      throw std::invalid_argument("Le denominateur ne peut pas etre nul");
} catch (std::invalid_argument&) { }

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

template<typename T>
Fraction<T> Fraction<T>::simplifier() const {
   T pgdc = plusGrandDiviseurCommun((T)abs(numerateur), denominateur);
   return Fraction<T>(numerateur / pgdc, denominateur / pgdc);
}

template<typename T>
bool Fraction<T>::identite(const Fraction<T> &f) const {
   return numerateur == f.numerateur && denominateur == f.denominateur;
}

template<typename T>
bool operator == (const Fraction<T>& lhs, const Fraction<T>& rhs) {
   return (float)lhs == (float)rhs;
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
Fraction<T> operator + (Fraction<T> lhs, const Fraction<T>& rhs) {
   lhs += rhs;
   return lhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator+=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();
   // Les dénominateur sont multiples l'un de l'autre mais pas égaux, on peut
   // ajuster un pour ensuite additionner l'autre
   if(plusGrandDiviseurCommun(tmpMembreDroite.denominateur, tmpMembreGauche
   .denominateur) != 1 && tmpMembreDroite.denominateur != tmpMembreGauche
   .denominateur) {
      // le plus petit dénominateur est le membre de gauche
      if(tmpMembreGauche.denominateur  == std::min(tmpMembreGauche.denominateur,
            tmpMembreDroite.denominateur)) {
         T facteur = tmpMembreDroite.denominateur / tmpMembreGauche.denominateur;
         if(debordementMultiplication(tmpMembreGauche.numerateur, facteur))
            throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                    "numerateur de l'operande de gauche");
         if(debordementMultiplication(tmpMembreGauche.denominateur, facteur))
            throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                    "denominateur de l'operande de gauche");
         tmpMembreGauche.numerateur *= facteur;
         tmpMembreGauche.denominateur *= facteur;
      // le plus petit dénominateur est le membre de droite
      } else {
         T facteur = tmpMembreGauche.denominateur / tmpMembreDroite.denominateur;
         if(debordementMultiplication(tmpMembreDroite.numerateur, facteur))
            throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                    "numerateur de l'operande de droite");
         if(debordementMultiplication(tmpMembreDroite.denominateur, facteur))
            throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                    "denominateur de l'operande de droite");
         tmpMembreDroite.numerateur *= facteur;
         tmpMembreDroite.denominateur *= facteur;
      }
   // Les dénominateurs ne sont pas multiples l'un de l'autre, il faut ajuster
   // les deux membres
   } else if (tmpMembreDroite.denominateur != tmpMembreGauche.denominateur){
      if(debordementMultiplication(tmpMembreGauche.numerateur, tmpMembreDroite.denominateur))
         throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                 "numerateur de l'operande de gauche");
      if(debordementMultiplication(tmpMembreDroite.numerateur, tmpMembreGauche.denominateur))
         throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                 "numerateur de l'operande de droite");
      if(debordementMultiplication(tmpMembreGauche.denominateur, tmpMembreDroite.denominateur))
         throw std::overflow_error("Il y a debordement lors de l'ajustement du "
                                 "denominateur");
      tmpMembreGauche.numerateur *= tmpMembreDroite.denominateur;
      tmpMembreDroite.numerateur *= tmpMembreGauche.denominateur;
      tmpMembreGauche.denominateur *= tmpMembreDroite.denominateur;
      tmpMembreDroite.denominateur = tmpMembreGauche.denominateur;
   }
   if(debordementAddition(tmpMembreGauche.numerateur, tmpMembreDroite.numerateur))
      throw std::overflow_error("Il y a debordement lors de l'addition des "
                              "numerateurs");
   *this = { T(tmpMembreGauche.numerateur + tmpMembreDroite.numerateur),
            tmpMembreDroite.denominateur };
   return *this = simplifier();
}

template<typename T>
Fraction<T> operator * (Fraction<T> lhs, const Fraction<T>& rhs) {
   lhs *= rhs;
   return lhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator*=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();

   T diagonaleGauche = plusGrandDiviseurCommun((T)abs(tmpMembreGauche.numerateur),
         tmpMembreDroite.denominateur);
   tmpMembreGauche.numerateur /= diagonaleGauche;
   tmpMembreDroite.denominateur /= diagonaleGauche;
   T diagonaleDroite = plusGrandDiviseurCommun(tmpMembreGauche.denominateur,
                                               (T)abs(tmpMembreDroite.numerateur));
   tmpMembreGauche.denominateur /= diagonaleDroite;
   tmpMembreDroite.numerateur /= diagonaleDroite;

   if(debordementMultiplication(tmpMembreGauche.numerateur, tmpMembreDroite.numerateur))
      throw std::out_of_range("Il y a debordement lors de la multiplication des "
                              "numerateurs");
   if(debordementMultiplication(tmpMembreGauche.denominateur, tmpMembreDroite.denominateur))
      throw std::out_of_range("Il y a debordement lors de la multiplication des "
                              "denominateurs");
   tmpMembreGauche.numerateur *= tmpMembreDroite.numerateur;
   tmpMembreGauche.denominateur *= tmpMembreDroite.denominateur;
   *this = tmpMembreGauche;
   return *this;
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const Fraction<T>& rhs) {
   os << (long long)rhs.numerateur << " / " << (long long)rhs.denominateur;
   return os;
}


#endif
