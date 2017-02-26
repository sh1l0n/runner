#include "structures.hpp"
#include <stdlib.h>
#include <time.h>  
#include <iostream>

int main(const int argv, const char** argc) {

	srand(time(NULL));
	
	Structures::BaseStructure* bs = Structures::getStructureMatrix();

	if(bs!=NULL) {
		std::cout << bs->toString() << std::endl;
	}
	else {
		std::cout << "Structure it's null\n";
	}

	return 0;
}
