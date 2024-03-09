/**
* Contains driver and menu methods to coordinate
* necessary operations for complete functionality.
* 
* @author  Siyar Tarik
*/

import java.io.IOException;
import java.util.*;
import src.*;
import src.buildings.*;

public class Silhouette {

	public static void main(String args[]) {

		test(200);	// tests certain methods and measures the time
		//driver();
		//menu();
	}

	public static void test(int elements) {

		long startTime = System.nanoTime();

		StreetLLs buildings = new StreetLLs();
		try{  
			buildings = new StreetLLs(10*elements);
   		}
   		catch(Exception e) {
   			System.out.print(e);
   		}

   		for (int i = 0; i < elements; ++i) {
			buildings.add(new House(10*i+4, 5, 5, 3, "test", "test"), true);
			buildings.add(new House(10*i+1, 5, 5, 3, "test", "test"), false);
   		}

   		long stopTime = System.nanoTime();

   		System.out.printf("\nTime for add method with %d elements in milliseconds:", elements);
   		System.out.println( (stopTime - startTime) / 1000000 );

   		startTime = System.nanoTime();

   		for (int i = 0; i < elements; ++i) {
			try {
			buildings.get(i, true).focus();
			}
   			catch(Exception e) {
   				System.out.print(e);
   			}
			try {
			buildings.get(i, false).focus();
			}
   			catch(Exception e) {
   				System.out.print(e);
   			}
   		}

   		stopTime = System.nanoTime();

   		System.out.printf("\nTime for get method with %d elements in milliseconds:", elements);
   		System.out.println( (stopTime - startTime) / 1000000 );

   		startTime = System.nanoTime();
		
		buildings.draw();	

   		stopTime = System.nanoTime();

   		System.out.printf("\nTime for silhouette to be drawn with %d elements in milliseconds:", elements);
   		System.out.println( (stopTime - startTime) / 1000000 );

   		startTime = System.nanoTime();

   		for (int i = 0; i < elements; ++i) {
			try {
				buildings.remove(0, true);
			}
   			catch(Exception e) {
   				System.out.print(e);
   			}
			try {
				buildings.remove(0, false);
			}
   			catch(Exception e) {
   				System.out.print(e);
   			}
   		}

   		stopTime = System.nanoTime();

   		System.out.printf("\nTime for remove method with %d elements in microseconds:", elements);
   		System.out.println( (stopTime - startTime) / 1000 );

	}

	public static void driver() {

		StreetLLs buildings = new StreetLLs();	// Street of length 50 is created
		try{  
			buildings = new StreetLLs(50);
   		}
   		catch(Exception e) {	// if invalid size detected (less than 20)
   			System.out.print(e);
   		}

		buildings.add(new House(1, 5, 5, 3, "red", "ahmet"), true);	// 4 different buildings added
		buildings.add(new Office(34, 10, 10, "IT", "fatih"), true);
		buildings.add(new Market(20, 5, 12, "10.00", "22.00", "BIM"), false);
		buildings.add(new Playground(40, 6, 2), false);

		buildings.draw();

		buildings.add(new House(6, 5, 5, 3, "green", "Azat"), false);
		buildings.add(new Playground(40, 5, 2), false);	// this one is not added since it overlaps with other buildings.
	  	
		buildings.remaining();	// testing
		buildings.list();
		buildings.ratio();
		buildings.total();

		buildings.draw();	
		
		try {
			buildings.remove(0, true);
		}
   		catch(Exception e) {	// if invalid index detected
   			System.out.print(e);
   		}
		buildings.remaining();	// testing
		buildings.list();

		buildings.ratio();
		buildings.total();
		buildings.draw();	// removal is done correctly

		try {
			buildings.remove(0, true);
		}
   		catch(Exception e) {	// if invalid index detected
   			System.out.print(e);
   		}	

		buildings.draw();	// removal is done correctly

		try{
		buildings.get(1, false).focus();	// focus used on a building
		}
   		catch(Exception e) {	// if invalid index detected
   			System.out.print(e);
   		}

		System.out.print("\n====END OF TEST====\n");	// Test is done
	}

	public static void menu() {

		Scanner scanner = new Scanner(System.in);
		int choice = 1;
		enum Choice {
			QUIT,
			EDIT,
			VIEW,
			DEFAULT
		}

		System.out.print("\nHi, There!\nWelcome to the \"Silhouette of the street.\"\n");	// Asking for size of the street
		System.out.print("\nEnter a size for the street (minimum 20): "); int size = scanner.nextInt(); StreetLLs buildings = new StreetLLs();

    	try{  
			buildings = new StreetLLs(size);

   		}
   		catch(Exception e) {	// if invalid size detected (less than 20)
   			System.out.print(e);
   		}

		while( choice != 0 ) {
			
			System.out.print("\n1-For edit mode,\n2-For view mode,\n0-QUIT.\n\nYour choice: ");	choice = scanner.nextInt();

			if ( choice > 2 || choice < 0 ) choice = 3;		// To not go out of bounds in the enum "Choice", invalid inputs are defaulted

			switch(Choice.values()[choice]) {	// For the rest of the code following 'switch' blocks will provide sufficient self-explanation
	
			case EDIT:
				edit(buildings);
			break;
			case VIEW:
				view(buildings);
			break;
			case QUIT:
				System.out.print("Program is being terminated...\n");
			break;
			case DEFAULT:
				System.out.print("Invalid Input!\n");
	        break;
			}
    	}
	}

	public static void edit(StreetLLs buildings){
	
		Scanner scanner = new Scanner(System.in);
		int add = 5, menu = 3;
		boolean side;	// false/'0' for left, true/'1' for right
		enum Menu {
			EXIT,
			ADD,
			REMOVE,
			DEFAULT
		}
		enum Buildings {
			EXIT,
			HOUSE,
			OFFICE,
			MARKET,
			PLAYGROUND,
			DEFAULT
		}

		while( menu == 3 ) {
			
			System.out.print("1-To add\n2-To remove\n0-To Exit.\n\nYour choice: ");	menu = scanner.nextInt();

			if ( menu > 2 || menu < 0 ) menu = 3;

			switch(Menu.values()[menu]) {

			case REMOVE:
				System.out.print("\nWhich side of the street contains the building to remove?\n");
				System.out.print("0-To left, 1-To right: ");	side = scanner.nextInt() != 0;	// tiny bit of special operation to nat go out of bounds with boolean type
				System.out.print("\nIndex of the building: "); 	int index = scanner.nextInt();	// essentially all of values out of 0 is defaulted to 1 or "true"
				
				try {
					buildings.remove(index, side);
				}
   				catch(Exception e) {	// if invalid index detected
   					System.out.print(e);
   				}
			break;
			case ADD:
				int length, height, position; String owner;	// Multiple use-case variables

				System.out.print("\nWhich side of the street will get the new building?\n");
				System.out.print("0-To left, 1-To right: ");	side = scanner.nextInt() != 0;	// false/'0' for left, true/'1' for right
		
				System.out.print("\nWhich type of building would you like to add to the \"Silhouette of the street.\"\n");
		
				while( add == 5 ) {
					
					System.out.print("1-House\n2-Office\n3-Market\n4-Playground\n0-To Exit.\n\nYour choice: ");	add = scanner.nextInt();
		
					if ( add > 4 || add < 0 ) add = 5;
		
					switch(Buildings.values()[add]) {
			
					case HOUSE:
						System.out.print("\nPosition of the house: "); position = scanner.nextInt();
						System.out.print("\nLength of the house: "); length = scanner.nextInt();
						System.out.print("\nHeight of the house: "); height = scanner.nextInt();
						System.out.print("\nRoom count of the house: "); int room = scanner.nextInt(); String color = scanner.nextLine();
						System.out.print("\nColor of the house: "); color = scanner.nextLine();
						System.out.print("\nOwner of the house: "); owner = scanner.nextLine();
						buildings.add(new House(position, length, height, room, color, owner), side);
					break;
					case OFFICE:
						System.out.print("\nPosition of the office: "); position = scanner.nextInt();
						System.out.print("\nLength of the office: "); length = scanner.nextInt();
						System.out.print("\nHeight of the office: "); height = scanner.nextInt(); String job = scanner.nextLine();
						System.out.print("\nJob type of the office: "); job = scanner.nextLine();
						System.out.print("\nOwner of the office: "); owner = scanner.nextLine();
						buildings.add(new Office(position, length, height, job, owner), side);
					break;
					case MARKET:
						System.out.print("\nPosition of the market: "); position = scanner.nextInt();
						System.out.print("\nLength of the market: "); length = scanner.nextInt();
						System.out.print("\nHeight of the market: "); height = scanner.nextInt(); String opening = scanner.nextLine();
						System.out.print("\nOpening time of the market: "); opening = scanner.nextLine();
						System.out.print("\nClosing time of the market: "); String closing = scanner.nextLine();
						System.out.print("\nOwner of the market: "); owner = scanner.nextLine();
						buildings.add(new Market(position, length, height, opening, closing, owner), side);
					break;
					case PLAYGROUND:
						System.out.print("\nPosition of the playground: "); position = scanner.nextInt();
						System.out.print("\nLength of the playground: "); length = scanner.nextInt();
						System.out.print("\nHeight of the playground: "); height = scanner.nextInt();
						buildings.add(new Playground(position, length, height), side);
					break;
					case EXIT:

					break;
					case DEFAULT:
						System.out.print("Invalid Input!");
	    		    break;
					}
				}
			break;
			}
		}
    }

    public static void view(StreetLLs buildings){
	
		Scanner scanner = new Scanner(System.in);
		int menu = 6;
		boolean side;	// false/'0' for left, true/'1' for right
		enum Menu {
			EXIT,
			REMAINING,
			LIST,
			RATIO,
			TOTAL,
			DRAW,
			DEFAULT
		}

		while( menu == 6 ) {
			
			System.out.print("\n1-To display the total remaining length of lands on the street.");
			System.out.print("\n2-To display the list of buildings on the street.");
			System.out.print("\n3-To display the number and ratio of length of playgrounds in the street.");
			System.out.print("\n4-To calculate the total length of street occupied by the market(s), house(s) or office(s).");
			System.out.print("\n5-To display the \"Silhouette of the street.\".");
			System.out.print("\n0-To Exit.\n\nYour choice: ");	menu = scanner.nextInt();

			if ( menu > 5 || menu < 0 ) menu = 6;

			switch(Menu.values()[menu]) {

			case REMAINING:
				buildings.remaining();
			break;
			case LIST:
				buildings.list();
			break;
			case RATIO:
				buildings.ratio();
			break;
			case TOTAL:
				buildings.total();
			break;
			case DRAW:
				buildings.draw();
			break;
			case EXIT:
			break;
			case DEFAULT:
				System.out.print("\nInvalid Input!\n");
			break;
			
			}
		}
    }
}