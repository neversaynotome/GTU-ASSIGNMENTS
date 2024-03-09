package src;

/**
* LDLinkedList's implementation with
* the Node class.
* 
*/

import java.util.*;
import java.io.IOException;

class LDLinkedList<T> extends AbstractList<T> {

	Node<T> head, tail;
	LinkedList< Node<T> > lazy = new LinkedList< Node<T> >();	// holds removed nodes
	int size = 0;
	
	/**
	* Adds an element to the list, initializes
	* a new node if necessary, if not gets one from
	* lazy list and re-uses it.
	*/

	public boolean add(T data) {

		if (head == null) {					// first element is created
			Node<T> node = new Node<>(data, null);
			tail = head = node;
			++size;
		}
		else if(lazy.size() > 0) { 			// if a removed element is in reach then that is used

			Node<T> node = lazy.remove();
			node.setData(data); node.setNext(null);
			tail.setNext(node);
			tail = node;
			++size;		}
		else {								// new node is initialized if none is available
			Node<T> node = new Node<>(data, null);
			tail.setNext(node);
			tail = node;
			++size;
		}
		return true;
	}
	
	/**
	* Removes (transfers) elements to lazy list.
	*/

	public T remove(int index) {

		if (size == 0)		// special cases
			return null;
		if (size == 1) {
			lazy.add(head);
			tail = head = null;
			--size;
			return lazy.getLast().getData();
		}

		if (index >= 0 || index < size)
			if (index == 0) {			// head is transfered to lazy list
				lazy.add(head);
				head = head.getNext();
			}
			else if (index == 1) {		// node next to head is transfered
				lazy.add(head.getNext());
				head.setNext(head.getNext().getNext());
			}
			else {
				Node<T> node = head;	// if index is bigger than two this operation transfers the node
				for (int i = 0; i < index-1; ++i)
					node = node.getNext();
				lazy.add(node.getNext());
				node.setNext(node.getNext().getNext());
			}
		--size;
		return lazy.getLast().getData();
	}

	public int size() {
		return size;
	}

	/**
	* Returns the element with the index.
	*/

	public T get(int index) {

		if (index >= 0 || index < size){
			Node<T> node = head;
			for (int i = 0; i < index; ++i)
				node = node.getNext();
			
			return node.getData();
		}
		return null;
	}

	public Node<T> getHead() {
		return head;
	}
	
	public Node<T> getTail() {
		return tail;
	}
}

class Node<T> {

	T data;
	Node<T> next;

	public Node(T data, Node<T> next) {
		this.data = data;
		this.next = next;
	}
	
	public void setData(T data) {
		this.data = data;
	}
	
	public void setNext(Node<T> next) {
		this.next = next;
	}
	
	public T getData() {
		return data;
	}
	
	public Node<T> getNext() {
		return next;
	}
}