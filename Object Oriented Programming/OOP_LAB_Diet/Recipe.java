package diet;

import java.util.ArrayList;
import java.util.List;

/**
 * Represent a recipe of the diet.
 * 
 * A recipe consists of a a set of ingredients that are given amounts of raw materials.
 * The overall nutritional values of a recipe can be computed
 * on the basis of the ingredients' values and are expressed per 100g
 * 
 *
 */
public class Recipe implements NutritionalElement {
	private String name;
	private Food food;
	private List<String> ingredients = new ArrayList<>();
	
	private double calories;
	private double proteins;
	private double carbs;
	private double fat;
    
	/**
	 * Recipe constructor.
	 * The reference {@code food} of type {@link Food} must be used to
	 * retrieve the information about ingredients. 
	 * 
	 * @param nome unique name of the recipe
	 * @param food object containing the information about ingredients
	 */
	public Recipe(String name, Food food){
		this.name = name;
		this.food = food;
		
		this.calories = this.proteins = this.carbs = this.fat = 0;
		food.addRecipe(this);
	}
	
	/**
	 * Adds a given quantity of an ingredient to the recipe.
	 * The ingredient is a raw material defined with the {@code food}
	 * argument of the constructor.
	 * 
	 * @param material the name of the raw material to be used as ingredient
	 * @param quantity the amount in grams of the raw material to be used
	 */
	public void addIngredient(String material, double quantity) {
		RawMaterial ingredient = (RawMaterial) food.getRawMaterial(material);
		if(ingredient == null) {
			System.out.println("Ingredient " + material + " not found");
			return;
		}
		this.calories += ingredient.getCalories() * quantity / 100;
		this.proteins += ingredient.getProteins() * quantity / 100;
		this.carbs 	  += ingredient.getCarbs() 	  * quantity / 100;
		this.fat 	  += ingredient.getFat() 	  * quantity / 100;
		
		ingredients.add(material);
	}

	@Override
	public String getName() {
		return this.name;
	}

	@Override
	public double getCalories() {
		return this.calories;
	}

	@Override
	public double getProteins() {
		return this.proteins;
	}

	@Override
	public double getCarbs() {
		return this.carbs;
	}

	@Override
	public double getFat() {
		return this.fat;
	}

	/**
	 * Indicates whether the nutritional values returned by the other methods
	 * refer to a conventional 100g quantity of nutritional element,
	 * or to a unit of element.
	 * 
	 * For the {@link Recipe} class it must always return {@code true}:
	 * a recipe expressed nutritional values per 100g
	 * 
	 * @return boolean indicator
	 */
	@Override
	public boolean per100g() {
	    // a recipe expressed nutritional values per 100g
		return true;
	}

}
