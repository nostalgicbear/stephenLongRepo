/**
 * @file        SurnameNotLongEx.java
 * @author      Stephen Long
 * @assignment  Creche
 * @notes		Custom Exception
 */
package ie.wit.abs;

public class SurnameNotLongEx extends Exception {
	String message;
	public SurnameNotLongEx(){
		
	}
	public SurnameNotLongEx(String message){
		this.message=message;
	}
	public String toString(){
		return message;
	}
}