#ifndef GNODE_H
#define GNODE_H

#include <vector>
#include <sstream>
#include "RBTree.h"
using namespace std;

enum class Colors {WHITE,GRAY,BLACK};

//GNode é la classe dei singoli nodi del grafo. 
//Setters and Getters

template <class T>
class GNode {
private:
    T data;
    int dist;
    Colors color;
    GNode<T>* p; //padre
    RBTree<GNode<T>*> *adiacent;

public:
    //costruttore
    GNode() {
        adiacent = new RBTree<GNode<T>*>;
        this -> p = nullptr;
        this -> color = Colors::WHITE;
        this -> dist = INT_MAX;
    }
/// SET
    void setColor(Colors color){
        this -> color = color;
    }

    void setDistance(int dist){
        this -> dist = dist;
    }

    void setData(T data){
        this -> data = data;
    }

    void setParentNode(GNode<T> *p){
        this -> p = p;
    }
/// GET
    Colors getColor(){
        return color;
    }

    int getDistance(){
        return dist;
    }
  
    T getData(){
        return data;
    }   
  
    RBTree<GNode<T> *> *getAdiacent(){
        return adiacent;
    }

///Stampa lista di adiacenza
    string AdiacentPrint(){
        stringstream adj("", ios::app | ios::out);
        for (auto node : *adiacent -> getListOfNodes()) {
            adj << this -> getData() << " ~~> " << node->getKey()->getData() << "\n";
        }
        return adj.str();
    }

    bool searchNodeInAdiacentList(GNode<T> *node){
        if(adiacent -> findNode(node))
            return true;
        return false;
    }

    void removeEdge(GNode<T> *node){
        adiacent->deleteNode(node);
    }

    void addEdge(GNode<T> *node){
        adiacent->insertNode(node);
    }
};


#endif // GNODE_H


