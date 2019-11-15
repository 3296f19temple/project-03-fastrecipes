INSERT INTO recipe
VALUES
	(DEFAULT, 'steak', NULL, 'dinner', 20, 8, 28, 1),
    (DEFAULT, 'salad', NULL, 'all', 20, 0, 20, 4),
    (DEFAULT, 'cake', NULL, 'dessert', 20, 60, 80, 8);

INSERT INTO step
VALUES
	(DEFAULT, 1, 'light grill', 1),
    (DEFAULT, 1, 'cook for 3 minutes per side, flipping once', 2),
    (DEFAULT, 2, 'add ingredients to bowl', 1),
    (DEFAULT, 2, 'toss', 2),
    (DEFAULT, 3, 'add dry ingredients to bowl and mix', 1),
    (DEFAULT, 3, 'add wet ingredients to seperate bowl and mix just enought to form uniform mixture', 2),
    (DEFAULT, 3, 'add dry ingredients to wet and stir gently, just enough to form uniform mixture', 3),
    (DEFAULT, 3, 'pour into cake pan', 4),
    (DEFAULT, 3, 'bake for one hour at 375', 5);

INSERT INTO ingredient
VALUES
	(DEFAULT, 'sirloin steak'),
    (DEFAULT, 'salt'),
    (DEFAULT, 'lettuce'),
    (DEFAULT, 'spinach'),
    (DEFAULT, 'dressing'),
    (DEFAULT, 'flour'),
    (DEFAULT, 'sugar'),
    (DEFAULT, 'milk'),
    (DEFAULT, 'egg');

INSERT INTO recipe_has_ingredient
VALUES
	(1, 1, 1, 'steak'),
    (1, 2, 3, 'tsps'),
    (2, 3, 4, 'cups'),
    (2, 4, 4, 'cups'),
    (2, 5, 0.5, 'cups'),
    (3, 6, 2, 'cups'),
    (3, 7, 0.25, 'cups'),
    (3, 8, 2, 'cups'),
    (3, 9, 1, 'egg'),
    (3, 2, 0.5, 'tsp');
