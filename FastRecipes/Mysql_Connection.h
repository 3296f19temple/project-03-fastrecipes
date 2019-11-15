#pragma 

#include <cppconn/sqlstring.h>
#include <vector>

struct FullRecipe {
	Recipe_Table recipe;
	std::vector<Step_Table> steps;
	std::vector<Ingredient> ingredients;
};

struct Recipe_Table {
	sql::SQLString recipe_name;
	sql::SQLString url;
	sql::SQLString category;
	int prep_time;
	int cook_time;
	int serving_count;
};

struct Step_Table {
	sql::SQLString instruction;
	int step_number;
	sql::SQLString ingredient_unit;
};

struct Ingredient {
	sql::SQLString ingredient_name;
	int quantity;
};

int getRecipe(sql::SQLString rname);

int insertRecipe(Recipe_Table recipe);

int insertIngredient(sql::SQLString ingredient);

void Mysql_Connection_Tester();
