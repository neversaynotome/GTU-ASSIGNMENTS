package src.buildings;

/**
* Base abstract class for all buildings.
*/

import java.util.*;
import java.io.IOException;

public abstract class Building {
	
	public Building(int p, int l, int h) {
		
		try {setter(p, l, h);}
   		catch(Exception e) {	// if invalidity detected
   			System.out.print(e);
   		}
	}

	public void setter(int p, int l, int h) throws IOException {
	
		if ( p <= 0 || l <= 0 || h < 0 ) throw new IOException("Unable to create the building, Invalid dimensions or position!");
		if ( h > 20 ) {
			h = 20;
			throw new IOException("\nInvalid height detected, size re-arranged to maximum allowed (20).\n");
		}
		// Maximum allowed height of a building is 20

		this.position = p;
		this.length = l;
		this.height = h;
	}

	abstract public void focus();

	abstract public void get();

	abstract public boolean check();

	public int pos(){return position;}
	public int len(){return length;}
	public int hei(){return height;}
	protected int position;
	protected int length;
	protected int height;
}