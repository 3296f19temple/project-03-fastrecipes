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

		pstmt = con->prepareStatement("CALL insert_recipe(?,?,?,?,?,?)");
		recipe.recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe.recipe_name);
		recipe.url.compare("") == 0 ?
			pstmt->setNull(2, sql::DataType::VARCHAR) :
			pstmt->setString(2, recipe.url);
		recipe.category.compare("") == 0 ?
			pstmt->setNull(3, sql::DataType::VARCHAR) :
			pstmt->setString(3, recipe.category);
		recipe.prep_time == NULL ?
			pstmt->setNull(4, sql::DataType::INTEGER) :
			pstmt->setInt(4, recipe.prep_time);
		recipe.cook_time == NULL ?
			pstmt->setNull(5, sql::DataType::INTEGER) :
			pstmt->setInt(5, recipe.cook_time);
		recipe.serving_count == NULL ?
			pstmt->setNull(6, sql::DataType::INTEGER) :
			pstmt->setInt(6, recipe.serving_count);

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
			recipe_name.compare("") == 0 ?
				pstmt->setNull(1, sql::DataType::VARCHAR) :
				pstmt->setString(1, recipe_name);
			step.step_number == NULL ?
				pstmt->setNull(2, sql::DataType::INTEGER) :
				pstmt->setInt(2, step.step_number);
			step.instruction.compare("") == 0 ?
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
			recipe_name.compare("") == 0 ?
				pstmt->setNull(1, sql::DataType::VARCHAR) :
				pstmt->setString(1, recipe_name);
			ingredient.ingredient_name.compare("") == 0 ?
				pstmt->setNull(2, sql::DataType::VARCHAR) :
				pstmt->setString(2, ingredient.ingredient_name);
			ingredient.quantity == NULL ?
				pstmt->setNull(3, sql::DataType::DOUBLE) :
				pstmt->setDouble(3, ingredient.quantity);
			ingredient.unit.compare("") == 0 ?
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

Recipe getRecipe(sql::SQLString recipe_name) {
	Recipe recipe;
	recipe.recipeRecord = getRecipeRecord(recipe_name);
	recipe.steps = getStepRecords(recipe_name);
	recipe.ingredients = getIngredientRecords(recipe_name);
	return recipe;
}

void insertRecipe(Recipe recipe) {
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

void Mysql_Connection_Tester() {
	RecipeRecord rr = { "scrambled eggs", "", "breakfast", 10, 10, 2 };
	StepRecord st1 = { 1, "break eggs and scramble" };
	StepRecord st2 = { 2, "fry in pan" };
	RecipeIngredientRecord rit1 = { "egg", 2, "eggs" };
	RecipeIngredientRecord rit2 = { "salt", 0.25, "tsp" };
	Recipe recipe = { rr, {st1, st2}, {rit1, rit2} };
	insertRecipe(recipe);

	sql::SQLString recipe_name = "scrambled eggs";
	recipe = getRecipe(recipe_name);

	cout << "Recipe.recipe_name: "<< recipe.recipeRecord.recipe_name.c_str() << endl;
	cout << "Recipe.url: " << recipe.recipeRecord.url.c_str() << endl;
	cout << "Recipe.category: " << recipe.recipeRecord.category.c_str() << endl;
	cout << "Recipe.prep_time: " << recipe.recipeRecord.prep_time << endl;
	cout << "Recipe.cook_time: " << recipe.recipeRecord.cook_time << endl;
	cout << "Recipe.serving_count: " << recipe.recipeRecord.serving_count << endl << endl;
	for (StepRecord step : recipe.steps) {
		cout << "Step.step_number: " << step.step_number << endl;
		cout << "Step.instruction: " << step.instruction.c_str() << endl << endl;
	}
	for (RecipeIngredientRecord ingredient : recipe.ingredients) {
		cout << "Ingredient.ingredient_name: " << ingredient.ingredient_name.c_str() << endl;
		cout << "Ingredient.quntity: " << ingredient.quantity << endl;
		cout << "Ingredient.unit: " << ingredient.unit.c_str() << endl;
	}

	deleteRecipe(rr.recipe_name);
}
