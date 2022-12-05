#ifndef RBTREE_H
#define RBTREE_H
#include "RBNode.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
//[Pseudocodici delle slide]
//Classe templata di un albero Red & Black
template <class T>
class RBTree {
private:
    RBNode<T> *root;
    RBNode<T> *null = new RBNode<T>;
    vector<RBNode<T> *> *ListofNodes;

    void RB_Insert(RBNode<T> *z);
    void RB_Delete_Fixup(RBNode<T> *z);
    void RBTransplant(RBNode<T> *u, RBNode<T> *v);
    void Right_Rotate(RBNode<T> *x);
    void Left_Rotate(RBNode<T> *x);
    void RB_Delete(RBNode<T> *z);
    void deleteNodebyListofNodes(RBNode<T> *z);

protected:
    RBNode<T> *createNewNode(T key);

public:
    RBTree();
    RBNode<T> *treeMinimum(RBNode<T> *x);
    RBNode<T> *treeMaximum(RBNode<T> *x);
    RBNode<T> *searchNodeIterative(T key);
    bool findNode(T key);
    void insertNode(T key);
    bool deleteNode(T key);
    vector<RBNode<T> *> *getListOfNodes();
};

template<class T>
RBTree<T>::RBTree() {
    ListofNodes = new vector<RBNode<T> *>;
    root = null;
}

template<class T>
void RBTree<T>::RB_Insert(RBNode<T> *x) {
    x -> setColor(RED);
    while (x->getParent()->getColor() == RED) {
        if (x->getParent() == x->getParent()->getParent()->getLeft()) {
            RBNode<T> *y = x->getParent()->getParent()->getRight();
            // Case 1
            if (y->getColor() == RED) {
                x->getParent()->setColor(BLACK);                                    
                y->setColor(BLACK);                                                 
                x->getParent()->getParent()->setColor(RED);                         
                x = x->getParent()->getParent();                                    
            }
            //Case 2
            else {
                if (x == x->getParent()->getRight()) {
                    x = x->getParent();                                             
                    Left_Rotate(x);                                                  
                }
                // Case 3
                x->getParent()->setColor(BLACK);                                    
                x->getParent()->getParent()->setColor(RED);                         
                Right_Rotate(x->getParent()->getParent());                           
            }
        }
        else {
            RBNode<T> *y = x->getParent()->getParent()->getLeft();
            // Case 4
            if (y->getColor() == RED) {
                x->getParent()->setColor(BLACK);                                    
                y->setColor(BLACK);                                                 
                x->getParent()->getParent()->setColor(RED);                         
                x = x->getParent()->getParent();                                    
            }
            else {
                // Case 5
                if (x == x->getParent()->getLeft()) {
                    x = x->getParent();                                            
                    Right_Rotate(x);                                                 
                }
                // Case 6
                x->getParent()->setColor(BLACK);                                    
                x->getParent()->getParent()->setColor(RED);                      
                Left_Rotate(x->getParent()->getParent());                            
            }
        }
    }
    root->setColor(BLACK);
}

template<class T>
void RBTree<T>::RB_Delete_Fixup(RBNode<T> *x) {
    while (x != root && x->getColor() == BLACK) {
        if (x == x->getParent()->getLeft()) {
            RBNode<T> *w = x->getParent()->getRight();
            // Case 1
            if (w->getColor() == RED) {
                w->setColor(BLACK);
                x->getParent()->setColor(RED);
                Left_Rotate(x->getParent());
                w = x->getParent()->getRight();
            }
            // Case 2
            if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK) {
                w->setColor(RED);
                x = x->getParent();
            }
            else {
                // Case 3
                if (w->getRight()->getColor() == BLACK) {
                    w->getLeft()->setColor(BLACK);
                    w->setColor(RED);
                    Right_Rotate(w);
                    w = x->getParent()->getRight();
                }
                // Case 4
                w->setColor(x->getParent()->getColor());
                x->getParent()->setColor(BLACK);
                w->getRight()->setColor(BLACK);
                Left_Rotate(x->getParent());
                x = root;
            }
        }
        else {
            RBNode<T> *w = x->getParent()->getLeft();
            // Case 1
            if (w->getColor() == RED) {
                w->setColor(BLACK);
                x->getParent()->setColor(RED);
                Right_Rotate(x->getParent());
                w = x->getParent()->getLeft();
            }
            // Case 2
            if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK) {
                w->setColor(RED);
                x = x->getParent();
            }
            else {
                // Case 3
                if (w->getLeft()->getColor() == BLACK) {
                    w->getRight()->setColor(BLACK);
                    w->setColor(RED);
                    Left_Rotate(w);
                    w = x->getParent()->getLeft();
                }
                // Case 4
                w->setColor(x->getParent()->getColor());
                x->getParent()->setColor(BLACK);
                w->getLeft()->setColor(BLACK);
                Right_Rotate(x->getParent());
                x = root;
            }
        }
    }
    x->setColor(BLACK);
}

template<class T>
void RBTree<T>::RBTransplant(RBNode<T> *u, RBNode<T> *v) {
    if (u->getParent() == null) {
        root = v;
    }
    else if (u == u->getParent()->getLeft()) {
        u->getParent()->setLeft(v);
    }
    else {
        u->getParent()->setRight(v);
    }
    v->setParent(u->getParent());
}

template<class T>
void RBTree<T>::RB_Delete(RBNode<T> *z) {
    RBNode<T> *x;
    RBNode<T> *y = z;
    enum RBCOLOR y_orig_color = y->getColor();
    if (z->getLeft() == null) {
        x = z->getRight();
        RBTransplant(z, z->getRight());
    }
    else if (z->getRight() == null) {
        x = z->getLeft();
        RBTransplant(z, z->getLeft());
    }
    else {
        y = treeMinimum(z->getRight());
        y_orig_color = y->getColor();
        x = y->getRight();
        if (y->getParent() == z) {
            x->setParent(y);
        }
        else {
            RBTransplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }
        RBTransplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
        y->setColor(z->getColor());
    }
    deleteNodebyListofNodes(z); //elimina il nodo dalla lista [serve per stampa del grafo, bfs e altro]
    delete z; //elimino il puntatore

    if (y_orig_color == BLACK) {
        RB_Delete_Fixup(x);
    }
}

template<class T>
void RBTree<T>::Right_Rotate(RBNode<T> *x) {
    RBNode<T> *y = x->getLeft();
    x->setLeft(y->getRight());
    if (y->getRight() != null) {
        y->getRight()->setParent(y);
    }
    y->setParent(x->getParent());
    if (x->getParent() == null) {
        root = y;
    }
    else if (x->getParent()->getRight() == x) {
        x->getParent()->setRight(y);
    }
    else {
        x->getParent()->setLeft(y);
    }
    y->setRight(x);
    x->setParent(y);
}

template<class T>
void RBTree<T>::Left_Rotate(RBNode<T> *x) {
    RBNode<T> *y = x->getRight();
    x->setRight(y->getLeft());
    if (y->getLeft() != null) {
        y->getLeft()->setParent(y);
    }
    y->setParent(x->getParent());
    if (x->getParent() == null) {
        root = y;
    }
    else if (x->getParent()->getLeft() == x) {
        x->getParent()->setLeft(y);
    }
    else {
        x->getParent()->setRight(y);
    }
    y->setLeft(x);
    x->setParent(y);
}

//Metodo che effettua la creazione e inizializza un nodo
template<class T>
RBNode<T> *RBTree<T>::createNewNode(T key) {
    RBNode<T> *x = new RBNode<T>;
    x->setKey(key);
    x->setRight(null);
    x->setLeft(null);
    return x;
}

//Ritorna il valore minimo dell'albero red black [complessitá O(h) dove h é altezza dell'albero]
template<class T>
RBNode<T> *RBTree<T>::treeMinimum(RBNode<T> *x) {
    while (x->getLeft() != null) {
        x = x->getLeft();
    }
    return x;
}

//Ritorna il massimo valore dell'albero red black [complessitá O(h) dove h é altezza dell'albero]
template<class T>
RBNode<T> *RBTree<T>::treeMaximum(RBNode<T> *x) {
    while (x->getRight() != null) {
        x = x->getRight();
    }
    return x;
}

//Ricerca di un nodo nell'albero Red & Black. Ritorna il nodo cercato se esiste
template<class T>
RBNode<T> *RBTree<T>::searchNodeIterative(T key) {
    RBNode<T> *x = root;
    while (x != null && x->getKey() != key) {
        if (key < x->getKey()) {
            x = x->getLeft();
        }
        else {
            x = x->getRight();
        }
    }
    return x;
}


// Inserisce un nodo nell'albero Red & Black
template<class T>
void RBTree<T>::insertNode(T key) {
    RBNode<T> *z = createNewNode(key);
    RBNode<T> *y = null;
    RBNode<T> *x = root;
    while (x != null) {
        y = x;
        if (z->getKey() < x->getKey()) {
            x = x->getLeft();
        }
        else {
            x = x->getRight();
        }
    }
    z->setParent(y);
    if (y == null) {
        root = z;
    }
    else if (z->getKey() < y->getKey()) {
        y->setLeft(z);
    }
    else {
        y->setRight(z);
    }
    ListofNodes->push_back(z);
    RB_Insert(z);
}

// Effettua la cancellazione di un dato nodo. Verifica se il nodo esiste, poi effettua l'eliminazione  
template<class T>
bool RBTree<T>::deleteNode(T key) {
    RBNode<T> *z = searchNodeIterative(key);
    // Nodo non trovato
    if (z == null) 
        return false;
    else
        RB_Delete(z);
    return true;
}

template<class T>
void RBTree<T>::deleteNodebyListofNodes(RBNode<T> *z) {
    for (int i = 0; i < ListofNodes->size(); i++) {
        RBNode<T> *node = ListofNodes->at(i);
        if (node->getKey() == z->getKey()) {
            ListofNodes->erase(ListofNodes->begin() + i);
            break;
        }
    }
}

//Restituisce una lista con tutti i nodi che sono nell'albero Red & Black
template<class T>
vector<RBNode<T> *> *RBTree<T>::getListOfNodes() {
    return ListofNodes;
}

// Ricerca di un nodo: return true se il nodo si trova nell'albero, false altrimenti
template<class T>
bool RBTree<T>::findNode(T key) {
    if (searchNodeIterative(key) != null)
        return true;
    else 
        return false;
}

#endif // RBTREE_H
