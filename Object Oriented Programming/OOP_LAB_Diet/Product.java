package diet;

public class Product implements NutritionalElement {
	private String name;
	private double calories;
	private double proteins;
	private double carbs;
	private double fat;
	private boolean per100g;
	
	public Product(String name,
						double calories,
						double proteins,
						double carbs,
						double fat,
						boolean per100g) {
		this.name = name;
		this.calories = calories;
		this.proteins = proteins;
		this.carbs = carbs;
		this.fat = fat;
		this.per100g = per100g;
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

	@Override
	public boolean per100g() {
		return this.per100g;
	}

}
