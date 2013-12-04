package ie.wit.abs;

public class NumberOutOfBounds extends Exception {
	String message;
	public NumberOutOfBounds(){
		
	}
	public NumberOutOfBounds(String message){
		this.message=message;
	}
	public String toString(){
		return message;
	}
}
