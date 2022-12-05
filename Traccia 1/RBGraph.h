#ifndef RBGRAPH_H
#define RBGRAPH_H

#include <iostream>
#include <vector>
#include <queue>   // BFS
#include "GNode.h"
using namespace std;

template <class T>
class RBGraph {
private:
    vector<GNode<T> *> *vertix;

protected:
    GNode<T> *createNewGNode(T data);

public:
    RBGraph(int vertix, int edges);
    bool addEdge(T src, T dest);
    bool findEdge(T src, T dest);
    bool removeEdge(T src, T dest);
    void BFS(T src);
    void StampaGrafo();
    int VertixNumber();
};

//Costruttore
template<class T>
RBGraph<T>::RBGraph(int vertix, int edges) {
    this->vertix = new vector<GNode<T> *>(vertix + 1);
}

template<class T>
void RBGraph<T>::StampaGrafo() {
    for (auto x : *vertix) {
        if (x != nullptr) {
            cout << x->AdiacentPrint();
        }
    }
}
template<class T>
GNode<T> *RBGraph<T>::createNewGNode(T newNode) {
    GNode<T> *node;
    // Il nodo non puó essere creato poiché supera il size del numero dei vertici
    if (newNode >= vertix->size()) {
        cout << "\nOVERFLOW" << endl;
        return nullptr;
    }
    // Nodo non ancora stato creato
    else if (vertix->at(newNode) == nullptr) {
        node = new GNode<T>;
        node->setData(newNode);

    // Aggiungo il nodo all'insieme dei vertici
        vertix->at(newNode) = node;
    }
    // Nodo giá stato creato
    else {
        node = vertix->at(newNode);
    }
    return node;
}

//usata per sapere il numero dei vertici [in addEdge e BFS]
template<class T>
int RBGraph<T>::VertixNumber() {
    return vertix->size();
}

template<class T>
bool RBGraph<T>::addEdge(T src, T dest) {
    GNode<T> *source = createNewGNode(src);    //creo un nuovo nodo sorgente
    GNode<T> *destNode = createNewGNode(dest);  //creo un nuovo nodo destinazione
    // Se uno dei due é nullo, allora non é possibile aggiungere un arco perché 
    // supererebbe le dimensioni della struttura dati grafo
    if (destNode == nullptr || source == nullptr) {
        cout << "\n[WARNING] Non posso aggiungere il seguente arco (" << src << " " << dest << ")" << endl;
        return false;
    }

    // L'arco esiste giá quindi non viene creato
    if (source->searchNodeInAdiacentList(destNode)){ //si trova nella lista di adiacenza
        cout << "\n[WARNING] Non é possibile creare l'arco (" << src << " " << dest << "), giá esiste."<< endl;
        return false;
    }
    source->addEdge(destNode); //aggiungo arco
    return true;
}

template<class T>
bool RBGraph<T>::removeEdge(T src, T dest) {
    //se esistono src e dest allora li rimuove
    if (findEdge(src, dest)) {
        GNode<T> *destNode = vertix->at(dest);
        GNode<T> *source = vertix->at(src);
        source->removeEdge(destNode);
        return true;
    }
    else { //non esiste l'arco
        cout << "\n[WARNING] Impossibile rimuovere arco (" << src << " " << dest << "): non esiste." << endl;
        return false;
    }
}

template<class T>
bool RBGraph<T>::findEdge(T src, T dest) {
//input negativi
    if (src < 0 || dest < 0) {
        cout << "\n[WARNING] Non posso cercare il seguente arco (" << src << " " << dest << "). Non sono ammessi valori negativi" << endl;
        return false;
    }

    // I nodi superano il numero massimo del grafo [out_of_range]
    if (dest >= vertix->size() || src >= vertix->size()) {
        return false;
    }
  
    // Il nodo dest non si trova nella lista di adiacenza del nodo src
    if (!vertix->at(src)->searchNodeInAdiacentList(vertix->at(dest))) {
        return false;
    }
    return true;
}

template<class T>
void RBGraph<T>::BFS(T source) {
    // Sorgente di dimensione maggiore del numero di vertici del grafo
    if (source >= this->VertixNumber()) {
        cout << "\nLa sorgente é maggiore della dimensione del grafo" << endl;
        return;
    }
    if (source < 0)
    {
        cout << "\nLa sorgente non puó essere un numero negativo" << endl;
        return;
    }

    GNode<T> *src = vertix->at(source);
  
    // Inizializzazione di tutti i vertici - {src}
    for (auto vtx : *vertix) {
        if (vtx != nullptr) {
            vtx->setColor(Colors::WHITE);
            vtx->setDistance(INT_MAX);
            vtx->setParentNode(nullptr);
        }
    }
    // Inizializzazione della sorgente
    src->setColor(Colors::GRAY);
    src->setDistance(0);
    src->setParentNode(nullptr);
    queue<GNode<T> *> Queue; //uso una coda
    Queue.push(src); //enqueue
    while (!Queue.empty()) {
        GNode<T> *u = Queue.front(); 
        Queue.pop(); //dequeue
        cout << u->getData() << " ";
        RBTree<GNode<T> *> *rbTree = u->getAdiacent();
        vector<RBNode<GNode<T> *> *> *adjU = rbTree->getListOfNodes();
        for (auto v : *adjU) { 
            if (v->getKey()->getColor() == Colors::WHITE) {
                v->getKey()->setColor(Colors::GRAY);
                v->getKey()->setDistance(u->getDistance() + 1);
                v->getKey()->setParentNode(u);
                Queue.push(v->getKey()); //enqueue
            }
        }
        u->setColor(Colors::BLACK);
    }
    cout << endl;
}

#endif // RBGRAPH_H
