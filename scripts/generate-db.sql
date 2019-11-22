CREATE SCHEMA fast_recipes;

USE fast_recipes;

CREATE TABLE recipe (
    recipe_name VARCHAR(255) NOT NULL,
    url VARCHAR(2047),
    image_url VARCHAR(2047),
    category VARCHAR(63),
	prep_time INT,
	cook_time INT,
	serving_count INT,
    CONSTRAINT pk_recipe PRIMARY KEY (recipe_name));

CREATE TABLE step (
    recipe_name VARCHAR(255) NOT NULL,
	step_number INT NOT NULL,
    instruction TEXT,
    CONSTRAINT pk_step PRIMARY KEY (recipe_name, step_number),
    CONSTRAINT fk_step_recipe FOREIGN KEY (recipe_name) REFERENCES recipe(recipe_name) ON DELETE CASCADE);

CREATE TABLE ingredient (
	ingredient_id INT NOT NULL AUTO_INCREMENT,
	recipe_name VARCHAR(255) NOT NULL,
    ingredient_name VARCHAR(255),
    quantity NUMERIC(6, 2),
    unit VARCHAR(65),
    CONSTRAINT pk_ingredient PRIMARY KEY (ingredient_id),
    CONSTRAINT fk_ingredient_recipe FOREIGN KEY (recipe_name) REFERENCES recipe(recipe_name) ON DELETE CASCADE);

DELIMITER $$
CREATE PROCEDURE get_recipe_record (IN get_recipe_name VARCHAR(255))
BEGIN
    SELECT *
    FROM recipe
    WHERE recipe_name = get_recipe_name;
END $$

CREATE PROCEDURE get_step_records (IN get_recipe_name VARCHAR(255))
BEGIN
    SELECT *
    FROM step
    WHERE recipe_name = get_recipe_name;
END$$

CREATE PROCEDURE get_ingredient_records (IN get_recipe_name VARCHAR(255))
BEGIN
    SELECT recipe_name, ingredient_name, quantity, unit
    FROM ingredient
    WHERE recipe_name = get_recipe_name;
END$$

CREATE PROCEDURE insert_recipe(
	IN new_recipe_name VARCHAR(255),
	IN new_url VARCHAR(2047),
    IN new_image_url VARCHAR(2047),
    IN new_category VARCHAR(63),
	IN new_prep_time INT,
	IN new_cook_time INT,
	IN new_serving_count INT)
BEGIN
INSERT INTO recipe
VALUES (new_recipe_name, new_url, new_image_url, new_category, new_prep_time, new_cook_time, new_serving_count);
END$$

CREATE PROCEDURE insert_step(
    IN new_recipe_name VARCHAR(255),
    IN new_step_number INT,
    IN new_instruction TEXT)
BEGIN
INSERT INTO step
VALUES (new_recipe_name, new_step_number, new_instruction);
END$$

CREATE PROCEDURE insert_ingredient(
	IN new_recipe_name VARCHAR(255),
    IN new_ingredient_name VARCHAR(255),
    IN new_quantity DECIMAL(6,2),
    IN new_unit VARCHAR(255))
BEGIN
INSERT INTO ingredient
VALUES (DEFAULT, new_recipe_name, new_ingredient_name, new_quantity, new_unit);
END$$

CREATE PROCEDURE delete_recipe(
    IN del_recipe_name VARCHAR(255))
BEGIN
    DELETE FROM recipe WHERE recipe_name = del_recipe_name;
END$$
DELIMITER ;

# DROP SCHEMA fast_recipes;