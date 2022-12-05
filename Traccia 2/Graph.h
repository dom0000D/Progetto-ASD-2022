#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
#include <vector>
#include "GNode.h"
#include "Edge.h"
#include "DisjointSet.h"
using namespace std;

//La classe Graph incapsula la struttura Grafo. All'interno abbiamo l'algoritmo di Kruskal e l'algoritmo che calcola il secondo MST migliore. 
template <class T>
class Graph {
private:
    vector <GNode<T> *> *vertix;
    vector <Edge<T>> edges;
    GNode <T> *createNewGNode(T data);

public:
    Graph(int vertix, int edges);
    bool addEdge(T src, T dest, int weight);
    void insertEdgeWeighted(GNode<T> *src, GNode<T> *dest, int weight);
    vector <Edge<T>> Kruskal(T &weight);
    void searchBestMST();
    void StampaMST(vector<Edge<T>> MST, T firstMSTweight);
    void Stampa2BestMST(vector<Edge<T>> SecondMST, T secondMSTweight);
    int VertixNumber();
};

template<class T>
Graph<T>::Graph(int vertix, int edges) {
    this->vertix = new vector<GNode<T> *>(vertix + 1);
}

template<class T>
GNode<T> *Graph<T>::createNewGNode(T newNode) {
    GNode<T> *node;
    // Il nodo non puó essere creato poiché supera il size del numero dei vertici
    if (newNode >= vertix->size()) { 
        cout <<"\nOVERFLOW: la dimensione del nodo e' maggiore del numero dei vertici" << endl;
        exit(0);
    }
    // Nodo non ancora stato creato
    else if (vertix->at(newNode) == nullptr) {
        node = new GNode<T>;
        node->setData(newNode);
    // Aggiungo il nodo all'insieme dei vertici
        vertix->at(newNode) = node;
    }
    // Nodo è già stato creato
    else {
        node = vertix->at(newNode);
    }
    return node;
}

template<class T>
int Graph<T>::VertixNumber() {
    return vertix->size();
}

template<class T>
bool Graph<T>::addEdge(T src, T dest, int weight) {
    GNode<T> *source = createNewGNode(src);    //creo un nuovo nodo sorgente
    GNode<T> *destNode = createNewGNode(dest); //creo un nuovo nodo destinazione

    // L'arco esiste giá quindi non viene creato
    if (source->searchNodeInAdiacentList(destNode)) {
        cout << "\n[WARNING] Non e' possibile aggiungere l'arco (" << src << " " << dest << "), gia' esiste."<< endl;
        return false;
    }
    // Controlla se il peso dell'arco é maggiore del massimo stabilito
    if (weight < 1 || weight >= 10000) {
        cout << "\n[WARNING] Non e' possibile aggiungere l'arco (" << src << " " << dest << ") perche' il suo peso non rispetta la soglia stabilita di [0 <= PESO <= 10000]"<< endl;
        return false;
    }
    source->addEdge(destNode);
    destNode->addEdge(source);
    insertEdgeWeighted(source, destNode, weight); //aggiungo i nodi + il peso alla lista degli archi
    return true;
}

template<class T>
void Graph<T>::insertEdgeWeighted(GNode<T> *src, GNode<T> *dest, int weight) {
    Edge<T> edge(weight, src, dest);
    edges.push_back(edge);
}

template<class T>
void Graph<T>::StampaMST(vector<Edge<T>> MST, T firstMSTweight) {
    cout << "\n\tPeso Primo MST = " << firstMSTweight << endl;
    for (auto edge : MST) {
        cout <<"\t"<< edge.getSource()->getData() << " ~~> " << edge.getDest()->getData() << " ~~> "<< edge.getWeight() << "   " << endl;
    }
    cout << endl;
}

template<class T>
void Graph<T>::Stampa2BestMST(vector<Edge<T>> SecondMST, T secondMSTweight) {
    cout << "\n\tPeso Secondo Miglior MST = " << secondMSTweight << endl;
    for (auto edge : SecondMST) {
        cout <<"\t"<< edge.getSource()->getData() << " ~~> " << edge.getDest()->getData() << " ~~> "<< edge.getWeight() << "   " << endl;
    }
    cout << endl;
}

template<class T>
vector<Edge<T>> Graph<T>::Kruskal(T &w) {
    w = 0;
    DisjointSet<GNode<T> *> disjointSet;
    vector<Edge<T>> A; 
    for (auto v : *vertix) {
        disjointSet.makeSet(v);
    }
    sort(edges.begin(), edges.end());
    for (auto uv : edges) {
        if (disjointSet.findSet(uv.getSource()) != disjointSet.findSet(uv.getDest())) {
            A.push_back(uv);
            w += uv.getWeight();
            disjointSet.Union(uv.getSource(), uv.getDest());
        }
    }
    return A;
}

template<class T>
void Graph<T>::searchBestMST() {
    vector<Edge<T>> MST1, MST2, tmpMST;
    
    int firstMSTweight = 0;
    int secondMSTweight = INT_MAX;
    int tempMSTweight = 0;

    MST1 = Kruskal(firstMSTweight);
    if (firstMSTweight < 0)
    {
        cout << "Errore nel calcolo del MST" << endl;
        exit(0);
    }
    StampaMST(MST1, firstMSTweight);

// per ogni arco del MST, escluderlo temporaneamente
// ricalcolare MST ogni volta
// ricercare il minimo
// riaggiungere l'arco eliminato in precedenza    

   for (auto uv : MST1) {
       auto temp = uv;
       edges.erase(remove(edges.begin(), edges.end(), uv));
       tmpMST.clear();
       tmpMST = Kruskal(tempMSTweight);
       if (tempMSTweight < secondMSTweight) {
           secondMSTweight = tempMSTweight;
           MST2 = tmpMST;
        }
        edges.push_back(temp);
    }
    if (secondMSTweight < 0)
    {
        cout << "Errore nel calcolo del secondo MST" << endl;
        exit(0);
    }
    Stampa2BestMST(MST2, secondMSTweight);
}

#endif // GRAPH_H
