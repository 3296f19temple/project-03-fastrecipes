#include <stdlib.h>
#include <iostream>
#include <vector>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include "Mysql_Connection.h"

const sql::SQLString server = "localhost:3306";
const sql::SQLString user = "root";
const sql::SQLString password = "password";
const sql::SQLString schema = "fast_recipes";

using namespace std;

RecipeRecord getRecipeRecord(sql::SQLString recipe_name) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = nullptr;
	RecipeRecord recipeRecord;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL get_recipe_record(?)");
		recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe_name);

		res = pstmt->executeQuery();
		while (res->next()) {
			recipeRecord.recipe_name = res->getString("recipe_name");
			recipeRecord.url = res->getString("url");
			recipeRecord.category = res->getString("category");
			recipeRecord.prep_time = res->getInt("prep_time");
			recipeRecord.cook_time = res->getInt("cook_time");
			recipeRecord.serving_count = res->getInt("serving_count");
		}
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete res;
	delete pstmt;
	delete con;
	return recipeRecord;
}

vector<StepRecord> getStepRecords(sql::SQLString recipe_name) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = nullptr;
	vector<StepRecord> steps;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL get_step_records(?)");
		recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe_name);

		res = pstmt->executeQuery();
		while (res->next()) {
			steps.push_back({ res->getInt("step_number"), res->getString("instruction") });
		}
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete res;
	delete pstmt;
	delete con;
	return steps;
}

vector<RecipeIngredientRecord> getIngredientRecords(sql::SQLString recipe_name) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = nullptr;
	vector<RecipeIngredientRecord> ingredients;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL get_ingredient_records(?)");
		recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe_name);

		res = pstmt->executeQuery();
		while (res->next()) {
			ingredients.push_back({ res->getString("ingredient_name"), (double)res->getDouble("quantity"), res->getString("unit") });
		}
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete res;
	delete pstmt;
	delete con;
	return ingredients;
}

void insertRecipeRecord(RecipeRecord recipe) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL insert_recipe(?,?,?,?,?,?,?)");
		recipe.recipe_name.find("n/a") != std::string::npos ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe.recipe_name);
		recipe.url.find("n/a") != std::string::npos ?
			pstmt->setNull(2, sql::DataType::VARCHAR) :
			pstmt->setString(2, recipe.url);
		recipe.image_url.find("n/a") != std::string::npos ?
			pstmt->setNull(3, sql::DataType::VARCHAR) :
			pstmt->setString(3, recipe.image_url);
		recipe.category.find("n/a") != std::string::npos ?
			pstmt->setNull(4, sql::DataType::VARCHAR) :
			pstmt->setString(4, recipe.category);
		recipe.prep_time == -1 ?
			pstmt->setNull(5, sql::DataType::INTEGER) :
			pstmt->setInt(5, recipe.prep_time);
		recipe.cook_time == -1 ?
			pstmt->setNull(6, sql::DataType::INTEGER) :
			pstmt->setInt(6, recipe.cook_time);
		recipe.serving_count == -1 ?
			pstmt->setNull(7, sql::DataType::INTEGER) :
			pstmt->setInt(7, recipe.serving_count);

		pstmt->execute();
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete pstmt;
	delete con;
}

void insertStepRecords(sql::SQLString recipe_name, vector<StepRecord> steps) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL insert_step(?,?,?)");
		for (StepRecord step : steps) {
			recipe_name.find("n/a") != std::string::npos ?
				pstmt->setNull(1, sql::DataType::VARCHAR) :
				pstmt->setString(1, recipe_name);
			step.step_number == -1 ?
				pstmt->setNull(2, sql::DataType::INTEGER) :
				pstmt->setInt(2, step.step_number);
			step.instruction.find("n/a") != std::string::npos ?
				pstmt->setNull(3, sql::DataType::VARCHAR) :
				pstmt->setString(3, step.instruction);
			pstmt->execute();
		}

	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete pstmt;
	delete con;
}

void insertIngredientRecords(sql::SQLString recipe_name, vector<RecipeIngredientRecord> ingredients) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL insert_ingredient(?,?,?,?)");
		for (RecipeIngredientRecord ingredient : ingredients) {
			recipe_name.find("n/a") != std::string::npos ?
				pstmt->setNull(1, sql::DataType::VARCHAR) :
				pstmt->setString(1, recipe_name);
			ingredient.ingredient_name.find("n/a") != std::string::npos ?
				pstmt->setNull(2, sql::DataType::VARCHAR) :
				pstmt->setString(2, ingredient.ingredient_name);
			ingredient.quantity == -1 ?
				pstmt->setNull(3, sql::DataType::DOUBLE) :
				pstmt->setDouble(3, ingredient.quantity);
			ingredient.unit.find("n/a") != std::string::npos ?
				pstmt->setNull(4, sql::DataType::VARCHAR) :
				pstmt->setString(4, ingredient.unit);
			pstmt->execute();
		}
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete pstmt;
	delete con;
}

sql::SQLString getRandomRecipeName() {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = nullptr;
	sql::SQLString recipe_name;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL get_random_recipe()");
		res = pstmt->executeQuery();
		while (res->next()) {
			recipe_name = res->getString("recipe_name");
		}
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete res;
	delete pstmt;
	delete con;
	return recipe_name;
}

SQL_recipe getRandomRecipe() {
	sql::SQLString recipe_name;
	SQL_recipe sql_recipe{};

	recipe_name = getRandomRecipeName();
	sql_recipe = getRecipe(recipe_name);
	return sql_recipe;
}

vector<sql::SQLString> getRecipesByIngredient(sql::SQLString ingredient) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = nullptr;
	vector<sql::SQLString> recipeNames;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL get_recipes_by_ingredient(?)");
		ingredient.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, ingredient);

		res = pstmt->executeQuery();
		while (res->next()) {
			recipeNames.push_back(res->getString(1).c_str());
		}
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete res;
	delete pstmt;
	delete con;
	return recipeNames;
}

SQL_recipe getRecipe(sql::SQLString recipe_name) {
	SQL_recipe recipe;
	recipe.recipeRecord = getRecipeRecord(recipe_name);
	recipe.steps = getStepRecords(recipe_name);
	recipe.ingredients = getIngredientRecords(recipe_name);
	return recipe;
}

void insertRecipe(SQL_recipe recipe) {
	insertRecipeRecord(recipe.recipeRecord);
	insertStepRecords(recipe.recipeRecord.recipe_name, recipe.steps);
	insertIngredientRecords(recipe.recipeRecord.recipe_name, recipe.ingredients);
}

void deleteRecipe(sql::SQLString recipe_name) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL delete_recipe(?)");
		recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe_name);

		pstmt->execute();
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
	}
	delete pstmt;
	delete con;
}

void print_sql_recipe(SQL_recipe recipe) {
	std::cout << "--------------------------" << std::endl;
	cout << "NAME: " << recipe.recipeRecord.recipe_name.c_str() << endl;
	cout << "URL: " << recipe.recipeRecord.url.c_str() << endl;
	cout << "CATEGORY: " << recipe.recipeRecord.category.c_str() << endl;
	cout << "PREPERATION TIME: " << recipe.recipeRecord.prep_time << endl;
	cout << "COOKING TIME: " << recipe.recipeRecord.cook_time << endl;
	cout << "SERVING COUNT: " << recipe.recipeRecord.serving_count << endl << endl;
	cout << "INGREDIENTS: " << endl;
	for (RecipeIngredientRecord ingredient : recipe.ingredients) {
		cout << ingredient.ingredient_name.c_str() << ", " << ingredient.quantity << " " << ingredient.unit.c_str() << endl;
	}
	cout << endl;
	for (StepRecord step : recipe.steps) {
		cout << "STEP " << step.step_number << ": ";
		cout << step.instruction.c_str() << endl;
	}
	std::cout << endl << endl;
}
