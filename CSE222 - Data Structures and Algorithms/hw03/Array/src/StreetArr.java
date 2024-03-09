package src;

/**
* Container class for buildings, name is partly self-explanatory.
* Dynamically stores "Building"s using only standart arrays.
*/

import src.buildings.*;
import java.util.*;
import java.io.IOException;

public class StreetArr {

	/**
	* Constructor which gets the size parameter.
	* StreetArr size is defaulted to minimum value of 20,
	* if exceeded throws an exception.
	* @param streetSize minimum value of 20
	*/

	public StreetArr(int streetSize) throws IOException {

	if ( streetSize < 20 ) {

		streetSize = 20;
		throw new IOException("\nInvalid size detected, size re-arranged to minimum allowed (20).\n");
	}
	street = streetSize;
	}

	public StreetArr() {street = 20;}

	/**
	* Coordination for dynamic storage, re-allocs when necessary
	* and doubles its size.
	* @param toAdd Building to add to the street
	* @param side to left or right of the street?
	*/

	public void add(Building toAdd, boolean side) {

		boolean error = false;

		try {
			isAvailable(toAdd, side);
		}
		catch(Exception e) {	// if invalid size detected
   			System.out.print(e);
   			error = true;
   		}

		if ( !(error) )
			if (side)				// for "right"
				if (capacityR == 0) {					// Initialize if "capacity" is 0
	
				right = new Building[1];
				right[0] = toAdd;
				this.sizeR++; this.capacityR++;
				}
				else if (this.capacityR == this.sizeR) {		// no more capacity left
		
					Building[] temp = new Building[this.capacityR];
	
					for (int i = 0; i < this.sizeR; ++i)
						temp[i] = right[i];	// Copying older
		
					this.capacityR *= 2;
					right = new Building[this.capacityR];
			
					for (int i = 0; i < this.sizeR; ++i)
						right[i] = temp[i];
			
					right[this.sizeR++] = toAdd;
		
				}
				else 
					right[this.sizeR++] = toAdd;		// Array has appropiate place for new element so just add it

			else 					// for "left"
				if (capacityL == 0) {					// Initialize if "capacity" is 0
	
				left = new Building[1];
				left[0] = toAdd;
				this.sizeL++; this.capacityL++;
				}
				else if (this.capacityL == this.sizeL) {		// no more capacity left
		
					Building[] temp = new Building[this.capacityL];
	
					for (int i = 0; i < this.sizeL; ++i)
						temp[i] = left[i];	// Copying older
		
					this.capacityL *= 2;
					left = new Building[this.capacityL];
			
					for (int i = 0; i < this.sizeL; ++i)
						left[i] = temp[i];
			
					left[this.sizeL++] = toAdd;
		
				}
				else 
					left[this.sizeL++] = toAdd;		// Array has appropiate place for new element so just add it
	}

	/**
	* Sees if designated place is available for the new building.
	* 
	* @param toAdd Building to add to the street
	* @param side to left or right of the street?
	*/

	private void isAvailable(Building toAdd, boolean side) throws IOException {	// all expections are self-explanatory

		if (toAdd.len() + toAdd.pos() > street) throw new IOException("Unable to add the building, building is out of the street!");
		
		if (side) {										// if spaces overlap
			for (int i = 0; i < sizeR; ++i)
				for (int j = toAdd.pos(); j <= ( toAdd.pos() + toAdd.len() ); ++j)
					if ( j <= ( right[i].pos() + right[i].len() ) && j >= right[i].pos() )
						throw new IOException("Unable to add the building, designated space overlaps other building(s)!");
		}		
		else {
			for (int k = 0; k < sizeL; ++k)
				for (int l = toAdd.pos(); l <= ( toAdd.pos() + toAdd.len() ); ++l)
					if ( l <= ( left[k].pos() + left[k].len() ) && l >= left[k].pos() )
						throw new IOException("Unable to add the building, designated space overlaps other building(s)!");
		}	
	}

	/**
	* To remove the building in the array.
	* 
	* @param index Index to remove contents of
	* @param side to left or right of the street?
	*/

	public void remove(int index, boolean side) throws IOException {
		
		if (index < 0) throw new IOException("Invalid index!");

		if (side)
			if (index >= sizeR) throw new IOException("Index out of bounds!");
		else
			if (index >= sizeL) throw new IOException("Index out of bounds!");

		if (side) {

		for (int i = index; i < sizeR-1; ++i)	// just skip the index and copy the rest to "i-1"
			right[i] = right[i+1];
		
		if (sizeR > 0)	--sizeR; // Element removed sucessfully
		}
		else {

		for (int i = index; i < sizeL-1; ++i)
			left[i] = left[i+1];
		
		if (sizeL > 0)	--sizeL; // Element removed sucessfully
		}
	}

	/**
	* Returns reference if available.
	* 
	* @param index -th element will be returned
	* @param side to left or right of the street?
	*/

	public Building get(int index, boolean side) throws IOException {

		if (index < 0) throw new IOException("Invalid index!");

		if (side)
			if (index >= sizeR || right == null) throw new IOException("Index out of bounds!");
		else
			if (index >= sizeL || left == null) throw new IOException("Index out of bounds!");

		if (side) return right[index];
		else	  return left[index];
	}

	/**
	* Prints remaining street space.
	*/

	public void remaining(){

		int used = 0;

		for (int i = 0; i < sizeR; ++i)
			used += right[i].len();
		for (int i = 0; i < sizeL; ++i)
			used += left[i].len();

		System.out.printf("\nRemaining street space is: %d\n", (2 * this.street) - used); // Two sides of the street
	}

	/**
	* Lists buildings by type.
	*/

	public void list(){
		
		System.out.printf("\nBuildings on the right:\n");
		for (int i = 0; i < sizeR; ++i)
			right[i].get();

		System.out.printf("\nBuildings on the left:\n");
		for (int i = 0; i < sizeL; ++i)
			left[i].get();
	}

	/**
	* Prints the ratio of the space occupied by playgrounds to the total space occupied.
	*/

	public void ratio(){

		double used = 0, notUsed = 0;

		for (int i = 0; i < sizeR; ++i) {
			if (right[i].check())
				used += right[i].len();
			else
				notUsed += right[i].len();
		}
		for (int i = 0; i < sizeL; ++i) {
			if (left[i].check())
				used += left[i].len();
			else
				notUsed += left[i].len();
		}
		System.out.printf("\n%%");	if ( (used + notUsed) == 0) notUsed = 1;	// To avoid division by 0
		System.out.printf("%.0f is the ratio of the space occupied by playgrounds to the total space occupied.\n", (used / (used + notUsed)) * 100 ); 
	}

	/**
	* Prints the total street space occupied by houses, markets & offices.
	*/

	public void total(){
		
		int used = 0;

		for (int i = 0; i < sizeR; ++i)
			if ( !(right[i].check()) )
				used += right[i].len();

		for (int i = 0; i < sizeL; ++i)
			if ( !(left[i].check()) )
				used += left[i].len();

		System.out.printf("\nTotal street space occupied by houses, markets & offices is: %d\n", used); // Two sides of the street

	}

	/**
	* Prints the silhouette of the street.
	*/

	public void draw(){

		System.out.printf("\n\n\n\"Silhouette of the street\":\n");
		
		int printSize = 0;	// to know how long of the street is going to be printed

		for (int i = 0; i < sizeR; ++i)						// checking to see which "position" is the last piece of building will be printed
			if ( right[i].pos() + right[i].len() > printSize )
				printSize = right[i].pos() + right[i].len();
		for (int i = 0; i < sizeL; ++i)
			if ( left[i].pos() + left[i].len() > printSize )
				printSize = left[i].pos() + left[i].len();

		++printSize;					// increase of 1 is necessary since for proper silhouette one extra space is needed

		for (int i = 20; i > 0; --i){	// 20 is max height allowed
			for (int j = 0; j < printSize; ++j)
				System.out.printf("%s", decider(i, j) );
			System.out.printf("\n");
		}	
		for (int i = 0; i < printSize; ++i) {
			System.out.printf("=");
		}
		System.out.printf("\n");
	}

	/**
	* Decide what is printed where.
	* "count" variable is for walls just behind eachother,
	* so buildings next to eachother don't have walls betwenn them.
	* @param row current row placement of the cursor
	* @param column current column placement of the cursor
	* @return 		character to be printed
	*/

	private String decider(int row, int column){

		String str = " "; int count = 0;

		for (int i = 0; i < sizeR; ++i) {			// if columns and rows exactly match outlines of the building appropiate character is selected
			if ( right[i].hei() == row && ( column > right[i].pos() && column < ( right[i].pos() + right[i].len() ) ) ) {str = "_"; ++count;}
			if ( right[i].pos() == column && row < right[i].hei() ) {str = "|"; ++count;}
			if ( ( right[i].pos() + right[i].len() ) == column && row < right[i].hei() ) {str = "|"; ++count;}
		}
		for (int i = 0; i < sizeL; ++i) {
			if ( left[i].hei() == row && ( column > left[i].pos() && column < (left[i].pos() + left[i].len()) ) ) {str = "_"; ++count;}
			if ( left[i].pos() == column && row < left[i].hei() ) {str = "|"; ++count;}
			if ( ( left[i].pos() + left[i].len() ) == column && row < left[i].hei() ) {str = "|"; ++count;}
		}
													// unless " " (empty space) is printed
		if ( str.equals("|") ) {		// If a building has a higher building next to it (to front or back), then outline (walls) of that exact part is not printed

			for (int i = 0; i < sizeR; ++i) {
				if ( ( column > right[i].pos() && column < (right[i].pos() + right[i].len()) ) && right[i].hei() > row ) str = " ";
				if ( ( column > right[i].pos() && column < (right[i].pos() + right[i].len()) ) && right[i].hei() == row ) str = "_";
			}

			for (int i = 0; i < sizeL; ++i) {
				if ( ( column > left[i].pos() && column < (left[i].pos() + left[i].len()) ) && left[i].hei() > row) str = " ";
				if ( ( column > left[i].pos() && column < (left[i].pos() + left[i].len()) ) && left[i].hei() == row) str = "_";
			}
		}

		if ( str.equals("_") ) {		// same with "line 312" but for roofs

			for (int i = 0; i < sizeR; ++i) {
				if ( ( column > right[i].pos() && column < (right[i].pos() + right[i].len()) ) && right[i].hei() > row ) str = " ";
			}

			for (int i = 0; i < sizeL; ++i) {
				if ( ( column > left[i].pos() && column < (left[i].pos() + left[i].len()) ) && left[i].hei() > row) str = " ";
			}
		}
		if (count > 1)
			if ( str.equals("|") ) str = " ";	// outlines exactly match then no character is printed for a expected result

		return str;
	}

	private Building[] right = new Building[0]; 
	private Building[] left = new Building[0];
	private int sizeR = 0, capacityR = 0, sizeL = 0, capacityL = 0, street;
}