// Main.cpp
// created by Matthew Majewski 11/8/2019

#include <iostream>
#include <fstream>

#include "webscrape.h"
#include "Mysql_Connection.h"
#include "py-sql_adapter.h"

int main()
{
	std::string filename = "../scripts/recipes.dat";
	Py_recipe py_recipe{};
	SQL_recipe sql_recipe{};
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Unable to open file " << filename << "\n";
		return 0;
	}
	
	int insertedRecipes = 0;
	while (read_recipe(file, py_recipe)) {
		// do something with recipe object
		// std::cout << "------------------------" << "\n";

		pyToMysqlRecipe(py_recipe, sql_recipe);
		//print_sql_recipe(sql_recipe);
		insertRecipe(sql_recipe);
		sql_recipe = {};
		py_recipe = {};
		if (++insertedRecipes % 100 == 0) {
			std::cout << insertedRecipes << " recipes inserted" << std::endl;
		}
	}
	return 0;
}