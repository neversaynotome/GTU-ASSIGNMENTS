/**
* Includes tests and implementations of homewrok #4
* 
* @author  Siyar Tarik
*/

import java.lang.*;

public class Recursive {

	public static void main(String args[]) {

		String b = "abcSelamabcaaSelamSelamabcSelam";	

		System.out.printf("\nSecond occurence of \"Selam\" in the bigger string start at index of %d\n", stringFinder(2, 0, b, "Selam"));
		System.out.printf("\nThird occurence of \"abc\" in the bigger string start at index of %d\n", stringFinder(3, 0, b, "abc"));

		int[] sorted = {22, 33, 44, 54, 67, 69, 77, 88, 99};

		System.out.printf("\nThere is %d element between %d and %d.\n", sortedFinder(sorted, 22, 69), 22, 69);
		System.out.printf("\nThere is %d element between %d and %d.\n", sortedFinder(sorted, 33, 88), 33, 88);

		int[] unsorted = {2,5,3,2,8,4,5,8,6,1,9,2,4,4,3,9,6,1,2,5,7,8,3};

		contSum(unsorted, 0, 10);
		System.out.printf("\n\n");

		contSum(unsorted, 0, 9);
		
		System.out.printf("\nResult of the method in question 4 is with 100 and 100: %d\n", foo(30,20));

		System.out.printf("\nResults of question 5 with an array of length 8 and 2 fillers with the length of 3:\n");

		int[] fillArray1 = {0,0,0,0,0,0,0,0};

		color1d(fillArray1, 0, 3, 2);

		System.out.printf("\nResults of question 5 with an array of length 14 and 2 fillers with the length of 4:\n");
		
		int[] fillArray2 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

		color1d(fillArray2, 0, 4, 2);
	}

	/**
	* Finds "i"th occurence of the "small" String in "big" String.
	*
	* @param index This is for search purpose holds a index in String big.
	* @param big String that will be searched in for the substring given.
	* @param small Substring to be found.
	* @param i "i"TH occurence will be returned.
	* @return returns index of the ith occurence of "small" String inside of "big".
	*/

	public static int stringFinder(int i, int index, String big, String small) {	// Q1

		int result = -1;

		if ( small.length() > big.length() - index ) return result;	// if "small" is longer than "big" then no need to look for it

		if ( small.equals( big.substring(index, index + small.length())))	// if a substring matching with "small" is found
			if ( i == 1 ) result = index;								// and also it is the ith ocurrence then result gets the value of that index
			else {
				--i;													// if ith occurrence is not achieved yet next one is going to be searched
				return stringFinder(i, ++index, big, small);
			}
		else
			return stringFinder(i, ++index, big, small);			// substring is not found, next index will be investigated

		return result;
	}

	/**
	* Finds and returns number of element inside of the given bounds.
	*
	* @param array This consains the sorted array.
	* @param first Starting boundary.
	* @param end End of the boundary.
	* @return number of element in the boundary.
	*/

	public static int sortedFinder(int[] array, int first, int last) {	// Q2

		int start = binary(array, first, 0, array.length);	// First index is found
		int end = binary(array, last, 0, array.length);		// Last is found too

		return (end - start) - 1;	// returns number of elements between the bounds
	}

	/**
	* Does binary search on a array to find the given integer.
	*/

	public static int binary(int[] array, int find, int start, int end) {	// a very standart binary implementation

		if (start > end) return -1;

		int middle = (start + end) / 2;
		
		if ( array[middle] == find) return middle;
		if ( array[middle] < find) return binary(array, find, middle + 1, end);
		if ( array[middle] > find) return binary(array, find, start, middle - 1);

		return -1;
	}

	/**
	* Finds and prints contiguous subarrays (if exits) that has the total sum of "compare".
	*
	* @param array This contains the sorted array.
	* @param index Index point to search.
	* @param compare Expected sum of the subarray element.
	*/

	public static void contSum(int[] array, int index, int compare) {	// Q3
		
		if (index < array.length) {									// base case: if index is inside the length of the array
			int result = contFinder(array, index, compare, 0);		// is the starting index is the start of a contigious block with the sum of "compare"
			if (result != -1)
				System.out.printf("\nThere exists an contigous subarray with the sum of %d from: %d, to: %d\n", compare, index, result);
				contSum(array, ++index, compare);		// print the indexes if there exits any and look for the next "index"
		}
	}

	/**
	* Recursively sums contiguous blocks to see if they match "compare".
	*/

	public static int contFinder(int[] array, int index, int compare, int sum) {
		
		if (index >= array.length) return -1;

		int current = array[index] + sum;	// sum holds the summation of contiguous blocks

		if (current == compare) return index;	// if sum is equal to "compare" return the index
		else if (current < compare) return contFinder(array, ++index, compare, current);	// next block is called and summed
		
		return -1;
	}

	/**
	* Algorithm in question 4.
	*/

	public static int foo(int integer1, int integer2) {	// Q4

		if (integer1 < 10 || integer2 < 10)
			return integer1 * integer2;

		//number_of_digit returns the number of digits in an integer
		int n = Math.max(number_of_digits(integer1), number_of_digits(integer2));
		int half = n/2;

		// split_integer splits the integer into returns two integers
		// from the digit at position half. i.e.,
		// first integer = integer / 2^half
		// second integer = integer % 2^half
		int int1 = integer1 / (int) Math.pow(10, (half));
		int int2 = integer1 % (int) Math.pow(10, (half));
		int int3 = integer2 / (int) Math.pow(10, (half));
		int int4 = integer2 % (int) Math.pow(10, (half));

		int sub0 = foo(int2, int4);
		int sub1 = foo( (int2 + int1), (int4 + int3) );
		int sub2 = foo(int1, int3);

		return ( sub2 * (int) Math.pow(10, (2 * half)) ) + ( (sub1 - sub2 - sub0) * (int) Math.pow(10, (half)) ) + (sub0);
	}

	/**
	* Returns number of digits of an int type variable.
	*/

	public static int number_of_digits(int number) {

		if (number < 100000) {
    		if (number < 100) {
    		    if (number < 10) {
    		        return 1;
    		    } else {
    		        return 2;
    		    }
    		} else {
    		    if (number < 1000) {
    		        return 3;
    		    } else {
    		        if (number < 10000) {
    		            return 4;
    		        } else {
    		            return 5;
    		        }
    		    }
    		}
		} else {
		    if (number < 10000000) {
		        if (number < 1000000) {
		            return 6;
		        } else {
		            return 7;
		        }
		    } else {
		        if (number < 100000000) {
		            return 8;
		        } else {
		            if (number < 1000000000) {
		                return 9;
		            } else {
		                return 10;
		            }
		        }
		    }
		}
	}



	/**
	* Finds and prints all subarrays with "fill" length and "count" times in the "array" array.
	*
	* @param array This contains the array with a certain length.
	* @param index Index point for operations.
	* @param fill Length of subarrays.
	* @param count Number of subarrays.
	*/

	public static void color1d(int[] array, int index, int fill, int count) {	// Q5

		if (index <= array.length - fill && array[index] == 0 && array[index + fill - 1] == 0 && count != 0) {
			color1d(array.clone(), index + 1, fill, count);
			--count;
			modifyArray(array, index, index + fill);
			if (count == 0) printArray(array, 0);
			color1d(array, index + fill + 1, fill, count);
		}
	}

	/**
	* Recursively modifies array to add an subarray to it.
	*/

	public static void modifyArray(int[] array, int start, int end) {
		
		if (start < end) {
			array[start] = 1;
			modifyArray(array, ++start, end);
		}
	}

	/**
	* Recursively prints the finished array.
	*/

	public static void printArray(int[] array, int toPrint) {
		
		if (toPrint == 0)
			System.out.printf("\n%d", array[toPrint]);
		else if (toPrint == array.length-1)
			System.out.printf("%d\n", array[toPrint]);
		else if (toPrint < array.length-1)
			System.out.printf("%d", array[toPrint]);

		if (toPrint != array.length)
			printArray(array, ++toPrint);
	}
}