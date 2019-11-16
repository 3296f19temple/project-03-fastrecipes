#pragma 

#include <cppconn/sqlstring.h>
#include <vector>

struct Recipe_Table {
	sql::SQLString recipe_name;
	sql::SQLString url;
	sql::SQLString category;
	int prep_time;
	int cook_time;
	int serving_count;
};

struct Step_Table {
	int step_number;
	sql::SQLString instruction;
};

struct Recipe_Ingredient_Table {
	sql::SQLString ingredient_name;
	int quantity;
	sql::SQLString unit;
};

struct Recipe {
	Recipe_Table recipe;
	std::vector<Step_Table> steps;
	std::vector<Recipe_Ingredient_Table> ingredients;
};

void insertRecipe(Recipe recipe);

void Mysql_Connection_Tester();
