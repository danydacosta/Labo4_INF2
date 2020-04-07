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
   if (d < 0)
      throw std::invalid_argument("Le denominateur ne peut pas etre negatif");
   if (d == 0)
      throw std::invalid_argument("Le denominateur ne peut pas etre nul");
} catch (std::invalid_argument &) {}

template<typename T>
Fraction<T>::operator float() const {
   return numerateur / (float) denominateur;
}

template<typename T>
Fraction<T>::operator double() const {
   return numerateur / (double) denominateur;
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
   T pgdc = plusGrandDiviseurCommun((T) abs(numerateur), denominateur);
   return Fraction<T>(numerateur / pgdc, denominateur / pgdc);
}

template<typename T>
bool Fraction<T>::identite(const Fraction<T> &f) const {
   return numerateur == f.numerateur && denominateur == f.denominateur;
}

template<typename T>
bool operator==(const Fraction<T> &lhs, const Fraction<T> &rhs) {
   return (float) lhs == (float) rhs;
}

template<typename T>
bool debordementAddition(T a, T b) {
   T res = a + b;
   if (a > 0 && b > 0 && res < 0)
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
Fraction<T> operator+(Fraction<T> lhs, const Fraction<T> &rhs) {
   lhs += rhs;
   return lhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator+=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();
   T denomPGDC = plusGrandDiviseurCommun(tmpMembreDroite.denominateur,
                                         tmpMembreGauche.denominateur);
   // Débordement ajustement dénominateur quand dénominateurs différents et pas
   // multiples
   if (debordementMultiplication(T(tmpMembreDroite.denominateur / denomPGDC),
                                 tmpMembreGauche.denominateur)) {
      throw std::overflow_error("debordement");
   }

   // facteur d'ajustement des membres
   T facteurGauche = tmpMembreDroite.denominateur / denomPGDC;
   T facteurDroite = tmpMembreGauche.denominateur / denomPGDC;
   // TODO : simplifier en mettant les throw dans debordement
   if (debordementMultiplication((T) facteurGauche, tmpMembreGauche.numerateur)) {
      throw std::overflow_error("debordement");
   }
   if (debordementMultiplication((T) facteurDroite, tmpMembreDroite.numerateur)) {
      throw std::overflow_error("debordement");
   }
   T numerateurGauche = (T)facteurGauche * tmpMembreGauche.numerateur;
   T numerateurDroite = (T)facteurDroite * tmpMembreDroite.numerateur;

   if (debordementAddition(numerateurGauche, numerateurDroite)) {
      throw std::overflow_error("debordement");
   }

   Fraction<T> resultat = { numerateurGauche + numerateurDroite,  tmpMembreGauche
                            .denominateur / denomPGDC * tmpMembreDroite.denominateur };
   return *this = resultat.simplifier();
}

template<typename T>
Fraction<T> operator*(Fraction<T> lhs, const Fraction<T> &rhs) {
   lhs *= rhs;
   return lhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator*=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();

   T diagonaleGauche = plusGrandDiviseurCommun((T) abs(tmpMembreGauche.numerateur),
                                               tmpMembreDroite.denominateur);
   tmpMembreGauche.numerateur /= diagonaleGauche;
   tmpMembreDroite.denominateur /= diagonaleGauche;
   T diagonaleDroite = plusGrandDiviseurCommun(tmpMembreGauche.denominateur,
                                               (T) abs(tmpMembreDroite.numerateur));
   tmpMembreGauche.denominateur /= diagonaleDroite;
   tmpMembreDroite.numerateur /= diagonaleDroite;

   if (debordementMultiplication(tmpMembreGauche.numerateur,
                                 tmpMembreDroite.numerateur))
      throw std::out_of_range("Il y a debordement lors de la multiplication des "
                              "numerateurs");
   if (debordementMultiplication(tmpMembreGauche.denominateur,
                                 tmpMembreDroite.denominateur))
      throw std::out_of_range("Il y a debordement lors de la multiplication des "
                              "denominateurs");
   tmpMembreGauche.numerateur *= tmpMembreDroite.numerateur;
   tmpMembreGauche.denominateur *= tmpMembreDroite.denominateur;
   *this = tmpMembreGauche;
   return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Fraction<T> &rhs) {
   os << (long long) rhs.numerateur << " / " << (long long) rhs.denominateur;
   return os;
}


#endif
