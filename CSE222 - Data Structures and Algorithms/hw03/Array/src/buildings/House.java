package src.buildings;

/**
* House class for houses.
* does exactly what is asked for.
*/

import java.util.*;

public class House extends Building implements Cloneable {

	public House(int p, int l, int h, int n, String c, String o){
		
		super(p, l, h);
		numOfRooms = n;
		color = c;
		owner = o;
	}

	private int numOfRooms;
	private String color;
	private String owner;

	@Override
	public void focus() {
		System.out.printf("\nThe owner of the selected house is: %s\n", this.owner);
	}

	/**
	* Prints building type.
	*/

	@Override
	public void get() {
		System.out.printf("\n House\n");
	}

	/**
	* To check if the class is playground or not.
	*/

	@Override
	public boolean check() {return false;}

	@Override
	public House clone() {return new House(this.position, this.length, this.height, this.numOfRooms, this.color, this.owner);}

	@Override
	public String toString() {return String.format("position: %d, length: %d, height: %d, number of rooms: %d, color: %s, owner: %s",this.position, this.length, this.height, this.numOfRooms, this.color, this.owner);}

	@Override
	public boolean equals(Object o) {

		if (!(o instanceof House))
			return false;
		
		House house = (House) o;
		
		if (o == this)
		return position == house.position && length == house.length && height == house.height && Objects.equals(color, house.color) && numOfRooms == house.numOfRooms && Objects.equals(color, house.color) && Objects.equals(owner, house.owner);
		
		return false;
	}

	@Override
	public int hashCode() {
		return Objects.hash(position, length, height, numOfRooms, color, owner);
	}

}