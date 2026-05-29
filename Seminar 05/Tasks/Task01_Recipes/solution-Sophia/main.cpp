#include <iostream>
#include "Cookbook.h"
#include "Recipe.h"
#include "Ingredient.h"

bool hasSugar(const Recipe& r) {
    return r.contains("Sugar");
}

int main() {
    Recipe pancakes("Pancakes", "Mix and fry");
    pancakes.addIngredient(Ingredient("Flour", 200, Unit::G));
    pancakes.addIngredient(Ingredient("Milk", 300, Unit::ML));
    pancakes.addIngredient(Ingredient("Sugar", 20, Unit::G));

    Recipe omelette("Omelette", "Beat eggs and cook");
    omelette.addIngredient(Ingredient("Eggs", 3, Unit::PIECES));
    omelette.addIngredient(Ingredient("Cheese", 1, Unit::G));

    Recipe tunaWithPasta("Tuna fish with pasta", "");
    tunaWithPasta.addIngredient(Ingredient("Tuna fish", 100, Unit::G));
    tunaWithPasta.addIngredient(Ingredient("Pasta", 200, Unit::G));
    tunaWithPasta.addIngredient(Ingredient("Mozzarella", 50, Unit::G));

    Cookbook book("My Cookbook");

    book.addRecipe(pancakes);
    book.addRecipe(omelette);
    book.addRecipe(tunaWithPasta);

    std::cout << "=== All recipes ===\n";
    printCookbook(book);

    std::cout << "\nContains Pancakes: "
              << (book.containsRecipe("Pancakes") ? "Yes" : "No") << "\n";

    book.removeRecipe("Omelette");

    std::cout << "\n=== After removing Omelette ===\n";
    printCookbook(book);

    std::cout << "\n=== Recipes containing sugar ===\n";
    filterRecipes(book, hasSugar);

    Cookbook copy = book;

    std::cout << "\n=== Copy of cookbook ===\n";
    printCookbook(copy);
}
