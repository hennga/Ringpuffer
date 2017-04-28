#include <iostream>
#include <vector>
#include <string>
#include "Menue.h"
#include "Ringpuffer.h"

int main() {
   Ringpuffer Puffer;
   Menue m1;
   
    (Puffer.getAnzahlGenutzteNodes()==0)?:
	std::cout <<"Das Backup-System ist leer, bitte fuegen sie ein Backup hinzu",
	m1.showSelectionMenue();
   
   m1.callRingpufferMethods(m1.readUserInput(),Puffer);
   
   


}