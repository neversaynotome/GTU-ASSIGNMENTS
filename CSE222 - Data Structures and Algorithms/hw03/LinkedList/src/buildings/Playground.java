package src.buildings;

/**
* Playground class for playgrounds.
*/

import java.util.*;

public class Playground extends Building implements Cloneable {

	public Playground(int p, int l, int h){
		super(p, l, h);
	}

	@Override
	public void focus(){
		System.out.printf("\nThe length of the selected playground is: %s\n", this.length);
	}

	/**
	* Prints building type.
	*/

	@Override
	public void get() {
		System.out.printf("\n Playground\n");
	}

	/**
	* To check if the class is playground or not.
	*/

	@Override
	public boolean check() {return true;}

	@Override
	public Playground clone() {return new Playground(this.position, this.length, this.height);}

	@Override
	public String toString() {return String.format("position: %d, length: %d, height: %d",this.position, this.length, this.height);}

	@Override
	public boolean equals(Object o) {

		if (!(o instanceof Playground)) {
			return false;
		}
		
		Playground playground = (Playground) o;

		if (o == this)
		return position == playground.position && length == playground.length && height == playground.height;

		return false;
	}

	@Override
	public int hashCode() {
		return Objects.hash(position, length, height);
	}
	
}