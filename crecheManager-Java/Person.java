/**
 * @file        Person.java
 * @author      Stephen Long
 * @assignment  Creche
 *
 */
package ie.wit.abs;

public abstract class Person {
	protected String firstName;
	protected String surname;
	protected String gender;
	protected int id;
	
	public Person(){
		this.firstName="";
		this.surname="";
		this.gender="";
		this.id=0;	
	}
	
	public Person(String firstName, String surname, String gender, int id){
		this.firstName=firstName;
		this.surname=surname;
		this.gender=gender;
		this.id=id;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public String getGender() {
		return gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}

	public abstract int getId() ;
	public abstract String getPersonType();

	public void setId(int id) {
		this.id = id;
	}

	@Override
	public String toString() {
		return "Person [firstName=" + firstName + ", surname=" + surname + ", gender=" + gender + ", id=" + id + "]";
	}
	
	

}
