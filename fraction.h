/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fraction.cpp
 Auteur(s)   : Oliveira da Costa Dany, Pozniakoff Lev, Vallon Axel
 Date        : 10.04.2020
 But         : -

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

template <typename T> class Fraction;

template <typename T>
std::ostream& operator <<(std::ostream& os, const Fraction<T>& rhs);

template <typename T>
class Fraction {
   /**
    * Surcharge de l'opérateur de flux pour affichage d'une fraction (non simplifié)
    */
   friend std::ostream& operator << <>(std::ostream& os, const Fraction<T>& rhs);

    /**
    * Surcharge de l'opérateur d'addition
    * @param f la fraction avec laquelle effectuer l'addition
    * @return La fraction représentant la somme
    */
    friend Fraction<T> operator + (const Fraction<T>& rhs) ;

    /**
    * Surcharge de l'opérateur de multiplication
    * @param f la fraction avec laquelle effectuer la multiplication
    * @return La fraction représentant le produit
    */
    friend Fraction<T> operator * (const Fraction<T>& rhs) const;
public:
   /**
    * Crée une fraction
    * @param n le numérateur
    * @param d le dénominateur
    */
   Fraction<T>(T n, T d);
   /**
    * Surcharge de l'opérateur de cast (float)
    * @return la valeur décimale en float de la fraction
    */
   operator float() const;
   /**
    * Surcharge de l'opérateur de cast (double)
    * @return la valeur décimale en double de la fraction
    */
   operator double() const;
   /**
    * Retourne une nouvelle fraction irréductible
    * @return la fraction irréductible
    */
   Fraction<T> simplifier() const;
   /**
    * Retourne si la fraction f passée en paramètre est identique à la fraction
    * courante, c.-à-d. si les numérateurs et dénominateurs sont égaux
    * @param f la fraction avec laquelle tester l'identité
    * @return si oui ou non deux fractions forment une identité
    */
   bool identite(const Fraction<T>& f) const;
   /**
    * Teste l'égalité numérique de deux fractions
    * @param f la fraction avec laquelle tester l'égalité numérique
    * @return si oui ou non les fractions sont égales
    */
   bool operator == (const Fraction<T>& rhs) const;

   /**
    * Surcharge de l'opérateur d'affectation composé +=
    * @param rhs la fraction avec laquelle effectuer l'addition
    * @return l'objet fraction courant dont on a ajouté rhs
    */
   Fraction<T>& operator += (const Fraction<T>& rhs);

   /**
    * Surcharge de l'opérateur d'affectation composé *=
    * @param rhs la fraction avec laquelle effectuer la multiplication
    * @return l'objet fraction courant dont on a multiplié rhs
    */
   Fraction<T>& operator *= (const Fraction<T>& rhs);
private:
   T numerateur, denominateur;
};

#include "fractionImpl.h"
#endif
