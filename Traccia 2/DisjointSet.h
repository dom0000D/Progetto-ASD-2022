#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>
#include <vector>
#include "DisjointNode.h"
using namespace std;

// Insieme disgiunti, utilizza DisjointNode che é un'istanza di un singolo nodo dell'insieme disgiunto.
template <class T>
class DisjointSet {
private:
    vector<DisjNode<T> *> vertix;
    
    DisjNode<T> *findSetHelper(DisjNode<T> *X) {
        if (X != X->getParent()) {
            X->setParentDisjNode(findSetHelper(X->getParent()));
        }
        return X->getParent();
    }

    public:
    void makeSet(T x) {
        DisjNode<T> *X = new DisjNode<T>(x);
        vertix.push_back(X);
        X->setParentDisjNode(X);
        X->setRank(0);
    }

    DisjNode<T> *findSet(T x) {
        DisjNode<T> *X;
        for (auto node : vertix) {
            if (node->getData() == x) {
                X = node;
                break;
            }
        }
        return findSetHelper(X);
    }

    void Link(DisjNode<T> *x, DisjNode<T> *y) {
        if (x->getRank() > y->getRank())
            y->setParentDisjNode(x);
        else {
            x->setParentDisjNode(y);
            if (x->getRank() == y->getRank()) {
            x->setRank(x->getRank()+1);
            }
        }
    }

    void Union(T u, T v) {
        Link(findSet(u), findSet(v));
    }
};


#endif // DISJOINTSET_H
