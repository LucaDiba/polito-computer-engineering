package diet;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a complete menu.
 * 
 * It can be made up of both packaged products and servings of given recipes.
 *
 */
public class Menu implements NutritionalElement {
	String name;
	Food food;
	private List<NutritionalElement> recipes	 = new ArrayList<>();
	private List<NutritionalElement> products 	 = new ArrayList<>();
	
	private double calories;
	private double proteins;
	private double carbs;
	private double fat;

	/**
	 * Menu constructor.
	 * The reference {@code food} of type {@link Food} must be used to
	 * retrieve the information about recipes and products 
	 * 
	 * @param nome unique name of the menu
	 * @param food object containing the information about products and recipes
	 */
	public Menu(String name, Food food){
		this.name = name;
		this.food = food;
		
		this.calories = this.proteins = this.carbs = this.fat = 0;
	}
	
	/**
	 * Adds a given serving size of a recipe.
	 * The recipe is a name of a recipe defined in the {@code food}
	 * argument of the constructor.
	 * 
	 * @param recipe the name of the recipe to be used as ingredient
	 * @param quantity the amount in grams of the recipe to be used
	 */
	public void addRecipe(String recipe, double quantity) {
		Recipe item = (Recipe) this.food.getRecipe(recipe);
		if(item == null) {
			System.out.println("Recipe " + recipe + " not found");
			return;
		}
		this.calories += item.getCalories() * quantity / 100;
		this.proteins += item.getProteins() * quantity / 100;
		this.carbs	  += item.getCarbs()	* quantity / 100;
		this.fat	  += item.getFat()		* quantity / 100;
		
		recipes.add(item);
	}

	/**
	 * Adds a unit of a packaged product.
	 * The product is a name of a product defined in the {@code food}
	 * argument of the constructor.
	 * 
	 * @param product the name of the product to be used as ingredient
	 */
	public void addProduct(String product) {
		Product item = (Product) this.food.getProduct(product);
		if(item == null) {
			System.out.println("Product " + product + " not found");
			return;
		}
		this.calories += item.getCalories();
		this.proteins += item.getProteins();
		this.carbs	  += item.getCarbs();
		this.fat	  += item.getFat();
		
		products.add(item);
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
	 * For the {@link Menu} class it must always return {@code false}:
	 * nutritional values are provided for the whole menu.
	 * 
	 * @return boolean indicator
	 */
	@Override
	public boolean per100g() {
		// nutritional values are provided for the whole menu.
		return false;
	}
}
