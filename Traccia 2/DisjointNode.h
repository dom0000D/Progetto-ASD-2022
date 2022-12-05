#ifndef DISJNODE_H
#define DISJNODE_H

//Nodo dell'insieme disgiunto
using namespace std;

template <class T>
class DisjNode {
private:
    T data;
    DisjNode<T> *p; //padre
    int rank;

public:
    //costruttore
    DisjNode(T data) {
        this->data = data;
    }
/// SET
    void setParentDisjNode(DisjNode<T> *p){ 
        this -> p = p; 
    }

    void setRank(int rank){ 
        this->rank = rank;
    }
/// GET
    T getData() {
        return data;
    }

    DisjNode<T> *getParent() {
        return p;
    }

    int getRank() {
        return rank;
    }
};

#endif // DISJNODE_H 
