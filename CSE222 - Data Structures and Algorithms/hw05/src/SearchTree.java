package src;

/**
* SearchTree interface in the book
*/

public interface SearchTree<E> {
	public boolean add(E item);
	public boolean contains(E target);
	public int find(E target);
	public E delete(E target);
	public boolean remove(E target);
}