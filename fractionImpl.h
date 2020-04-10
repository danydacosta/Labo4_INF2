/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.cpp
 Auteur(s)   : Oliveira da Costa Dany, Pozniakoff Lev, Vallon Axel
 Date        : 10.04.2020
 But         : Définition des fonctions membres de la classe Fraction.

 Remarque(s) : Contient également trois autres fonctions non-membres ;
 plusGrandDiviseurCommun(), debordementAddition(), debordementMultiplication().

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

//
// Created by Lev on 30.03.2020.
//
#include "fraction.h"
#include <iostream>
#include <cmath>

#ifndef FRACTIOIMPLN_H
#define FRACTIONIMPL_H

#include <limits>
#include <stdexcept>

#include "fraction.h"

template<typename T>
Fraction<T>::Fraction(T n, T d) : numerateur(n), denominateur(d) {
   if (d < 0)
      throw std::invalid_argument("Le denominateur ne peut pas etre negatif");
   if (d == 0)
      throw std::invalid_argument("Le denominateur ne peut pas etre nul");
}

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

/**
 * Détermine si la somme de deux entiers a et b va déborder. Lance un exception
 * si c'est le cas
 */
template<typename T>
void debordementAddition(T a, T b) {
   T res = a + b;
   const std::string MSG_ERREUR = "Debordement lors de l'addition des numerateurs";
   if (a > 0 && b > 0 && res < 0) {
      throw std::overflow_error(MSG_ERREUR);
   } else if (a < 0 && b < 0 && res > 0) {
      throw std::underflow_error(MSG_ERREUR);
   }
}

/**
 * Détermine si le produit de deux entiers a et b va déborder. Lance un exception
 * si c'est le cas
 */
template<typename T>
void debordementMultiplication(T a, T b, const std::string& MSG_ERREUR) {
   T res = a * b;
   if(!(a == res / b))
      throw std::overflow_error(MSG_ERREUR);
}

template<typename T>
Fraction<T> operator+(Fraction<T> lhs, const Fraction<T> &rhs){
   return lhs += rhs;
}

template<typename T>
Fraction<T> &Fraction<T>::operator+=(const Fraction<T> &rhs) {
   Fraction<T> tmpMembreGauche = simplifier();
   Fraction<T> tmpMembreDroite = rhs.simplifier();
   T denomPGDC = plusGrandDiviseurCommun(tmpMembreDroite.denominateur,
                                         tmpMembreGauche.denominateur);
   const std::string MSG_ERREUR_MULTIPLICATION = "Debordement de la "
                                                 "multiplication lors de "
                                                 "l'ajustement des termes";
   // Débordement possible lors de la multiplication des dénominateurs dans le
   // cas où les dénominateurs sont différents et pas multiples l'un de l'autre
   debordementMultiplication(T(tmpMembreDroite.denominateur / denomPGDC),
                                 tmpMembreGauche.denominateur, MSG_ERREUR_MULTIPLICATION);

   // Calcul des facteurs d'ajustement de chaque fraction
   T facteurGauche = tmpMembreDroite.denominateur / denomPGDC;
   T facteurDroite = tmpMembreGauche.denominateur / denomPGDC;

   debordementMultiplication((T) facteurGauche, tmpMembreGauche.numerateur, MSG_ERREUR_MULTIPLICATION);
   debordementMultiplication((T) facteurDroite, tmpMembreDroite.numerateur, MSG_ERREUR_MULTIPLICATION);
   T numerateurGauche = (T)facteurGauche * tmpMembreGauche.numerateur;
   T numerateurDroite = (T)facteurDroite * tmpMembreDroite.numerateur;

   debordementAddition(numerateurGauche, numerateurDroite);

   Fraction<T> resultat = { T(numerateurGauche + numerateurDroite),
                            T(facteurDroite * tmpMembreDroite.denominateur) };

   return *this = resultat.simplifier();
}

template<typename T>
Fraction<T> operator*(Fraction<T> lhs, const Fraction<T> &rhs) {
    return lhs *= rhs;
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

   debordementMultiplication(tmpMembreGauche.numerateur, tmpMembreDroite
   .numerateur, "Debordement lors de la multiplication des numerateurs");
   debordementMultiplication(tmpMembreGauche.denominateur, tmpMembreDroite
   .denominateur, "Debordement lors de la multiplication des denominateurs");

   tmpMembreGauche.numerateur *= tmpMembreDroite.numerateur;
   tmpMembreGauche.denominateur *= tmpMembreDroite.denominateur;
   *this = tmpMembreGauche;
   return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Fraction<T> &rhs) {
   // TODO : cast explicite pour l'affichage des chars
   os << (long long) rhs.numerateur << " / " << (long long) rhs.denominateur;
   return os;
}
#endif
