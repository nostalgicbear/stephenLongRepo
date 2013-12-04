/**
 * @file        CrecheManager.java
 * @author      Stephen Long
 * @assignment  Creche
 * @brief       Contains methods that create and appear on the menu
 *
 */
package ie.wit.abs;
import java.util.List;
import java.util.*;
import ie.wit.abs.Person;

import javax.swing.*;

public class CrecheManager {
	private static Icon crecheImage = new ImageIcon("..\\Creche\\images\\crecheImage.jpg","");
	private static Icon imageInstance = new ImageIcon();
	private List<Person> creche = new ArrayList<Person>();
	private static int personId=1;


public CrecheManager(){
	Child firstChild = new Child("Stephen", "Long", "Male", personId, 5.5);
	creche.add(firstChild);
}

public int menuMain()
{
	int option = 0;
	
	   String opt1 = new String("1. Register a Person :");
	   String opt2 = new String("2. Register a Child with a Parent :");
	   String opt3 = new String("3. List All Parents & Children :");
	   String opt4 = new String("4. List All Children of Parent :");
	   String opt5 = new String("5. Calculate weekly income for All Children:");
	   String opt6 = new String("6. Search for a person (based on firstName & LastName) :");
	   String opt7 = new String("7. Remove a person based on ID :");
	   String opt8 = new String("8Search based on either First or Last name");
	   String opt9 = new String ("9.Exit System :");
	   String msg = new String("** Enter number of option in the box below **");
	   JTextField opt = new JTextField("");
	   
	   Object message[] = new Object[12];

	   message[0] = crecheImage;
	   message[1] = opt1;
	   message[2] = opt2;
	   message[3] = opt3;
	   message[4] = opt4;
	   message[5] = opt5;
	   message[6] = opt6;
	   message[7] = opt7;
	   message[8] = opt8;
	   message[9] = opt9;
	   message[10] = msg;
	   message[11] = opt;

	   int response = JOptionPane.showConfirmDialog(null,message,"Happyways Creche",JOptionPane.OK_CANCEL_OPTION,
               JOptionPane.QUESTION_MESSAGE ,imageInstance);

if(response == JOptionPane.CANCEL_OPTION){
	int answer;
	answer = JOptionPane.showConfirmDialog(null,"Are you sure you want to exit?",null, JOptionPane.YES_NO_OPTION);
	if(answer == JOptionPane.YES_OPTION){
		JOptionPane.showMessageDialog(null,"Goodbye");
		System.exit(0);
	}
}
else
{
try {
option = Integer.parseInt(opt.getText());
if(option<=0 || option>9){
	throw new NumberOutOfBounds();
}
}catch(NumberOutOfBounds ex){
	JOptionPane.showMessageDialog(null,"You entered " + option + "\nPlease enter a number in the range of 1-9");
}

catch (NumberFormatException e)
{
JOptionPane.showMessageDialog(null,"You entered letters into the command box \n Please enter a number ranging from 1-9");
}
}
return option;
}	
/**
 * @param creche
 * If the creche array is not empty, the person at each index is listed.
 */
public void listPersons(){
	if(creche.size()>=1){
	JOptionPane.showMessageDialog(null,"This is the list :" + creche);
}
	else{
		JOptionPane.showMessageDialog(null,"The list is currently empty");
	}
}
/**			
 * @param creche
 * Allows the user to search for a person based on either firstname or surname.
 * If the entered string is found in firstname or surname of an index, the person(s) is returned.
 */
public void searchPerson(List<Person>creche){
	try{
	String name;
	int answer;
	boolean found = false;
	name = JOptionPane.showInputDialog("Enter firstname or surname of person you wish to search");
	if(!name.equals(""))
	for(int i = 0; i < creche.size(); i++){
		if (creche.get(i).getFirstName().contentEquals(name)||creche.get(i).getSurname().contentEquals(name) ){
			JOptionPane.showMessageDialog(null,creche.get(i));
			found = true;
		}	
	}
	if(!found)
		JOptionPane.showMessageDialog(null,"The person " + name + " was not found");
	answer = JOptionPane.showConfirmDialog(null,"Would you like to view the list?",null, JOptionPane.YES_NO_OPTION);
	if(answer == JOptionPane.YES_OPTION){
		listPersons();
	}
	}catch(Exception e){
		JOptionPane.showMessageDialog(null,"An error occured, please try again");
	}
}

public List<Person> getCreche() {
	return creche;
}

public void setcreche(List<Person> creche) {
	this.creche = creche;
}

/**
 * @param creche
 * Based on the option chosen by the user, a Parent or Child is created. 
 * Fields must be filled in correctly, with incorrect input being rejected, and the user warned via exceptions.
 * Each piece of user input is validated against an exception.
 */
public void registerAPerson(List<Person>creche){
	Object options[]= new String[3]; 
	options[0]= "Child";
	options[1]="Parent";
	options[2]="Cancel";
	int n = JOptionPane.showOptionDialog(null, "Do you want to register a child or a  parent?", "Register a Person", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[2]);
	if(n==0){
		JTextField firstName = new JTextField("firstName");
		JTextField surname = new JTextField("surname");
		JTextField gender = new JTextField("gender");
		JTextField fee = new JTextField("fee");
		
		Object message[]= new Object[4];
		message[0]=firstName;
		message[1]=surname;
		message[2]=gender;
		message[3]=fee;
		JOptionPane.showMessageDialog(null, message);
		
		try{
			String newFirstName = firstName.getText();
			if(newFirstName.length()<1){
				throw new NameNotLongEx(newFirstName);
			}
			String newSurname = surname.getText();
			if(newSurname.length()<1){
				throw new SurnameNotLongEx(newSurname);
			}
		 double newFee = Double.parseDouble(fee.getText());
		 if(newFee <1){
			 throw new ValidateFee();
		 }
		 String newGender = gender.getText();
			if(!newGender.equals("male") && !newGender.equals("female")){
				throw new genderException(newGender);
			}
			
		personId++;
		JOptionPane.showMessageDialog(null,"A child has been added to the creche and assigned the id " + personId);
		Child child = new Child(newFirstName,newSurname,newGender,personId,newFee);
		creche.add(child);

		} catch (ValidateFee ex) {
			JOptionPane.showMessageDialog(null,"You entered" + ex.toString() + " as the fee needs to be a positive number" + "\nPlease try again");
		}catch(NameNotLongEx ex){
			JOptionPane.showMessageDialog(null,"No first name was entered " +  "\nPlease try again");
		}catch(SurnameNotLongEx ex){
			JOptionPane.showMessageDialog(null,"No surname was entered "+ex.toString() + "\nPllease try again");
		}catch(genderException ex){
			JOptionPane.showMessageDialog(null,"You must enter a gender as being either 'male' or 'female'" +  "\nPlease try again");
		}catch(Exception e){
			JOptionPane.showMessageDialog(null,"An error has occured while registering this person" +  "\n Please register the person again");
		}
		
		}
	if(n==1){
		JTextField firstName = new JTextField("firstName");
		JTextField surname = new JTextField("surname");
		JTextField gender = new JTextField("gender");
		
		Object message[]= new Object[3];
		message[0]=firstName;
		message[1]=surname;
		message[2]=gender;
		JOptionPane.showMessageDialog(null, message);
		
		try{
			String newFirstName = firstName.getText();
			if(newFirstName.length()<1){
				throw new NameNotLongEx(newFirstName);
			}
			String newSurname = surname.getText();
			if(newSurname.length()<1){
				throw new SurnameNotLongEx(newSurname);
			}
			String newGender = gender.getText();
			if(!newGender.contentEquals("male") && !newGender.contentEquals("female")) {
				throw new genderException(newGender);
			}
		Parent parent = new Parent(newFirstName,newSurname,newGender,++personId);
		JOptionPane.showMessageDialog(null,"A person has been added to the creche and assigned the id " + personId);
		creche.add(parent); 
	}catch(NameNotLongEx ex){
		JOptionPane.showMessageDialog(null,"No first name was entered " +  "\nPlease try again");
	}catch(SurnameNotLongEx ex){
		JOptionPane.showMessageDialog(null,"No surname was entered " +  "\nPlease try again");
	}catch(genderException ex){
		JOptionPane.showMessageDialog(null,"You must enter a gender as being either 'male' or 'female'" +  "\nPlease try again");
	}catch(Exception e){
		JOptionPane.showMessageDialog(null,"An error has occured while registering this person" +  "\n Please register the person again");
	}
	}
}
/**
 * 
 * @param creche
 * The total income is initialized as 0. For each person in the creche, who is a child, the double stored under fee is added to the total.
 */
public void calcTotalWeeklyFee(List<Person>creche){
	double total =0.0;
	if(creche.size()>0){
	for(Person i: creche){
		if(i.getPersonType().equals("child")){
			total=total +((Child) i).getFee();
		}
	}
	JOptionPane.showMessageDialog(null,"The total weekly income is : " + total);
	}
	else{
		JOptionPane.showMessageDialog(null,"The list is currently empty. \n Therefore the income is 0");
	}
}

/**
 * 
 * @param creche
 * The user inputs an id. If the entered id is the id of the parent, and the second user input is a valid id of a child, the child is added to the parent.
 */
public void registerChildWithParent(List<Person>creche){
	try{
	Parent p = null;
	Child w = null;
	boolean validParent = false;
	boolean validChild = false;
	String prompt;
	String prompt2;
	int n;
	int x;
	prompt = JOptionPane.showInputDialog("Please enter ID of the Parent");
	n = Integer.parseInt(prompt);
	for(int i=0;i<creche.size();i++){
		if(creche.get(i).getId()==n && creche.get(i).getPersonType()=="parent"){
			validParent = true;
			p = (Parent)creche.get(i);
		}
	}
		prompt2 = JOptionPane.showInputDialog("Please enter ID of the Child");
		x = Integer.parseInt(prompt2);
		for(int q=0; q<creche.size();q++){
			if(creche.get(q).getId()==x && creche.get(q).getPersonType()=="child"){
				validChild=true;
				w = (Child)creche.get(q);
			}
		}
			if(validParent==true && validChild==true){
				p.addChild(w);
				JOptionPane.showMessageDialog(null,"The child has been successfully added to the parent " );
			}
		
	if(!validParent || !validChild){
		JOptionPane.showMessageDialog(null,"Parent or Child not found");
	}
	}catch(NumberFormatException ex){
		JOptionPane.showMessageDialog(null,"Please enter a number for the ID. \n Please try again");
	}catch(Exception e){
		JOptionPane.showMessageDialog(null,"An error occured. \n Please try again");
	}
}
/**
 * 
 * @param creche
 * The user enters a firstname & surname.
 * If the contents of the firstname & contents of the surname are found at the same index in the array, the person is returned.
 */
public void findPerson(List<Person>creche){
	try{
	String name1;
	String name2;
	boolean found = false;
	name1 = JOptionPane.showInputDialog("Enter firstname of person you want to search");
	name2 = JOptionPane.showInputDialog("Enter surname of person you want to search");
	for(int i = 0; i < creche.size(); i++){
		if (creche.get(i).getFirstName().contentEquals(name1) && creche.get(i).getSurname().contentEquals(name2)){	
		found = true;
		JOptionPane.showMessageDialog(null,"Person found :" + creche.get(i));
}
		
}
	if(!found){
		JOptionPane.showMessageDialog(null,"Person not found");
	}
}catch(NumberFormatException e){
	JOptionPane.showMessageDialog(null,"Please enter a number for for id" + "\nPlease try again");
}catch(Exception e){
	JOptionPane.showMessageDialog(null,"Returning to menu");
}
}
/**
 * 
 * @param creche
 * The user inputs an id of a parent. If the id is valid, the array of that person is searched and each child added to that array is returned.
 */
public void listChildrenOfParents(List<Person>creche){
	try{
	String a;
	String b;
	boolean validParent = false;
	String prompt;
	int n;
	prompt = JOptionPane.showInputDialog("Please enter ID of the Parent");
	n=Integer.parseInt(prompt);
	for(int i=0;i<creche.size();i++){
		if((creche.get(i).getId()==n) && creche.get(i).getPersonType()=="parent"){
			validParent = true;
			if(((Parent)creche.get(i)).getChildren().size()>0)
				for(int j =0; j<((Parent) creche.get(i)).getChildren().size();j++){
					a = ((Parent) creche.get(i)).getChildren().get(j).getFirstName();
					b = ((Parent) creche.get(i)).getChildren().get(j).getSurname();
					JOptionPane.showMessageDialog(null,"The child/children of the parent with id " + prompt + ":" + a + " " + b);
			}
			else
				JOptionPane.showMessageDialog(null,"There are no children registered to this parent");
		}
	}
	
	if(!validParent){
		JOptionPane.showMessageDialog(null,"You did not enter the id of a parent");
	}
}catch(NumberFormatException ex){
	JOptionPane.showMessageDialog(null,"Please enter numbers for the id");
}catch(Exception ex){
	JOptionPane.showMessageDialog(null,"An error has occured");
}

}
/**
 * @param creche
 * The user inputs an id. The person with that id is removed from the creche.
 * If the id is that of a child, the child is also removed from any parent it may be registered to.
 */
public void removeAPerson(List<Person>creche){
	try{
	boolean personFound = false;
	int input;
	String numberIn;
	numberIn= JOptionPane.showInputDialog("Please enter ID of the person you wish to remove");
	input = Integer.parseInt(numberIn);
	if(input<0){
		throw new NumberOutOfBounds();
	}
	for(int i=0;i<creche.size();i++){
		if(creche.get(i).getId()==input && creche.get(i).getPersonType()=="parent"){
			personFound=true;
			JOptionPane.showMessageDialog(null,"You have removed " + creche.get(i).getFirstName() + " " + creche.get(i).getSurname() + " from the list.");
			creche.remove(i);
		}
		else if (creche.get(i).getId()==input && creche.get(i).getPersonType()=="child"){
			personFound=true;
			JOptionPane.showMessageDialog(null,"You have removed " + creche.get(i).getFirstName() + " " + creche.get(i).getSurname() + " from the list.");
			for(int x=0; x<creche.size();x++){
				if(creche.get(x).getPersonType()=="parent"){
					for(int j=0;j<((Parent)creche.get(j)).getChildren().size();j++){
						if(((Parent)creche.get(j)).getChildren().get(j).getId()==input){
							((Parent)creche.get(j)).getChildren().remove(j);	
						}
					}
				}
			}
			creche.remove(i);
		}
	}if(!personFound){
		JOptionPane.showMessageDialog(null,"Person not found");
}
}catch(NumberFormatException e){
	JOptionPane.showMessageDialog(null,"An id must contain only numbers" +  "\n Please enter a valid id of someone in the list");
}catch(NumberOutOfBounds ex){
	JOptionPane.showMessageDialog(null,"You entered a negative value for Id" + "\nPlease try again");
}catch(Exception e){
	JOptionPane.showMessageDialog(null,"An error has occured" + "\nPlease try again");
}
}

}
