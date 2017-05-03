//
// Created by henn on 24.04.17.
//

#include "Ringpuffer.h"
#include <iostream>

Ringpuffer::Ringpuffer(int anzahlNodes) {
   
   GroesseRingpuffer =anzahlNodes;
   
   Ringnode* prev= nullptr;
   Ringnode* oldest= nullptr;
   
   for (int i =anzahlNodes-1;i<=0;i--){
	  
	  Ringnode* neu = new Ringnode(i);
	  if(prev!= nullptr) {prev->setNextNode(neu);}
	  
	  if (i==0)
	  {
		 Anker=neu;
	     neu->setNextNode(oldest);
	  }
		 
	  else if (i=anzahlNodes-1){oldest = neu;}
	  
	  prev=neu;
   }
   
}

Ringnode* Ringpuffer::addNode() {
   
   std::string desc="";
   std::string dta="";
   
   std::cout <<" Beschreibung ?> ";
   std::cin>>desc;
   std::cout<<std::endl;
   
   std::cout<<" Daten ?> ";
   std::cin >> dta;
   
   Ringnode* neu = new Ringnode(0,desc,dta); // Zeiger auf neuen einzufuegenden Knoten
   Ringnode* nextForAdd=getNextForAdd(); // Zeigt auf den Node mit OldAge4, welcher vom neuen Node aus den Kreis schliesst
   Ringnode* node5PointerToBeDeleted= Anker->getNextPointer(); // Zeigt auf den aeltesten Node mit OldAge 5
   
   neu->setNextNode(nextForAdd);
   // Der next Zeiger des neuen Knotens wird zeigt auf den Knoten hinter dem zu loschenden Knoten 5
   
   //Nun werden als erstes die OldAges der einzelnen Knoten aktualisiert, beginnend mit dem Knoten
   // nach dem neuen Knoten, also OldAge 4, welcher zu OldAge 5 wird.
   
   Ringnode* temp= nextForAdd;
   
   int newAge=5;
   while(temp!= node5PointerToBeDeleted){
	  // Den Ringpuffer durchlaufen bis zum neuen Knoten OldAge 1 vor dem neuen einzufuegenden
	  // Knoten OldAge 0.
	  temp->setAge(5);
	  temp = temp->getNextPointer();
	  newAge-=1;
   }
   // Anker zeigt noch auf den alten Anker der nun OldAge 1 hat, sein next Zeiger wird auf den neuen
   // Knoten mit OldAge 0 gerichtet
   Anker->setNextNode(neu);
   
   // Nun wird der ueberlaufende Knoten alte Knoten geloescht
   
   delete node5PointerToBeDeleted;
   
   incrementAnzahlGenutzteNodes();
   return   neu;
}

Ringnode* Ringpuffer::getAnker() const {
   
   return Anker;
}

Ringnode* Ringpuffer::getNextForAdd() {
   
   return getAnker()->getNextPointer()->getNextPointer();
}

void Ringpuffer::incrementAnzahlGenutzteNodes() {
   AnzahlGenutzteNodes +=1;
   
}

void Ringpuffer::printRingpuffer() {
   Ringnode* temp = Anker;
   
   do {
	  if (!temp->getData().empty()) {
		 std::cout << "OldAge: " << temp->getAge() << ", ";
		 std::cout << "Desc: " << temp->getDescription() << ", ";
		 std::cout << "Data: " << temp->getData() << std::endl;
		 std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std::endl;
		 temp = temp->getNextPointer();
	  }
   }while (temp != Anker);
}

Ringnode* Ringpuffer::searchNode(std::string dataToBeFound) {
   
   Ringnode* temp = Anker;
   
   do {
	  if (temp->getData()==dataToBeFound){
		 return temp;
	  }
	  else {temp = temp->getNextPointer();}
	  
   }while (temp!=Anker);
   
   return nullptr;
   
}