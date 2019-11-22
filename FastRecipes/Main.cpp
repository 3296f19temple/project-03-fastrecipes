// Main.cpp
// created by Matthew Majewski 11/8/2019

#include <iostream>
#include <fstream>

#include "webscrape.h"
#include "Mysql_Connection.h"
#include "py-sql_adapter.h"

const std::string filename = "../scripts/recipes.dat";

int main()
{
	int input;
	SQL_recipe sql_recipe;
	while (true) {
		std::cout << "--------------------------" << std::endl;
		std::cout << "[1]\tinsert recipes from file" << std::endl;
		std::cout << "[2]\tget random recipe" << std::endl;
		std::cout << "[3]\texit" << std::endl;
		std::cout << "--------------------------" << std::endl;
		std::cout << "Enter choice: ";
		std::cin >> input;
		std::cout << std::endl;
		switch (input) {
		case 1:
			insertFromDatFile(filename);
			break;
		case 2:
			sql_recipe = getRandomRecipe();
			print_sql_recipe(sql_recipe);
			sql_recipe = {};
			break;
		case 3:
			return 0;
		default:
			std::cout << "invalid" << std::endl;
		}
	}
}