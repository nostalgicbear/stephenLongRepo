/**
 * @file        Child.java
 * @author      Stephen Long
 * @assignment  Creche
 *
 */
package ie.wit.abs;
import ie.wit.abs.Person;
public class Child extends Person{
	public double fee;
	
	public Child(){
		super();
		this.fee=0;
	}
	
	public Child(String firstName, String surname, String gender, int id, double fee){
		super(firstName, surname, gender, id);
		this.fee=fee;
	}
	
	public int getId(){
		return id;
	}
	
	public String getPersonType(){
		return "child";
	}

	public double getFee() {
		return fee;
	}

	public void setFee(double fee) {
		this.fee = fee;
	}

	@Override
	public String toString() {
		return "\nChild: Name: " + firstName + " " + surname + ", Gender: " + gender + ", Id: " + id + ", Weekly fee:" + fee;
	}
	

	
}

