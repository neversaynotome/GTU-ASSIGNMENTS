package src;

/**
* Sorter and three implementations that are asked for
*/

import java.util.*;
import java.lang.*;

public class Sorter {

	public Sorter(int size) {
		data = new int[size];

		Random rand = new Random();

		for (int i = 0; i < data.length ; ++i) {
			data[i] = rand.nextInt(data.length);
		}
		//System.out.printf("\n%d\n", data.length); // TODO
	}

	public void Mixer() {

	}

	public void MergeSort() {
		sort(0, data.length - 1);
	}

	private void sort(int l, int r) {
        if (l < r) {
            // Find the middle point
            int m =l+ (r-l)/2;
  
            // Sort first and second halves
            sort(l, m);
            sort(m + 1, r);
  
            // Merge the sorted halves
            merge(l, m, r);
        }
    }

    private void merge(int l, int m, int r) {
        // Find sizes of two subdataays to be merged
        int n1 = m - l + 1;
        int n2 = r - m;
  
        /* Create temp dataays */
        int L[] = new int[n1];
        int R[] = new int[n2];
  
        /*Copy data to temp dataays*/
        for (int i = 0; i < n1; ++i)
            L[i] = data[l + i];
        for (int j = 0; j < n2; ++j)
            R[j] = data[m + 1 + j];
  
        /* Merge the temp dataays */
  
        // Initial indexes of first and second subdataays
        int i = 0, j = 0;
  
        // Initial index of merged subdataay dataay
        int k = l;
        while (i < n1 && j < n2) {
            if (L[i] < R[j]) {
                data[k] = L[i];
                i++;
            }
            else {
                data[k] = R[j];
                j++;
            }
            k++;
        }
  
        /* Copy remaining elements of L[] if any */
        while (i < n1) {
            data[k] = L[i];
            i++;
            k++;
        }
  
        /* Copy remaining elements of R[] if any */
        while (j < n2) {
            data[k] = R[j];
            j++;
            k++;
        }
    }

	public void QuickSort() {
		quickSort(0, data.length - 1);
	}

	private void quickSort(int low, int high) {

    	if (low < high) {
         
        	// pi is partitioning index, data[p]
        	// is now at right place
        	int pi = partition(low, high);
 
        	// Separately sort elements before
        	// partition and after partition
        	quickSort(low, pi - 1);
        	quickSort(pi + 1, high);
    	}
	}

	private int partition(int low, int high) {
     
	    int pivot = data[high];
     
    	// Index of smaller element and
    	// indicates the right position
    	// of pivot found so far
    	int i = (low - 1);
 
    	for(int j = low; j <= high - 1; j++) {
         
        	// If current element is smaller
        	// than the pivot
        	if (data[j] < pivot) {
             
            // Increment index of
            // smaller element
            i++;
            swap(i, j);
        	}
    	}
	    swap(i + 1, high);
	    return (i + 1);
	}

	private void swap(int i, int j) {
    	int temp = data[i];
    	data[i] = data[j];
    	data[j] = temp;
	}

	public void new_sort() {
		new_sort(0, data.length);
	}

	private void new_sort(int head, int tail) {

		int min = data[head], max = data[tail];
		
		if (head <= tail) {
			min_max_finder(head, tail, min, max);
			swapIndex(head, min);
			swapIndex(tail, max);
			new_sort(head + 1, tail - 1);
		}

	}

	private void min_max_finder(int head, int tail, int min, int max) {
		
		if (head <= tail) {
			min_max_finder(head + 1, tail / 2, min, max);
			min_max_finder(tail / 2 + 1, tail - 1, min, max);
			
			if (data[head] < min)
				min = data[head];
			if (data[tail] < min)
				min = data[tail];

			if (data[head] > max)
				max = data[head];
			if (data[tail] >max)
				max = data[tail];
		}
	}

	private void swapIndex(int index, int item) {

		int temp = data[index];
		data[index] = item;
		item = temp;
	}

	private int[] data;
}