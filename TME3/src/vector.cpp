#include "vector.h"
#include <vector>
#include <string>
#include <iostream>
#include "timer.h"
#include <fstream>
#include <regex>

using namespace std;
#include "GPL_2_text.h"

namespace vector_bench{

    void sortEachInsert(){
        //On démarre le chrono
        Timer chrono;
        chrono.start();

        // On cré un vecteur de string
        vector<string> vecteurTexte;
        
        // On copie le tableau de char* dans un vecteur en le triant
        for (size_t n=0; GPL_2_text[n] != NULL ; n++){
            vecteurTexte.push_back(GPL_2_text[n]);

            // On trie par ordre alphébétique
            size_t i=n;
            while(i > 0){
                string temp;
                size_t  j=i;

                // On met en minuscule pour comparer
                string moti = vecteurTexte[i], motjmoins1 = vecteurTexte[j-1];
                transform(moti.begin(),moti.end(),moti.begin(),::tolower);
                transform(motjmoins1.begin(),motjmoins1.end(),motjmoins1.begin(),::tolower);

                while (j>0 && (moti < motjmoins1)) {
                    --j ; // On compare au moins précédent
                    if (j>0){
                        // on met en minuscule le mot précédent
                        motjmoins1 = vecteurTexte[j-1];
                        transform(motjmoins1.begin(),motjmoins1.end(),motjmoins1.begin(),::tolower);
                    }
                }

                // Si j!=i c'est qu'on a trouvé une meilleurs place
                if (j != i){
                    temp            = vecteurTexte[j];
                    vecteurTexte[j] = vecteurTexte[i];
                    vecteurTexte[i] = temp;
                }else --i; // Sinon on passe au mot suivant
                
            };
        }

        // On affiche tous les élements sur une ligne
        //for(string motCourant : vecteurTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << "SortEachInsert() "<< chrono;


    }

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

        // On trie par ordre alphébétique
        size_t i=1;
        do{
            string temp;
            size_t  j=i;

            // On met en minuscule pour comparer
            string moti = vecteurTexte[i], motjmoins1 = vecteurTexte[j-1];
            transform(moti.begin(),moti.end(),moti.begin(),::tolower);
            transform(motjmoins1.begin(),motjmoins1.end(),motjmoins1.begin(),::tolower);

            while (j>0 && (moti < motjmoins1)) {
                --j ; // On compare au moins précédent
                if (j>0){
                    // on met en minuscule le mot précédent
                    motjmoins1 = vecteurTexte[j-1];
                    transform(motjmoins1.begin(),motjmoins1.end(),motjmoins1.begin(),::tolower);
                }
            }

            // Si j!=i c'est qu'on a trouvé une meilleurs place
            if (j != i){
                temp            = vecteurTexte[j];
                vecteurTexte[j] = vecteurTexte[i];
                vecteurTexte[i] = temp;
            }else ++i; // Sinon on passe au mot suivant
            
        }while(i < vecteurTexte.size());

        // On affiche tous les élements sur une ligne
        //for(string motCourant : vecteurTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << "BackInsert() "<< chrono;
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
        for (int i=longueur-1; i>=0 ; i--){
                vecteurTexte.resize(longueur-i);
                for(int j=(vecteurTexte.size()-1); j>0;j--) vecteurTexte[j]=vecteurTexte[j-1];
                vecteurTexte[0]=GPL_2_text[i];
        }

        // On affiche le nombre d'élements du vecteur
        cout << "Le vecteur contient " << vecteurTexte.size()<< " elements." << endl;

        // On trie par ordre alphébétique
        size_t i=1;
        do{
            string temp;
            size_t  j=i;

            // On met en minuscule pour comparer
            string moti = vecteurTexte[i], motjmoins1 = vecteurTexte[j-1];
            transform(moti.begin(),moti.end(),moti.begin(),::tolower);
            transform(motjmoins1.begin(),motjmoins1.end(),motjmoins1.begin(),::tolower);

            while (j>0 && (moti < motjmoins1)) {
                --j ; // On compare au moins précédent
                if (j>0){
                    // on met en minuscule le mot précédent
                    motjmoins1 = vecteurTexte[j-1];
                    transform(motjmoins1.begin(),motjmoins1.end(),motjmoins1.begin(),::tolower);
                }
            }

            // Si j!=i c'est qu'on a trouvé une meilleurs place
            if (j != i){
                temp            = vecteurTexte[j];
                vecteurTexte[j] = vecteurTexte[i];
                vecteurTexte[i] = temp;
            }else ++i; // Sinon on passe au mot suivant
            
        }while(i < vecteurTexte.size());

        // On affiche tous les élements sur une ligne
        //for(string motCourant : vecteurTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << "FrontInsert() "<< chrono;



    }







}