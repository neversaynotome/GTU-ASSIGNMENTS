package src;

/**
* Implementation of q4
*/

import java.util.*;

public class BinarySearchTree<E extends Comparable<E> > implements SearchTree<E> {

	public BinarySearchTree() {

		for (int i = 0; i < tree.length; ++i)
			tree[i] = null;		//filling the array with "null" references
	}

	public void getArray() {

		for (int i = 0; i < tree.length; ++i)
			if (tree[i] != null)	// printing the array
				System.out.println("index:" + i + " data:" + tree[i]);
	}

	/** Starter method add.
	* pre: The object to insert must implement the
	* Comparable interface.
	* @param item The object being inserted
	* @return true if the object is inserted, false
	* if the object already exists in the tree
	*/

	@Override
	public boolean add(E item) {
	 	return add(0, item);
	}

	/** Recursive add method.
	* post: The data field addReturn is set true if the item is added to
	* the tree, false if the item is already in the tree.
	* @param index index of The local root of the subtree
	* @param item The object to be inserted
	* @return true if the object is inserted, false
	* if the object already exists in the tree
	*/

	private boolean add(int index, E item) {

		if (tree[index] == null) {
		 	// item is not in the tree — insert it.
		 	tree[index] = item;
			return true;
		} else if (item.compareTo(tree[index]) == 0) {
		 	// item is equal to tree[index]
		 	return false;
		} else if (item.compareTo(tree[index]) < 0) {
		 	// item is less than tree[index]
		 	return add(index * 2 + 1, item);
		} else {
		 	// item is greater than tree[index]
		 	return add(index * 2 + 2, item);
		}
	}

	/** 
	* Calls find.
	* @param target The Comparable object being sought
	* @return true if found, otherwise false
	*/
	
	@Override
	public boolean contains(E target) {
		if ( find(target) == -1) return false;
		return true;
	}

	/** Starter method find.
	* pre: The target object must implement
	* the Comparable interface.
	* @param target The Comparable object being sought
	* @return The index of the object, if found, otherwise -1
	*/

	@Override
	public int find(E target) {
		return find(0, target);
	}

	/** Recursive find method.
	* @param index The index of local subtree's root
	* @param target The object being sought
	* @return The index of the object, if found, otherwise -1
	*/

	private int find(int index, E target) {

		if (tree[index] == null)
			return -1;
			// Compare the target with the data field at the root.
		int compResult = target.compareTo(tree[index]);

		if (compResult == 0)
			return index;
		else if (compResult < 0)
			return find(index * 2 + 1, target);
		else
			return find(index * 2 + 2, target);
	}
	
	/** Starter method delete.
	* post: The object is not in the tree.
	* @param target The object to be deleted
	* @return The object deleted from the tree
	* or null if the object was not in the tree
	* @throws ClassCastException if target does not implement
	* Comparable
	*/
	
	@Override
	public E delete(E target) {
 		return delete(0, target);
	}
	/** Recursive delete method.
 	* post: The item is not in the tree;
 	* deleteReturn is equal to the deleted item
 	* as it was stored in the tree or null
 	* if the item was not found.
	* @param index The index of the root of the current subtree
 	* @param item The item to be deleted
	* @return The deleted E
	*/
	private E delete(int index, E item) {

 		if (tree[index] == null) {
 			// item is not in the tree.
 			return null;
 		}

 		// Search for item to delete.
 		int compResult = item.compareTo(tree[index]);
 		
 		if (compResult < 0) {
 			// item is smaller than tree[index].
 			tree[index * 2 + 1] = delete(index * 2 + 1, item);
 			return tree[index];
 		} else if (compResult > 0) {
 			// item is larger than tree[index].
 			tree[index * 2 + 2] = delete(index * 2 + 2, item);
 		return tree[index];
 		} else {
 			// item is at local root.
 			if (tree[index * 2 + 1] == null) {
 				// If there is no left child, return right child
 				// which can also be null.
 				return null;
 			} else if (tree[index * 2 + 2] == null) {
 				// If there is no right child, return left child.
 				return null;
 			} else {
 				// Node being deleted has 2 children, replace the data
 				// with inorder predecessor.
 				if (tree[(index * 2 + 1) * 2 + 2] == null) {
 					// The left child has no right child.
 					// Replace the data with the data in the
 					// left child.
 					tree[index] = tree[index * 2 + 1];
 					// Replace the left child with its left child.
 					tree[index * 2 + 1] = tree[(index * 2 + 1) * 2 + 1];
 					return tree[index];
 				} else {
 					// Search for the inorder predecessor (ip) and
 					// replace deleted node's data with ip.
 					tree[index] = findLargestChild(index * 2 + 1);
 					return tree[index];
 				}
 			}
		}
	}

	/** Find the node that is the
	* inorder predecessor and replace it
	* with its left child (if any).
	* post: The inorder predecessor is removed from the tree.
	* @param index The parent of possible inorder
	* predecessor (ip)
	* @return The data in the ip
	*/

	private E findLargestChild(int index) {
		// If the right child has no right child, it is
		// the inorder predecessor.
		if ( tree[(index * 2 + 2) * 2 + 2] == null) {
			E returnValue = tree[index * 2 + 2];
			tree[index * 2 + 2] = tree[(index * 2 + 2) * 2 + 2];
			return returnValue;
		} else {
			return findLargestChild(index * 2 + 2);
		}
	}

	/** 
	* Calls remove.
	* @param target The Comparable object to delete
	* @return true if deleted, otherwise false
	*/

	@Override
	public boolean remove(E target) {
		if ( delete(target) == null) return false;
		return true;
	}
	private E[] tree =  (E[]) new Comparable[100];
}