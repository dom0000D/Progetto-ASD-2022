#ifndef GNODE_H
#define GNODE_H

#include <vector>
#include <sstream>
#include <list>
using namespace std;

//GNode é la classe dei singoli nodi del grafo. 
//Setters and Getters
template <class T>
class GNode {
private:
    T data;
    GNode<T>* p;
    list<GNode<T> *> *adiacent;

public:
    //costruttore    
    GNode() {
        adiacent = new list<GNode<T> *>;
        this->p = nullptr;
    }
/// SET
    void setData(T data) {
        this->data = data;
    }

/// GET
    T getData() {
        return data;
    }

    void addEdge(GNode<T> *node) {
        adiacent->push_back(node);
    }

    void removeEdge(GNode<T> *node) {
        adiacent->remove(node);
    }

    bool searchNodeInAdiacentList(GNode<T> *node) {
        for (auto vertex : *adiacent) {
            if (vertex->getData() == node->getData())
                return true;
        }
        return false;
    }
};

#endif // GNODE_H 
