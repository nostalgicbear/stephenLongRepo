/**
 * @file        Parent.java
 * @author      Stephen Long
 * @assignment  Creche
 *
 */
package ie.wit.abs;
import java.util.ArrayList;
import java.util.List;

import ie.wit.abs.Person;
public class Parent extends Person {
	private List<Child> children = new ArrayList<Child>();
	public Parent(){
	super();
	}
	
	public Parent(String firstName, String surname, String gender, int id){
		super(firstName, surname, gender, id);
	}
	
	public int getId(){
		return id;
	}
	
	public String getPersonType(){
		return "parent";
	}
	
	public void addChild(Child c){
		children.add(c);
	}
	
	public void removeChild(Child c){
		children.remove(c);
	}
	


	@Override
	public String toString() {
		return "\nParent Name:" + firstName + " " + surname + ", Gender: " + gender + ", id: " + id;
	}

	public List<Child> getChildren() {
		return children;
	}

	public void setChildren(List<Child> children) {
		this.children = children;
	}

}
