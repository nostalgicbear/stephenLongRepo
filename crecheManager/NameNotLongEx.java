/**
 * @file        NameNotLongEx.java
 * @author      Stephen Long
 * @assignment  Creche
 *@notes 		Custom Exception
 */
package ie.wit.abs;

public class NameNotLongEx extends Exception {
	String message;
	public NameNotLongEx(){
		
	}
	public NameNotLongEx(String message){
		this.message=message;
	}
	public String toString(){
		return message;
	}
}
