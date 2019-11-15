#pragma 

#include <cppconn/sqlstring.h>

struct Recipe {
	sql::SQLString recipe_name;
	sql::SQLString url;
	sql::SQLString category;
	int prep_time;
	int cook_time;
	int serving_count;
};

struct step {
	std::string instruction;
	int step_number;
};

int getRecipe(sql::SQLString rname);

int insertRecipe(Recipe recipe);

void Mysql_Connection_Tester();
