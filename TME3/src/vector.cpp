#include "vector.h"
#include "GPL_2_text.h"

using namespace std;

namespace map_bench{

    void testMap(){
        //On démarre le chrono
        Timer chrono;
        chrono.start();

        map<string, int> mapMots; // On déclare la map

        // On copie le tableau de char* dans la map
        for (int i=0; GPL_2_text[i] != NULL ; i++) ++mapMots[GPL_2_text[i]];

        // On affiche le nombre d'éléments dans la map :
        cout << "le nombre d'éléments dans la map<>. est de : " << mapMots.size() << endl;

        //On affiche tous les mots et on les compte
        size_t totalMots = 0;
        for (const auto &p : mapMots){
            cout << p.first << ":" << p.second << " ";
            totalMots += p.second;
        }

        //On affiche le nombre de mots
        cout << endl << "Le nombre de mot dans la map<>. est de : " << totalMots << endl;

    }
}// fin namespace map_bench

namespace list_bench{
    void backInsert    (){
        //On démarre le chrono
        Timer chrono;
        chrono.start();

        // On cré un vecteur de string
        list<string> listeTexte;
        
        // On copie le tableau de char* dans la liste
        for (int i=0; GPL_2_text[i] != NULL ; i++) listeTexte.push_back(GPL_2_text[i]);

        // On affiche le nombre d'élements de la liste
        cout << "La liste contient " << listeTexte.size()<< " elements." << endl;

        // On trie par ordre alphabétique
        listeTexte.sort();

        // On affiche tous les élements sur une ligne
        //for(string motCourant : listeTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << "BackInsert() "<< chrono;
    }


    void frontInsert   (){
        
        //On démarre le chrono
        Timer chrono;
        chrono.start();

        // On cré une liste de string
        list<string> listeTexte;
        
        // On copie le tableau de char* dans la lsite
        for (int i=0; GPL_2_text[i] != NULL ; i++) listeTexte.push_front(GPL_2_text[i]);

        // On affiche le nombre d'élements de la liste
        cout << "La liste contient " << listeTexte.size()<< " elements." << endl;

        // On trie par ordre alphabétique
        listeTexte.sort();

        // On affiche tous les élements sur une ligne
        //for(string motCourant : listeTexte) cout << motCourant << " ";
    
        // On arrête le chrono
        chrono.stop();
        cout << "frontInsert() "<< chrono;
    }


    void sortEachInsert(){

        //On démarre le chrono
        Timer chrono;
        chrono.start();

        // On cré un vecteur de string
        list<string> listeTexte;
        
        // On copie le tableau de char* dans la liste
        for (int i=0; GPL_2_text[i] != NULL ; i++) {
            listeTexte.push_back(GPL_2_text[i]);
            listeTexte.sort();
        }

        // On affiche le nombre d'élements de la liste
        cout << "La liste contient " << listeTexte.size()<< " elements." << endl;

        // On trie par ordre alphabétique
        listeTexte.sort();

        // On affiche tous les élements sur une ligne
        //for(string motCourant : listeTexte) cout << motCourant << " ";
    
        // On arrête le chrono
        chrono.stop();
        cout << "sortEachInsert() "<< chrono;
    }
} //fin namespace list_bench

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
            sort(vecteurTexte.begin(), vecteurTexte.end());
        }

        // On affiche le nombre d'élements du vecteur
        cout << "Le vecteur contient " << vecteurTexte.size()<< " elements." << endl;
        
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

        // On trie par ordre alphabétique
        sort(vecteurTexte.begin(), vecteurTexte.end());

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
        sort(vecteurTexte.begin(), vecteurTexte.end());
       
        // On affiche tous les élements sur une ligne
        //for(string motCourant : vecteurTexte) cout << motCourant << " ";

        // On arrête le chrono
        chrono.stop();
        cout << "FrontInsert() "<< chrono;
    }
}//fin namespace vector_bench