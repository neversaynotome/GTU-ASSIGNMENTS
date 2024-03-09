package src.buildings;

/**
* Office class for offices.
*/

import java.util.*;

public class Office extends Building implements Cloneable {

	public Office(int p, int l, int h, String j, String o){

		super(p, l, h);
		job = j;
		owner = o;
	}

	private String job;
	private String owner;

	@Override
	public void focus(){
		System.out.printf("\nThe job type of the selected office is: %s\n", this.job);
	}

	/**
	* Prints building type.
	*/

	@Override
	public void get() {
		System.out.printf("\n Office\n");
	}

	/**
	* To check if the class is playground or not.
	*/

	@Override
	public boolean check() {return false;}

	@Override
	public Office clone() {return new Office(this.position, this.length, this.height, this.job, this.owner);}

	@Override
	public String toString() {return String.format("position: %d, length: %d, height: %d, job: %s, owner: %s",this.position, this.length, this.height, this.job, this.owner);}

	@Override
	public boolean equals(Object o) {

		if (!(o instanceof Office))
			return false;

		Office office = (Office) o;
		if (o == this)
		return position == office.position && length == office.length && height == office.height && Objects.equals(job, office.job) && Objects.equals(owner, office.owner);
	
		return false;
	}

	@Override
	public int hashCode() {
		return Objects.hash(position, length, height, job, owner);
	}
}