package implementation_package;
import abstract_package.Person;


//Add an icon for player profile.
public class Player extends Person {
	
	@Override
	public String toString() {
		return getFirstName() + " "
				+ getLastName() ;
	}

	private String position;
	private int rating;
	private boolean injured;
	
	public Player(String firstName, String lastName, int age, String nationality, String position, int rating){
		super(firstName, lastName, age, nationality);
		this.position = position;
		this.rating = rating;		
		injured=false;
	}

	//Return person type
	public String getType(){
		return "Player";
	}
	
	//Getters and Setters
	public String getPosition() {
		return position;
	}

	public int getRating() {
		if(injured)
			return 0;
		return rating;
	}

	public boolean isInjured() {
		return injured;
	}

	public void setInjured(boolean injured) {
		this.injured = injured;
	}

	
}
