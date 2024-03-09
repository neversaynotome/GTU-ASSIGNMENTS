/**
* Testing for for Q4
* 
* @author  Siyar Tarik
*/

import java.lang.*;
import java.util.*;
import src.*;

public class Q7test {

	public static void main(String args[]) {

		BinaryTree<Integer> myBT = new BinaryTree<>();
		Integer [] myArray = new Integer[5];

		myArray[0] = 30;
		myArray[1] = 10;
		myArray[2] = 20;
		myArray[3] = 40;
		myArray[4] = 50;
		
		myBT.add(6);
		myBT.add(1);
		myBT.add(4);
		myBT.add(10);
		myBT.add(15);

		System.out.println("Printing the starting Binary Tree:");
		System.out.println(myBT);

		myBT.constructBST(myArray);

		System.out.println("Printing the Binary Tree after BST conversion happened:");
		System.out.println(myBT);

		BinarySearchTree<Integer> myBST = new BinarySearchTree<>();

		for (int i = 0;i < 10; ++i)
			myBST.add(i);

		System.out.println("Printing a very unbalanced Binary Search Tree:");
		System.out.println(myBST);

		AVLTree myAVL = BSTtoAVL(myBST);
	
		System.out.println("Printing the AVL Tree with elements of the Binary Search Tree:");
		System.out.println(myAVL);
	}

	public static AVLTree BSTtoAVL(BinarySearchTree<Integer> data) {	// creates an AVL tree with a BST
	
		AVLTree myAVL = new AVLTree();
	
		List<Integer> BTarray = data.getArray();

		for (Integer temp : BTarray)
			myAVL.insert(temp);

		return myAVL;
	}
}