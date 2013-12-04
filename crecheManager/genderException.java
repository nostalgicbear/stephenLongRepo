/**
 * @file        CrecheManager.java
 * @author      Stephen Long
 * @assignment  Creche
 * @notes		Custom Exception
 */
package ie.wit.abs;

public class genderException extends Exception {
	String message;
	public genderException(){
		
	}
	public genderException(String message){
		this.message=message;
	}
	public String toString(){
		return message;
	}
}
