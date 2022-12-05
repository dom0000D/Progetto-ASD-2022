#ifndef EDGE_H
#define EDGE_H

// Edge rappresenta gli archi del grafo.
using namespace std;

template <class T>
class Edge {
private:
    GNode<T> *source;
    GNode<T> *dest;
    int weight;
public:
    Edge(int weight, GNode<T> *source, GNode<T> *dest) {
        this->weight = weight;
        this->source = source;
        this->dest = dest;
    }
/// GET
    int getWeight() const {
        return weight;
    }  
      
    GNode<T> *getSource() const {
        return source;
    }

    GNode<T> *getDest() const {
        return dest;
    }


///Overload di = in supporto a erase::STL
    friend bool operator== (const Edge<T> &edge1, const Edge<T> &edge2) {
        if((edge1.getSource() == edge2.getSource()) && (edge1.getDest() == edge2.getDest())) 
            return true;
        else return false;
    }


///Overload di < in supporto a sort::STL 
    friend bool operator< (const Edge<T> &edge1, const Edge<T> &edge2) {
        if (edge1.getWeight() < edge2.getWeight()) return true;
        else return false;
    }
};
#endif // EDGE_H
