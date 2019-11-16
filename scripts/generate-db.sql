CREATE SCHEMA fast_recipes;

USE fast_recipes;

CREATE TABLE recipe (
	recipe_id INT NOT NULL AUTO_INCREMENT,
    recipe_name VARCHAR(255) NOT NULL UNIQUE,
    url VARCHAR(2047),
    category VARCHAR(63),
	prep_time INT,
	cook_time INT,
	serving_count INT,
    CONSTRAINT pk_recipe PRIMARY KEY (recipe_id));

CREATE TABLE step (
	step_id INT NOT NULL AUTO_INCREMENT,
    recipe_id INT NOT NULL,
    instruction TEXT NOT NULL,
    step_number INT,
    CONSTRAINT pk_step PRIMARY KEY (step_id, recipe_id),
    CONSTRAINT fk_step_recipe FOREIGN KEY (recipe_id) REFERENCES recipe(recipe_id));

CREATE TABLE ingredient (
	ingredient_id INT NOT NULL AUTO_INCREMENT,
    ingredient_name VARCHAR(255) NOT NULL UNIQUE,
    CONSTRAINT pk_ingredient PRIMARY KEY (ingredient_id));

CREATE TABLE recipe_has_ingredient (
	recipe_id INT NOT NULL,
    ingredient_id INT NOT NULL,
    quantity NUMERIC(6, 2),
    unit VARCHAR(65),
    CONSTRAINT pk_recipe_has_ingredient PRIMARY KEY (recipe_id, ingredient_id),
    CONSTRAINT fk_recipe_ingredient FOREIGN KEY	(recipe_id) REFERENCES recipe(recipe_id),
    CONSTRAINT fk_ingredient_recipe FOREIGN KEY (ingredient_id) REFERENCES ingredient(ingredient_id));

# DROP SCHEMA fast_recipes;