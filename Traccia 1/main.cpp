#include <iostream>
#include "File.h"
using namespace std;

//Richiamo la funzione start() che si trova in File.h per le operazioni del programma
int main() {
    File avvio; //istanza della classe file 
    avvio.start("inputProf.txt");
    return 0;
}
