package src;

/**
* Container class for buildings, name is partly self-explanatory.
* Dynamically stores "Building"s using self-implemented LDLinkedList class.
*/

import src.buildings.*;	// TODO
import java.util.*;
import java.io.IOException;

public class StreetLDLLs {

	/**
	* Constructor which gets the size parameter.
	* Street size is defaulted to minimum value of 20,
	* if exceeded throws an exception.
	* @param streetSize minimum value of 20
	*/

	public StreetLDLLs(int streetSize) throws IOException {

	if ( streetSize < 20 ) {

		streetSize = 20;
		throw new IOException("\nInvalid size detected, size re-arranged to minimum allowed (20).\n");
	}
	street = streetSize;
	}

	public StreetLDLLs() {street = 20;}

	/**
	* Adds the objects to LDLinkedLists that hold objects. 
	* @param toAdd Building to add to the street
	* @param side to left or right of the street?
	*/

	public void add(Building toAdd, boolean side) {

		boolean error = false;

		try {
			isAvailable(toAdd, side);
		}
		catch(Exception e) {	// if invalid building placement detected
   			System.out.print(e);
   			error = true;
   		}

		if ( !(error) )
			if (side)				// for "right"
				right.add(toAdd);
			else 					// for "left"
				left.add(toAdd);
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
			for (int i = 0; i < right.size(); ++i)
				for (int j = toAdd.pos(); j <= ( toAdd.pos() + toAdd.len() ); ++j)
					if ( j <= ( right.get(i).pos() + right.get(i).len() ) && j >= right.get(i).pos() )
						throw new IOException("Unable to add the building, designated space overlaps other building(s)!");
		}		
		else {
			for (int k = 0; k < left.size(); ++k)
				for (int l = toAdd.pos(); l <= ( toAdd.pos() + toAdd.len() ); ++l)
					if ( l <= ( left.get(k).pos() + left.get(k).len() ) && l >= left.get(k).pos() )
						throw new IOException("Unable to add the building, designated space overlaps other building(s)!");
		}	
	}

	/**
	* To remove the building in the LDLinkedList.
	* 
	* @param index Index to remove contents of
	* @param side to left or right of the street?
	*/

	public void remove(int index, boolean side) throws IOException {

		if (side)
			if (index < 0 || index >= right.size()) throw new IOException("Index out of bounds!");
		else
			if (index < 0 || index >= left.size()) throw new IOException("Index out of bounds!");

		if (side)
			right.remove(index);
		else
			left.remove(index);
	}

	/**
	* Returns reference if available.
	* 
	* @param index -th element will be returned
	* @param side to left or right of the street?
	*/

	public Building get(int index, boolean side) {

		if (side) return right.get(index);
		else	  return left.get(index);
	}

	/**
	* Prints remaining street space.
	*/

	public void remaining(){

		int used = 0;

		for (int i = 0; i < right.size(); ++i)
			used += right.get(i).len();
		for (int i = 0; i < left.size(); ++i)
			used += left.get(i).len();

		System.out.printf("\nRemaining street space is: %d\n", (2 * street) - used); // Two sides of the street
	}

	/**
	* Lists buildings by type.
	*/

	public void list(){
		
		System.out.printf("\nBuildings on the right:\n");
		for (int i = 0; i < right.size(); ++i)
			right.get(i).get();

		System.out.printf("\nBuildings on the left:\n");
		for (int i = 0; i < left.size(); ++i)
			left.get(i).get();
	}

	/**
	* Prints the ratio of the space occupied by playgrounds to the total space occupied.
	*/

	public void ratio(){

		double used = 0, notUsed = 0;

		for (int i = 0; i < right.size(); ++i) {
			if (right.get(i).check())
				used += right.get(i).len();
			else
				notUsed += right.get(i).len();
		}
		for (int i = 0; i < left.size(); ++i) {
			if (left.get(i).check())
				used += left.get(i).len();
			else
				notUsed += left.get(i).len();
		}
		System.out.printf("\n%%");	if ( (used + notUsed) == 0) notUsed = 1;	// To avoid division by 0
		System.out.printf("%.0f is the ratio of the space occupied by playgrounds to the total space occupied.\n", (used / (used + notUsed)) * 100 ); 
	}

	/**
	* Prints the total street space occupied by houses, markets & offices.
	*/

	public void total(){
		
		int used = 0;

		for (int i = 0; i < right.size(); ++i)
			if ( !(right.get(i).check()) )
				used += right.get(i).len();

		for (int i = 0; i < left.size(); ++i)
			if ( !(left.get(i).check()) )
				used += left.get(i).len();

		System.out.printf("\nTotal street space occupied by houses, markets & offices is: %d\n", used); // Two sides of the street

	}

	/**
	* Prints the silhouette of the street.
	*/

	public void draw(){

		System.out.printf("\n\n\n\"Silhouette of the street\":\n");
		
		int printSize = 0;	// to know how long of the street is going to be printed

		for (int i = 0; i < right.size(); ++i)						// checking to see which "position" is the last piece of building will be printed
			if ( right.get(i).pos() + right.get(i).len() > printSize )
				printSize = right.get(i).pos() + right.get(i).len();
		for (int i = 0; i < left.size(); ++i)
			if ( left.get(i).pos() + left.get(i).len() > printSize )
				printSize = left.get(i).pos() + left.get(i).len();

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

		for (int i = 0; i < right.size(); ++i) {			// if columns and rows exactly match outlines of the building appropiate character is selected
			if ( right.get(i).hei() == row && ( column > right.get(i).pos() && column < ( right.get(i).pos() + right.get(i).len() ) ) ) {str = "_"; ++count;}
			if ( right.get(i).pos() == column && row < right.get(i).hei() ) {str = "|"; ++count;}
			if ( ( right.get(i).pos() + right.get(i).len() ) == column && row < right.get(i).hei() ) {str = "|"; ++count;}
		}
		for (int i = 0; i < left.size(); ++i) {
			if ( left.get(i).hei() == row && ( column > left.get(i).pos() && column < (left.get(i).pos() + left.get(i).len()) ) ) {str = "_"; ++count;}
			if ( left.get(i).pos() == column && row < left.get(i).hei() ) {str = "|"; ++count;}
			if ( ( left.get(i).pos() + left.get(i).len() ) == column && row < left.get(i).hei() ) {str = "|"; ++count;}
		}
													// unless " " (empty space) is printed
		if ( str.equals("|") ) {		// If a building has a higher building next to it (to front or back), then outline (walls) of that exact part is not printed

			for (int i = 0; i < right.size(); ++i) {
				if ( ( column > right.get(i).pos() && column < (right.get(i).pos() + right.get(i).len()) ) && right.get(i).hei() > row ) str = " ";
				if ( ( column > right.get(i).pos() && column < (right.get(i).pos() + right.get(i).len()) ) && right.get(i).hei() == row ) str = "_";
			}

			for (int i = 0; i < left.size(); ++i) {
				if ( ( column > left.get(i).pos() && column < (left.get(i).pos() + left.get(i).len()) ) && left.get(i).hei() > row) str = " ";
				if ( ( column > left.get(i).pos() && column < (left.get(i).pos() + left.get(i).len()) ) && left.get(i).hei() == row) str = "_";
			}
		}

		if ( str.equals("_") ) {		// same with "line 312" but for roofs

			for (int i = 0; i < right.size(); ++i) {
				if ( ( column > right.get(i).pos() && column < (right.get(i).pos() + right.get(i).len()) ) && right.get(i).hei() > row ) str = " ";
			}

			for (int i = 0; i < left.size(); ++i) {
				if ( ( column > left.get(i).pos() && column < (left.get(i).pos() + left.get(i).len()) ) && left.get(i).hei() > row) str = " ";
			}
		}
		if (count > 1)
			if ( str.equals("|") ) str = " ";	// outlines exactly match then no character is printed for a expected result

		return str;
	}

	private LDLinkedList<Building> right = new LDLinkedList<Building>();
	private LDLinkedList<Building> left = new LDLinkedList<Building>();
	private int street;
}