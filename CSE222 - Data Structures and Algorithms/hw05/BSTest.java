/**
* Testing for for Q4
* 
* @author  Siyar Tarik
*/

import java.lang.*;
import src.*;

public class BSTest {

	public static void main(String args[]) {

		BinarySearchTree<Integer> data = new BinarySearchTree<>();

		data.add(3);
		data.add(2);
		data.add(4);
		data.add(5);
		data.add(10);

		System.out.printf("\n3, 2, 4, 5 and 10 are added to the tree.\n");
		
		System.out.printf("\n\n");
		data.getArray();

		if (data.contains(2) == true)
			System.out.printf("\n2 is in the tree");
			System.out.println(" and its index is: " + data.find(2));

		if (data.contains(9) == false)
			System.out.printf("\n9 is not in the tree.\n");

		data.delete(10);
		System.out.printf("\n10 is removed from the tree.\n");

		if (data.contains(10) == false)
			System.out.printf("\n10 is not in the tree anymore.\n");

		if (data.remove(9) == false);
			System.out.printf("\n9 can't be removed from the tree since it isn't in it.\n");

		System.out.printf("\n\n");
		data.getArray();
		System.out.printf("\n\n");
	}
}