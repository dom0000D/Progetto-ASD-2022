#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <fstream>
#include "RBGraph.h"
using namespace std;

//La classe File dispone le operazioni  per caricare il grafo e applicare le operazioni richieste. 
class File {
    private:
        RBGraph<int> *GRAFO; //usa RBGraph
        bool createGraphByFile(ifstream &file);
        void menu();
    public:
        File() { GRAFO = nullptr; };
        void start(string file);
};

//Crea e carica i dati nel grafo
bool File::createGraphByFile(ifstream &file) {
    string tmp;
    int M = 0, N = 0;
    int row = 1; // contatore righe del file
    // Lettura dei primi due valori, rispettivamente N e M [numero di nodi e archi]
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
        M = stoi(startEdges, nullptr,10); //inizializzo gli archi
    }
    // Controllo sui valori di N e M
    if ((M < 0 || M > 1000) || (N < 0 || N > 1000)) {
        cout << "\n[WARNING] I dati alla riga principale sono errati. I valori iniziali devono essere 0 <= N <= 1000 e 0 <= M <= 1000.\n";
        return false;
    }
    
    GRAFO = new RBGraph<int>(N,M); // Inizializzazione prima riga del grafo
    // Lettura dati dal file
    while (getline(file,tmp)) {
        row++;
        auto space = tmp.find(" ");
        string firstNum = tmp.substr(0,space);
        string secondNum = tmp.substr(space);
        int node = stoi(firstNum, nullptr,10);
        int edge = stoi(secondNum, nullptr,10);
        // Aggiunta arco al grafo
        bool load = GRAFO->addEdge(node, edge);
        if (!load) {
            cout << "[WARNING] Errore alla riga " << row << endl;
            return false;
        }
    }
    return true;
}

//Si occupa della gestione delle operazioni svolte dall'utente attraverso il menù
 void File::menu() {
    int digit = 0;
    char cont;
    int source, dest;
    do {
        //MENU
        cout << "\n\t\t ++ INSERIRE UN NUMERO PER UN'OPERAZIONE ++" << endl;
        cout << "[0] EXIT" << endl;
        cout << "[1] AddEdge(i,j)" << endl;
        cout << "[2] RemoveEdge(i,j)" << endl;
        cout << "[3] FindEdge(i,j)" << endl;
        cout << "[4] Visita in Ampiezza [BFS(s)]" << endl;
        cout << "[5] Stampa del Grafo" << endl;
        cout << "[DIGIT]: ";
        cin >> digit;

        //check sull input dell'utente
        if (digit >= 1 && digit <= 3) {
            cout << "\nHai scelto: " << digit << endl;
            
            if (digit == 1) {
            cout << "\t\t****** ADD EDGE *****"<< endl;
            cout << "Digita il nodo sorgente per aggiungere un collegamento: ";
            cin >> source;
            cout << "Digita il nodo destinazione per aggiungere un collegamento: ";
            cin >> dest;
                if (GRAFO->addEdge(source, dest)!= 0) {
                    cout << "[SUCCESS] Arco (" << source << " " << dest << ") aggiunto." << endl;
                }
            }
            else if (digit == 2) {
            cout << "\t\t****** REMOVE EDGE *****"<< endl;
            cout << "Digita il nodo sorgente per rimuovere un collegamento: ";
            cin >> source;
            cout << "Digita il nodo destinazione per rimuovere un collegamento: ";
            cin >> dest;
                if (GRAFO->removeEdge(source, dest)!= 0) {
                    cout << "[SUCCESS] Arco (" << source << " " << dest << ") rimosso." << endl;
                }
            }
            else if (digit == 3) {
            cout << "\t\t****** FIND EDGE *****"<< endl;
            cout << "Digita il nodo sorgente per la ricerca: ";
            cin >> source;
            cout << "Digita il nodo destinazione per la ricerca: ";
            cin >> dest;
                if (GRAFO->findEdge(source, dest)!= 0) {
                    cout << "[SUCCESS] L'arco (" << source << " " << dest << ") é presente nel grafo." << endl;
                }
                else {
                    cout << "[WARNING] L'arco " << source << " " << dest << " non é presente nel grafo." << endl;
                }
            }
        }
        else if (digit == 4) {
            cout << "\t\t****** BREADTH-FIRST SEARCH *****"<< endl;
            cout << "\nInserire il nodo sorgente per la Visita in Ampiezza [BFS]: ";
            cin >> source;
            cout << "BFS in corso..."<<endl;
            cout << "BFS: ";
            GRAFO->BFS(source);
        }
        else if (digit == 5) {
            cout << "\t\t****** STAMPA GRAFO *****"<< endl;
            GRAFO->StampaGrafo();
        }

        else {
            if (digit != 0) {
				cout << "\n[WARNING] Non esiste un'operazione per la tua scelta " << digit << ": riprovare [0 1 2 3 4 5]" << endl;
            }
        }
        cout << "Vuoi fare un'altra operazione? [Y/y per continuare. Qualsiasi tasto per uscire.]" << endl;
        cin >> cont;
        if (cont == 'y' || cont == 'Y')
            continue;
        else break; 
    } while (digit != 0);
    cout << "[EXIT] Grazie per aver usato questo programma" << endl;
}


//Funzione che verrá richiamata nel main: carca il file e lancia il menú di scelta 
void File::start(string file) {
    ifstream numFile;
    numFile.open(file, ios::in);
    if (createGraphByFile(numFile)) {
        cout << "\n[SUCCESS] File " << file << " caricato correttamente." << endl;
        menu();
    }
}

#endif // FILE_H
