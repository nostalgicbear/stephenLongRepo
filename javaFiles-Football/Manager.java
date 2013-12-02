package implementation_package;
import abstract_package.Person;

//Add and icon for player profiles
public class Manager extends Person {

	@Override
	public String toString() {
		return getFirstName() + " "
				+ getLastName();
	}

	int rating;
	
	public Manager(String firstName, String lastName, int age, String nationality, int rating){
		super(firstName, lastName, age, nationality);
		this.rating = rating;		
	}

	public String getType(){
		return "Manager"; 
	}

	public int getRating() {
		return rating;
	}
	
}
