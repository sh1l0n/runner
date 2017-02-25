#include "structures.hpp"
#include <stdlib.h>
#include <time.h>  
#include <iostream>

int main(const int argv, const char** argc) {

	srand(time(NULL));
	std::cout << "hello\n";
	Runner::BaseStructure* bs = new Runner::Pyramid();

	std::cout << bs << std::endl;

	return 0;
}
