#ifndef RBNODE_H
#define RBNODE_H

enum RBCOLOR{BLACK,RED}; // un nodo deve essere ROSSO o NERO [1 proprietá]
template <class T>
/*Nodo dell'albero Red & Black. */
class RBNode{
	//Attributi del nodo [key, padre, puntatore sx e puntatore dx, colore]
	private:
		T key;
		RBNode<T> *p; //padre
		RBNode<T> *right;
		RBNode<T> *left;
		enum RBCOLOR color;

	//getters and setters
	public:
		//costruttore
		RBNode(): p(nullptr), right(nullptr), left(nullptr){
			color = BLACK;
		}

//// SET
		void setKey(T chiave){
			key = chiave;
		}
		
		void setParent (RBNode<T> *p){
			this -> p = p;
		}

		void setRight(RBNode<T> *right){
            this->right = right;
        }

        void setLeft(RBNode<T> *left){
            this->left = left;
        }

        void setColor(enum RBCOLOR color){
            this->color = color;
  		}
//// GET
		T getKey(){
			return key;
		}

		RBNode<T> *getParent(){
			return p;
		}

		RBNode<T> *getRight(){
            return right;
		}
         
        RBNode<T> *getLeft(){
            return left;
        }

        RBCOLOR getColor(){
            return color;
        }	
};
#endif // RBNODE_H