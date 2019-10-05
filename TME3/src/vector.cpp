#include "vector.h"
#include <vector>
#include <string>
#include <iostream>
#include "timer.h"

using namespace std;
#include "GPL_2_text.h"
namespace vector_bench{


    void backInsert    (){

        //On démarre le chrono
        Timer chrono;
        chrono.start();

        // On cré un vecteur de string
        vector<string> vecteurTexte;
        
        // On copie le tableau de char* dans un vecteur
        for (int i=0; GPL_2_text[i] != NULL ; i++) vecteurTexte.push_back(GPL_2_text[i]);

        // On affiche le nombre d'élements du vecteur
        cout << "Le vecteur contient " << vecteurTexte.size()<< " elements." << endl;

        // On affiche tous les élements sur une ligne
        for(string motCourant : vecteurTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << chrono;
    }

    void frontInsert   (){

        
        //On démarre le chrono
        Timer chrono;
        chrono.start();

        // On cré un vecteur de string
        vector<string> vecteurTexte;
        
        //On compte le nombre d'éléments du tableau
        size_t longueur=0;
        for (int i=0; GPL_2_text[i] != NULL ; i++) ++longueur;

        // On copie le tableau de char* dans un vecteur
        for (int i=longueur-1; i>0 ; i--){
                vecteurTexte.resize(longueur-i);
                for(int j=(vecteurTexte.size()-1); j>0;j--) vecteurTexte[j]=vecteurTexte[j-1];
                vecteurTexte[0]=GPL_2_text[i];
            }

        // On affiche le nombre d'élements du vecteur
        cout << "Le vecteur contient " << vecteurTexte.size()<< " elements." << endl;

        // On affiche tous les élements sur une ligne
        for(string motCourant : vecteurTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << chrono;



    }







}