#pragma 

#include <cppconn/sqlstring.h>
#include <vector>

struct RecipeRecord {
	sql::SQLString recipe_name;
	sql::SQLString url;
	sql::SQLString category;
	int prep_time;
	int cook_time;
	int serving_count;
};

struct StepRecord {
	int step_number;
	sql::SQLString instruction;
};

struct RecipeIngredientRecord {
	sql::SQLString ingredient_name;
	double quantity;
	sql::SQLString unit;
};

struct Recipe {
	RecipeRecord recipeRecord;
	std::vector<StepRecord> steps;
	std::vector<RecipeIngredientRecord> ingredients;
};

Recipe getRecipe(sql::SQLString recipe_name);

void insertRecipe(Recipe recipe);

void Mysql_Connection_Tester();
