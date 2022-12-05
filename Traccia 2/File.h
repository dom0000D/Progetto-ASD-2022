#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <fstream>
#include "Graph.h"
using namespace std;

//La classe File dispone le operazioni  per caricare il grafo e applicare le operazioni richieste. 
class File {
    private:
        Graph<int> *GRAFO; //usa Graph
        bool createGraphByFile(ifstream &file);
    public:
        File() { GRAFO = nullptr; };
        void start(string file);
};

//Crea e carica i dati nel grafo
bool File::createGraphByFile(ifstream &file) {
    string tmp;
    int P = 0, N = 0;
    int row = 1; // contatore righe del file
    // Lettura dei primi due valori, rispettivamente N e P
    if(!file.is_open()){
        cout << "\n[WARNING] Errore apertura file. Il file potrebbe essere inesistente o trovarsi nel path diverso del programma" << endl;
        return false;
    } 

    if (getline(file, tmp)) {
        auto del = tmp.find(" "); //dichiaro una stringa deliminatore che é lo spazio
        string startNodes = tmp.substr(0,del); //estrazione della sottostringa che va da 0 allo spazio
        string startEdges = tmp.substr(del);   //estrazione della stringa successiva allo spazio
    //Conversione string to int    
        N = stoi(startNodes, nullptr,10); //inizializzo i nodi
        P = stoi(startEdges, nullptr,10); //inizializzo gli archi
    }
    // Controllo sui valori di N e P
    if ((P <= 0 || P >= 10000) || (N <= 0 || N > 1000)) {
        cout << "\n[WARNING] I dati alla riga principale sono errati. I valori iniziali devono essere 1 <= N <= 1000 e 0 <= P <= 10000.\n";
        return false;
    }
    
    GRAFO = new Graph<int>(N,P); // Inizializzazione prima riga del grafo
    // Lettura dati dal file
    while (getline(file,tmp)) {
        row++;
        auto space = tmp.find(" ");
        string firstNum = tmp.substr(0,space);
        string secondNum = tmp.substr(space);
        
        string tmpweight = tmp.substr(space+1);

        auto space2 = tmpweight.find(" ");
        string weight = tmpweight.substr(space2);
        int node = stoi(firstNum, nullptr,10);
        int edge = stoi(secondNum, nullptr,10);
        int peso = stoi(weight, nullptr,10);
        // Aggiunta arco al grafo
        bool load = GRAFO->addEdge(node, edge, peso);
        if (!load) {
            cout << "[WARNING] Errore alla riga " << row << endl;
            return false;
        }
    }
    return true;
}

//Funzione che verrá richiamata nel main: carca il file e calcola MST e 2BESTMST
void File::start(string file) {
    ifstream numFile;
    numFile.open(file, ios::in);
    if (createGraphByFile(numFile)) {
        cout << "\n[SUCCESS] File " << file << " caricato correttamente." << endl;
        GRAFO -> searchBestMST();
    }
}

#endif // FILE_H
