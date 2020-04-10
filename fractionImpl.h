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
#include <limits>

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
T debordementAddition(T a, T b) {
    const std::string MSG_ERREUR = "Debordement lors de l'addition des numerateurs";
    if (std::numeric_limits<T>::max() - a < b)
        (a > 0) ? throw std::overflow_error(MSG_ERREUR) :
        throw std::underflow_error(MSG_ERREUR);
    return a + b;
}

/**
 * Détermine si le produit de deux entiers a et b va déborder. Lance un exception
 * si c'est le cas
 */
template<typename T>
T debordementMultiplication(T a, T b, const std::string& MSG_ERREUR) {
    if(std::numeric_limits<T>::max() / std::abs(a) < std::abs(b)) {
        if (a < 0 != b < 0) //fonction logique xor
            throw std::underflow_error(MSG_ERREUR);
        else
            throw std::overflow_error(MSG_ERREUR);
    }
    return a * b;
}

template<typename T>
Fraction<T> operator+(Fraction<T> lhs, const Fraction<T> &rhs) {
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

    T numerateurGauche = debordementMultiplication(facteurGauche, tmpMembreGauche.numerateur, MSG_ERREUR_MULTIPLICATION);
    T numerateurDroite =  debordementMultiplication(facteurDroite, tmpMembreDroite.numerateur, MSG_ERREUR_MULTIPLICATION);

    Fraction<T> resultat (debordementAddition(numerateurGauche, numerateurDroite),
                            T(facteurDroite * tmpMembreDroite.denominateur));

    return *this = resultat.simplifier();
}

template<typename T>
Fraction<T> operator*(Fraction<T> lhs, const Fraction<T> &rhs) {
    return lhs *= rhs;;
}

template<typename T>
Fraction<T> &Fraction<T>::operator*=(const Fraction<T> &rhs) {
    //simplification des membre pour réduire les chances d'overflow
    Fraction<T> tmpMembreGauche = simplifier();
    Fraction<T> tmpMembreDroite = rhs.simplifier();

    //On intervertit les attributs de rhs et this pour les simplifier "en croix"
    //pour réduire les chances d'overflow
    std::swap(tmpMembreDroite.numerateur, tmpMembreGauche.numerateur);
    tmpMembreDroite.simplifier();
    tmpMembreGauche.simplifier();

    //verification des debordements possibles lors de la multiplication
    //la fonction debordement renvoie le resultat s'il n'y a pas de debordement
    this->numerateur = debordementMultiplication(tmpMembreGauche.numerateur, tmpMembreDroite
            .numerateur, "Debordement lors de la multiplication des numerateurs");
    this->denominateur = debordementMultiplication(tmpMembreGauche.denominateur, tmpMembreDroite
            .denominateur, "Debordement lors de la multiplication des denominateurs");
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Fraction<T> &rhs) {
    //cast en long long pour afficher les chars avec leurs valeurs numériques
    os << (long long) rhs.numerateur << " / " << (long long) rhs.denominateur;
    return os;
}
#endif
