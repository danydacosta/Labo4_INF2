/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : main.cpp
 Auteur(s)   : Oliveira da Costa Dany, Pozniakoff Lev, Vallon Axel
 Date        : 10.04.2020
 But         : -

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#include "fraction.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
   cout << "======== Debut du programme de test ========" << endl;
   {
      cout << "******** Test du constructeur ********" << endl;
      int n1 = 1, d1 = -3;
      cout << "Test de construction de la fraction " << n1 << " / " << d1 << endl;
      try {
         Fraction<int> f1(1, -3);
      } catch(invalid_argument& e) {
         cout << e.what() << endl;
      }
      int n2 = 1, d2 = 0;
      cout << "Test de construction de la fraction " << n2 << " / " << d2 << endl;
      try {
         Fraction<int> f1(1, 0);
      } catch(invalid_argument& e) {
         cout << e.what() << endl;
      }
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur de cast ********" << endl;
      Fraction<int> f1(1, 3);
      cout << "f1 = " << f1 << endl;
      cout << "(float)f1 = " << (float)f1 << endl;
      cout << "(double)f1 = " << (double)f1 << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de la simplification ********" << endl;
      Fraction<int> f1(70, 7);
      cout << "f1 = " << f1 << endl;
      cout << "f1.simplifier() = " << f1.simplifier() << endl;
      cout << "---" << endl;
      Fraction<int> f2(-70, 7);
      cout << "f1 = " << f2 << endl;
      cout << "f2.simplifier() = " << f2.simplifier() << endl;
      cout << "---" << endl;
      Fraction<int> f3(-127, 3);
      cout << "f3 = " << f3 << endl;
      cout << "f3.simplifier() = " << f3.simplifier() << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'identite ********" << endl;
      Fraction<int> f1(1, 4);
      Fraction<int> f2(1, 4);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      cout << "f1.identite(f2) = " << boolalpha << f1.identite(f2) << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur d'egalite ********" << endl;
      Fraction<int> f1(12, 4);
      Fraction<int> f2(3, 1);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      cout << "f1 == f2 : " << boolalpha << (f1 == f2) << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur += ********" << endl;
      Fraction<char> f1(126, 2);
      Fraction<char> f2(1, 2);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      try {
         cout << "f1 += f2 : ";
         cout << (f1 += f2) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "f1 = " << f1 << endl;
      cout << "---" << endl;
      Fraction<char> f3(127, 2);
      Fraction<char> f4(1, 2);
      cout << "f3 = " << f3 << endl;
      cout << "f4 = " << f4 << endl;
      try {
         cout << "f3 += f4 : ";
         cout << (f3 += f4) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "f3 = " << f3 << endl;
      cout << "---" << endl;
      Fraction<char> f5(1, 2);
      Fraction<char> f6(5, 4);
      cout << "f5 = " << f5 << endl;
      cout << "f6 = " << f6 << endl;
      try {
         cout << "f5 += f6 : ";
         cout << (f5 += f6) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "f5 = " << f5 << endl;
      cout << "---" << endl;
      Fraction<char> f7(127, 4);
      Fraction<char> f8(3, 2);
      cout << "f7 = " << f7 << endl;
      cout << "f8 = " << f8 << endl;
      try {
         cout << "f7 += f8 : ";
         cout << (f7 += f8) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "f7 = " << f7 << endl;
      cout << "---" << endl;
      Fraction<char> f9(1, 73);
      Fraction<char> f10(1, 64);
      cout << "f9 = " << f9 << endl;
      cout << "f10 = " << f10 << endl;
      try {
         cout << "f9 += f10 : ";
         cout << (f9 += f10) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "f9 = " << f9 << endl;
      cout << "---" << endl;
      Fraction<char> f11(-127, 4);
      Fraction<char> f12(4, 5);
      cout << "f11 = " << f11 << endl;
      cout << "f12 = " << f12 << endl;
      try {
         cout << "f11 += f12 : ";
         cout << (f11 += f12) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "f11 = " << f11 << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur + ********" << endl;
      Fraction<char> f1(126, 2);
      Fraction<char> f2(1, 2);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      try {
         cout << "f1 + f2 = ";
         cout << (f1 + f2) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "---" << endl;
      Fraction<char> f3(3, 6);
      Fraction<char> f4(-128, 3);
      cout << "f3 = " << f3 << endl;
      cout << "f4 = " << f4 << endl;
      try {
         cout << "f3 + f4 = ";
         cout << (f3 + f4) << endl;
      } catch(overflow_error& e) {
         cout << e.what() << endl;
      }
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur *= ********" << endl;
      Fraction<char> f1(126, 2);
      Fraction<char> f2(1, 2);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      try {
         cout << "f1 *= f2 : ";
         cout << (f1 *= f2) << endl;
      } catch(out_of_range& e) {
         cout << e.what() << endl;
      }
      cout << "f1 = " << f1 << endl;
      cout << "---" << endl;
      Fraction<char> f3(126, 101);
      Fraction<char> f4(1, 2);
      cout << "f3 = " << f3 << endl;
      cout << "f4 = " << f4 << endl;
      try {
         cout << "f3 *= f4 : ";
         cout << (f3 *= f4) << endl;
      } catch(out_of_range& e) {
         cout << e.what() << endl;
      }
      cout << "f3 = " << f3 << endl;
      cout << "************************************" << endl;
   }
   {
      cout << "******** Test de l'operateur * ********" << endl;
      Fraction<char> f1(126, 2);
      Fraction<char> f2(1, 2);
      cout << "f1 = " << f1 << endl;
      cout << "f2 = " << f2 << endl;
      try {
         cout << "f1 * f2 = ";
         cout << (f1 * f2) << endl;
      } catch(out_of_range& e) {
         cout << e.what() << endl;
      }
      cout << "---" << endl;
      Fraction<char> f3(3, 6);
      Fraction<char> f4(-127, 3);
      cout << "f3 = " << f3 << endl;
      cout << "f4 = " << f4 << endl;
      try {
         cout << "f3 * f4 = ";
         cout << (f3 * f4) << endl;
      } catch(out_of_range& e) {
         cout << e.what() << endl;
      }
      cout << "---" << endl;
      Fraction<char> f5(-73, 61);
      Fraction<char> f6(5, 7);
      cout << "f5 = " << f5 << endl;
      cout << "f6 = " << f6 << endl;
      try {
         cout << "f5 * f6 = ";
         cout << (f5 * f6) << endl;
      } catch(out_of_range& e) {
         cout << e.what() << endl;
      }
      cout << "f5 = " << f5 << endl;
      cout << "************************************" << endl;
   }

   return EXIT_SUCCESS;
}