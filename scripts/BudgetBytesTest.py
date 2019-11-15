# Created by Matthew Majewski (BigBadBoris) on 11/13/2019
# This script is made to web-scrape recipes from the website
# budgetbytes.com. The html is nicely organized into distinct 
# classes, which make it easy to separate ingredient names, 
# amounts, and units of each amount. 

# To figure out how to parse the html tree of a website to extract the
# information you want, I recomend using the "inspect element" feature
# built-in to firefox. To use this, right-click on the relevant
# text/region on the page, and the firefox debugger will pop up,
# high-lighting the relevant portion of the html. Inside the debugger,
# you can also mouse over a portion of the html, and the relevant
# region in the webpage will be high-lighted as well.

import bs4 
import requests 

class Recipe:
    def __init__(self):
        self.name = "n/a"
        self.category = "n/a"
        self.prep_time = "n/a"
        self.cook_time = "n/a"
        self.total_time = "n/a"
        self.num_servings = "n/a"
        self.ingredients = []
        self.instructions = []


class Ingredient:
    def __init__(self):
        self.amount = "n/a"
        self.unit = "n/a"
        self.name = "n/a"


def print_recipe(recipe):
    print("Name: ", recipe.name)
    print("Prep Time: ", recipe.prep_time)
    print("Cook Time: ", recipe.cook_time)
    print("Total Time: ", recipe.total_time)
    print("Servings: ", recipe.num_servings)
    print("Ingredients: ")
    for ingredient in recipe.ingredients:
        print("\tName: ", ingredient.name)
        print("\tAmount: ", ingredient.amount)
        print("\tUnit: ", ingredient.unit)
    print("Instructions: ")
    for step in recipe.instructions:
        print()
        print(step)


def get_recipe_name(soup, Recipe):
    element = soup.select('.wprm-recipe-name')
    Recipe.name = element[0].text


def get_recipe_time(soup, Recipe):
    # get prep time
    element = soup.select('.wprm-recipe-prep_time')
    Recipe.prep_time = element[0].text
    # get cook time
    element = soup.select('.wprm-recipe-cook_time')
    Recipe.cook_time = element[0].text
    # get total time
    element = soup.select('.wprm-recipe-total_time')
    Recipe.total_time = element[0].text


def get_recipe_servings(soup, Recipe):
    element = soup.select('.wprm-recipe-servings')
    Recipe.num_servings = element[0].text


def get_recipe_instructions(soup, Recipe):
    elements = soup.select('.wprm-recipe-instruction')
    for element in elements:
        Recipe.instructions.append(element.text)
    

def get_recipe_ingredients(soup, Recipe):
    soup.select('.wprm-recipe-ingredient')
    top_elements = soup.select('.wprm-recipe-ingredient')
    for top_element in top_elements:
        children = top_element.children
        ingredient = Ingredient()
        for child in children:
            if isinstance(child, str):
                continue
            current_class = child['class'][0]
            # do comparison here
            if current_class == 'wprm-recipe-ingredient-amount':
                ingredient.amount = child.text
                #print("\tingredient amount: ", child.text)
            elif current_class == 'wprm-recipe-ingredient-unit':
                ingredient.unit = child.text
                #print("\tingredient unit: ", child.text)
            elif current_class == 'wprm-recipe-ingredient-name':
                ingredient.name = child.text
                #print("\tingredient name: ", child.text)
        Recipe.ingredients.append(ingredient)



# Test Code
webpage = 'https://www.budgetbytes.com/sweet-potato-biscuits/'
# fetch webpage
res = requests.get(webpage)
html_string = res.text
# Get beautiful soup parser
soup = bs4.BeautifulSoup(html_string, 'html.parser')
# create new recipe object
recipe = Recipe()
# fill its contents
get_recipe_ingredients(soup, recipe)
get_recipe_instructions(soup, recipe)
get_recipe_name(soup, recipe)
get_recipe_time(soup, recipe)
get_recipe_servings(soup, recipe)
print_recipe(recipe)
