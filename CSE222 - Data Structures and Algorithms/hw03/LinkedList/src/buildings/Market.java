package src.buildings;

/**
* Market class for markets.
*/

import java.util.*;

public class Market extends Building implements Cloneable {

	public Market(int p, int l, int h, String op, String cl, String ow){
		
		super(p, l, h);
		opening = op;
		closing = cl;
		owner = ow;
	}

	private String opening;
	private String closing;
	private String owner;

	@Override
	public void focus(){
		System.out.printf("\nThe closing time of the selected market is: %s\n", this.closing);
	}

	/**
	* Prints building type.
	*/

	@Override
	public void get() {
		System.out.printf("\n Market\n");
	}

	/**
	* To check if the class is playground or not.
	*/

	@Override
	public boolean check() {return false;}

	@Override
	public Market clone() {return new Market(this.position, this.length, this.height, this.opening, this.closing, this.owner);}

	@Override
	public String toString() {return String.format("position: %d, length: %d, height: %d, opening: %s, closing: %s, owner: %s",this.position, this.length, this.height, this.opening, this.closing, this.owner);}

	@Override
	public boolean equals(Object o) {

		if (!(o instanceof Market))
			return false;

		Market market = (Market) o;
		if (o == this)
		return position == market.position && length == market.length && height == market.height && Objects.equals(opening, market.opening) && Objects.equals(closing, market.closing) && Objects.equals(owner, market.owner);

		return false;
	}

	@Override
	public int hashCode() {
		return Objects.hash(position, length, height, opening, closing, owner);
	}

}