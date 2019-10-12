 /*size_t i=1;
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
        */



            /*size_t i=n;
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
                
            };*/