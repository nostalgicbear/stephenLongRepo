/**
 * @file        ValidateFee.java
 * @author      Stephen Long
 * @assignment  Creche
 * @notes		Custom Exception
 */
package ie.wit.abs;

public class ValidateFee extends Exception {
	String message;
	public ValidateFee(){
		message = "test";
	}
	public ValidateFee(double fee){
		message+=fee;
	}
	public String toString(){
		return message;
	}
}