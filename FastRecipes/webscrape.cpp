#include "webscrape.h"
#include <fstream>
#include <iostream>
#include <regex>

bool read_recipe(std::ifstream& file, Py_recipe& recipe)
{
	std::string buffer;
	// name
	if (!check_field("name:", file))
		return false;
	std::getline(file, recipe.name);
	// url
	if (!check_field("url:", file))
		return false;
	std::getline(file, recipe.url);
	// img_url
	if (!check_field("img_url:", file))
		return false;
	std::getline(file, recipe.img_url);
	// category
	if (!check_field("category:", file))
		return false;
	std::getline(file, recipe.category);
	// prep_time
	if (!check_field("prep_time:", file))
		return false;
	file >> recipe.prep_time;
	// cook_time
	if (!check_field("cook_time:", file))
		return false;
	file >> recipe.cook_time;
	// num_servings
	if (!check_field("num_servings:", file))
		return false;
	file >> recipe.num_servings;
	// ingredients
	if (!check_field("ingredients:", file))
		return false;
	while (get_ingredient(file, recipe));
	// instructions
	while (get_instruction(file, recipe));
	// read --- marker
	file >> buffer;
	return true;
}

std::string ltrim(const std::string& s)
{
	return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

bool check_field(const std::string& name, std::ifstream& stream)
{
	return check_field(name, stream, true);
}

bool check_field(const std::string& name, std::ifstream& stream, bool error_check)
{
	std::string buffer;
	stream >> buffer;
	if (buffer != name) {
		if (error_check)
			std::cerr << "expected field " << name << ", got " << buffer << "\n";
		return false;
	}
	return true;
}

bool get_ingredient(std::ifstream& stream, Py_recipe& recipe) {
	Py_ingredient ingredient{};
	// name
	int len = stream.tellg();
	if (!check_field("name:", stream, false)) {
		stream.seekg(len, std::ios_base::beg);
		return false;
	}
	std::getline(stream, ingredient.name);
	// amount 
	if (!check_field("amount:", stream))
		return false;
	std::getline(stream, ingredient.amount);
	// unit
	if (!check_field("unit:", stream))
		return false;
	std::getline(stream, ingredient.unit);
	recipe.ingredients.push_back(ingredient);
}

bool get_instruction(std::ifstream& stream, Py_recipe& recipe)
{
	int len = stream.tellg();
	std::string junk;
	std::string step;
	if (!check_field("step", stream, false)) {
		stream.seekg(len, std::ios_base::beg);
		return false;
	}
	std::getline(stream, junk);
	std::getline(stream, step);
	recipe.instructions.push_back(step);
	std::cout << "got step\n";
	return true;
}

void print_py_ingredient(const Py_ingredient& i) {
	std::cout << "\tingredient name: " << i.name << "\n";
	std::cout << "\tingredient amount: " << i.amount << "\n";
	std::cout << "\tingredient unit: " << i.unit << "\n";
}

void print_py_recipe(const Py_recipe& r) {
	std::cout << "name: " << r.name << "\n";
	std::cout << "url: " << r.url << "\n";
	std::cout << "img_url: " << r.url << "\n";
	std::cout << "category: " << r.category << "\n";
	std::cout << "prep_time: " << r.prep_time << "\n";
	std::cout << "cook_time: " << r.cook_time << "\n";
	std::cout << "num_servings: " << r.num_servings << "\n";
	for (const Py_ingredient& i : r.ingredients) {
		print_py_ingredient(i);
	}
	int i = 0;
	for (const std::string& step : r.instructions) {
		std::cout << "step " << i << ": " << step << "\n";
		++i;
	}
}





