#pragma once

#include <cppconn/sqlstring.h>
#include <vector>

class RecipeRecord {
public:
	sql::SQLString recipe_name;
	sql::SQLString url;
	sql::SQLString image_url;
	sql::SQLString category;
	int prep_time;
	int cook_time;
	int serving_count;
};

class StepRecord {
public:
	int step_number;
	sql::SQLString instruction;
};

class RecipeIngredientRecord {
public:
	sql::SQLString ingredient_name;
	double quantity;
	sql::SQLString unit;
};

class SQL_recipe {
public:
	RecipeRecord recipeRecord;
	std::vector<StepRecord> steps;
	std::vector<RecipeIngredientRecord> ingredients;
};

SQL_recipe getRandomRecipe();

SQL_recipe getRecipe(sql::SQLString recipe_name);

void insertRecipe(SQL_recipe recipe);

void print_sql_recipe(SQL_recipe recipe);
