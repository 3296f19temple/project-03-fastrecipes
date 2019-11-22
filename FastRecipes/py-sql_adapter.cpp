#include <iostream>
#include <fstream>

#include "py-sql_adapter.h"

void pyToMysqlRecipe(Py_recipe& py_recipe, SQL_recipe& sql_recipe) {
	sql_recipe.recipeRecord.recipe_name = py_recipe.name.c_str();
	sql_recipe.recipeRecord.url = py_recipe.url.c_str();
	sql_recipe.recipeRecord.image_url = py_recipe.img_url.c_str();
	sql_recipe.recipeRecord.category = py_recipe.category.c_str();
	sql_recipe.recipeRecord.prep_time = py_recipe.prep_time;
	sql_recipe.recipeRecord.cook_time = py_recipe.cook_time;
	sql_recipe.recipeRecord.serving_count = py_recipe.num_servings;

	for (int i = 0; i < py_recipe.instructions.size(); i++) {
		StepRecord sqlInstruction{};
		sqlInstruction.step_number = i + 1;
		sqlInstruction.instruction = py_recipe.instructions.at(i).c_str();
		sql_recipe.steps.push_back(sqlInstruction);
	}

	for (Py_ingredient& py_ingredient : py_recipe.ingredients) {
		RecipeIngredientRecord sqlIngredient{};
		sqlIngredient.ingredient_name = py_ingredient.name.c_str();
		try {
			sqlIngredient.quantity = std::stod(py_ingredient.amount);
		}
		catch (std::invalid_argument e) {
			sqlIngredient.quantity = -1;
		}
		sqlIngredient.unit = py_ingredient.unit.c_str();
		sql_recipe.ingredients.push_back(sqlIngredient);
	}
}

void insertFromDatFile(std::string filename) {
	Py_recipe py_recipe{};
	SQL_recipe sql_recipe{};
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Unable to open file " << filename << "\n";
		return;
	}

	int insertCount = 0;
	while (read_recipe(file, py_recipe)) {
		pyToMysqlRecipe(py_recipe, sql_recipe);
		insertRecipe(sql_recipe);
		sql_recipe = {};
		py_recipe = {};
		if (++insertCount % 10 == 0) {
			std::cout << insertCount << " recipes inserted" << std::endl;
		}
	}
}

