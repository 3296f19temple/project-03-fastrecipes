// Main.cpp
// created by Matthew Majewski 11/8/2019

#include <iostream>
#include <fstream>
#include "webscrape.h"

int main()
{
    std::cout << "Hello World!\n";
	std::string filename = "../scripts/recipes.dat";
	Py_recipe recipe{};
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Unable to open file " << filename << "\n";
		return 0;
	}
	while (read_recipe(file, recipe)) {
		// do something with recipe object
		print_py_recipe(recipe);
		std::cout << "------------------------" << "\n";
		recipe = Py_recipe();
	}
	return 0;
}