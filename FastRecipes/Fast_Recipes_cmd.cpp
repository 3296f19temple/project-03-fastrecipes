#include <stdlib.h>
#include <iostream>
#include <vector>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include "Fast_Recipes_cmd.h"
#include "Mysql_Connection.h"
#include "py-sql_adapter.h"

const std::string filename = "../scripts/recipes.dat";

void searchByIngredient() {
	uint64_t recipeNum = 0;
	std::string ingredient;
	std::vector<sql::SQLString> recipes;

	while (recipes.size() == 0) {
		std::cout << "Enter ingredient name or \"cancel\": ";
		std::cin >> ingredient;
		if (ingredient.compare("cancel") == 0) {
			return;
		}
		recipes = getRecipesByIngredient(ingredient.c_str());
		if (recipes.size() == 0) {
			std::cout << "Sorry, no recipes with that ingredient." << std::endl;
		}
	}

	std::cout << "Recipes with " << ingredient << ":" << std::endl;
	for (int i = 0; i < recipes.size(); i++) {
		std::cout << "[" << i + 1 << "] " << recipes[i].c_str() << std::endl;
	}

	while (recipeNum < 1 || recipeNum > recipes.size()) {
		std::cout << "Enter recipe number for full recipe: ";
		std::cin >> recipeNum;
		if (recipeNum < 1 || recipeNum > recipes.size()) {
			std::cout << "Not valid input, try again" << std::endl;
		}
		std::cout << std::endl;
	}
	print_sql_recipe(getRecipe(recipes[recipeNum - 1].c_str()));
}

void Fast_Recipes_cmd::commandLine() {
	int input;
	SQL_recipe sql_recipe;
	while (true) {
		std::cout << "--------------------------" << std::endl;
		std::cout << "[1]\tinsert recipes from file" << std::endl;
		std::cout << "[2]\tget random recipe" << std::endl;
		std::cout << "[3]\tget recipe by ingredient" << std::endl;
		std::cout << "[4]\texit" << std::endl;
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
			sql_recipe = SQL_recipe();
			break;
		case 3:
			searchByIngredient();
			break;
		case 4:
			return;
		default:
			std::cout << "invalid" << std::endl;
		}
	}
}
