package abstract_package;

public abstract class Person {
	
	private String firstName, lastName, nationality;
	private int age;
	
	//Constructor
	public Person(String firstName, String lastName, int age, String nationality){
		this.firstName = firstName;
		this.lastName = lastName;
		this.age = age;
		this.nationality = nationality;	
	}
	
	//Abstract methods
	public abstract String getType();
	public abstract int getRating();

	//Getter & Setters
	
	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public String getNationality() {
		return nationality;
	}

	public void setNationality(String nationality) {
		this.nationality = nationality;
	}
	
	
	
	
	
}
