Program to find out if a given tree is symmetric.

Solution:

NOTE:
	I discovered recursive and iterative solutions(using proper-pairing of elements in the queue data-structure). But I will stick on to the
	approach I discussed with you(Venkat) during the interview, I.e. comparing each levels of the tree. 
	
	- Looks like this method (that i discussed in interview) also has its advantages over other methods in certain cases. Have explained below the analysis aswell in detail.
	
Input : Any Binary Tree.

Assumptions:
1. The Input <Tree> is recieved in the Array representation format with root of the Tree indexed at 0, i.e. Array[0] represents the root node.

Ex : BinaryTree ArrayList[15];
         0  
   1           2
 3   4      5     6
7 8 9 10  11 12 13 14

NOTE: 
1. Size of ArrayList should be in terms of 1, 3, 6 ... , 2^(l+1) - 1 only.
2. Make sure that none of the BinaryTree node-values is "-1" as this is the value to indicate the null nodes.

Each BinaryTreeNode in the array is as follows:

typedef struct tree{
int value;//Tree symmetry is based on this value.
int nodeIndex;//This is the ArrayIndex at which this node is stored. Index=0 indicates the root of the tree.
int leftChildIndex;//This should be initialized to -1 if child doesnot exist, else to "2*nodeIndex + 1". This is not used in below code.
int RightChildIndex;//This should be initialized to -1 if child doesnot exist, else to "2*nodeIndex + 2". This is not used in below code.
}BinaryTree;

bool isSymmetric(BinaryTree ArrayList[])
{
	size = ArrayList.size(); // size is of the order of 2^(l+1) -1 where l is the level of the tree.
 	//above ex: size = 15.
	//Compare last size/2 elements.
	//assert the size is of the order 2^(l+1)-1.
	
	startIndex1 = (size-1)/2;
	endIndex1 = startIndex1 + (size+1)/4 - 1;
	startIndex2 = endIndex1 + 1;
	endIndex2 = size-1;
	
	for(;;)
	{
			for(i = startIndex1, j = endIndex2; i < j          && 
												i <= endIndex1 && 
												j >= startIndex2; i++, j--)
			{
				if (ArrayList[i].value != ArrayList[j].value)		
					return false;
				else
					continue;
			}//This completes processing a particular level. Last level(l=log(N) to start with.
			//Move to level (l-1), change indices accordingly.
			endIndex2 = startIndex1 - 1;
			startIndex1 = endIndex2/2; //I am not considering the fraction values here as endIndices at each level, 
							   //"endIndex2", will be of form 2^(l+1)-2 which is always even.
			endIndex1 = startIndex1 + (endIndex2+2)/4 - 1); //here offset range is 2^(l-1)-1, no need to worry about fractions here aswell for division by 4 
			startIndex2 = endIndex1 + 1;
	
			if (startIndex1 !< endIndex2) //reached the root of the BinaryTree.
				break;
	}
	return true;
}
Time Complexity Analysis:

Case 1: Almost Complete Tree/Complete Tree
	The above algorithm seems to work very well for this case. The size of the Array storing the tree nodes is almost equal to size of tree, 
	i.e. N.
	
Amortized analysis: Creation of tree:
- Takes O(N)	where N is the size of the tree i.e. on an average, each treeNode insertion happens in O(1) time.
- Initially we could have small array size and increase the size when the BinayTreeNode index exceeds the array-bound.
- Reallocate the new size for new array in the order of 2^(l+1)-1, copy the existing treeNodes and again start inserting directly at the appropriate 
	index.
- location of insertion is @ location 2*(index-of-parent)+1 for left child, 2*(index-of-parent)+2 for right child,

Verification of: IsSymmetric(...) happens in O(N) (i.e N/2 comparisons).

Derivation of the above O(N):
1. Starting the comparison from the leaf nodes(level l=log(N)), if total size is N, number of leaf nodes will be upperbound-of(N/2).
 - First half of N/2, i.e, N/4 nodes are compared against second half of N/2, i.e. N/4 nodes <-- N/4 comparisons.
2. Similarly for level l = log(N) - 1, it is N/8 comparisons and so on till it reaches level 1, where it is 1 comparison.
3. The outer loop maximum runs for log(N) times. Total comparisons = N/4 + N/8 + N/16 + ... + 1 = N/2 comparisons = O(N).

Case 2: Sparse Tree
	In this case, the implementation doesnot perform well as the size of Array(storing the Tree Nodes) becomes very large compared to the 
	size of the Tree.
	
	Worst case: Let l be the level of the sparse tree where each level just contains 2 nodes, i.e. LeftSubTree of Root contains l nodes and 
	RightSubTree of Root contains l nodes. Totalling to 2*l + 1(root node) = 2l+1.
	
	In the above case, the size of the Array storing the above sparse tree would be 2^0 + 2^1 + ... + 2^l = 2^(l+1) - 1 .
	So in this case, the amortized runtime of algorithm is O(2^N) where "N" is the size of the sparse binary Tree in the worst case.
	
Conclusion:
	Since we did not discuss about other characteristics of the binary tree, options are:
		1. Balance the tree as the size increases beyond a certain limit and use array representation(above) for treeNodes.
			If there is a concern for using large sized arrays, try many variants of ordered lists where insertion of each node is O(1).
			Could think of skip-lists.
		2. Using queues, iterative approach.
		3. Using recursion.