#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
	return;
}


void BinaryTree::insert(int value)
{
	TreeNode* newMode = new TreeNode(value);

	//If the tree is empty, set the root to be a new node with the given value.
	if (isEmpty())
	{
		m_root = newMode;
	}
	
			//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
		TreeNode* current = m_root;
		//Create a TreeNode pointer that will act as an iterator pointing to the parent
		//of the current node and set it to the root.
		TreeNode* parent = current;
		//Loop until the the current node iterator reaches a nullptr.
		while (current != nullptr)
		{
			//Check if the value we want to add to the tree is less than the value at the current node.
			if (value < current->getData())
			{
				//Set the parent node to be the current node before the current node moves positions.
				parent = current;

				//Change the current node to be the child to its left and continue.
				current = current->getLeft();
			}
			//Check if the value we want to add to the tree is greater than the value at the current node.
			else if (value > current->getData())
			{
				//Set the parent node to be the current node before the current node moves positions.
				parent = current;

				//Change the current node to be the child to its right and continue.
				current = current->getRight();
			}
			//If the value is the same as a value already in the list return 
			else if (value == current->getData())
			{
				return;
			}
		}
		//If the value we want to add is less than the value of the parent node, insert the value to the left.
		if (value < parent->getData())
		{
			parent->setLeft(newMode);
		}
		//Otherwise, insert the value to the right.
		else if(value > parent->getData())
		{
			parent->setRight(newMode);
		}

}

void BinaryTree::remove(int value)
{
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	//and another to hold a reference to its parent.
	TreeNode* current = nullptr;
	TreeNode* parent = nullptr;

	TreeNode* minNode = nullptr;

	//Try to find the node that matches the value given and its parent in the tree.
	findNode(value, current, parent);

	//If the node cannot be found return.
	if (current == nullptr)
	{
		return;
	}

	//Check to see if the node has a right
	if (current->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		TreeNode* minNode = current;

		//Set the first iterator to point to the right child of the node we want to remove.
		TreeNode* minNode2 = minNode;
		minNode = current->getRight();

		//Loop while the first iterator has a value to its left
		while (minNode->hasLeft())
		{
			//Set the second iterator to be the value of the first iterator.
			minNode2 = minNode;
			//Set the first iterator to be the value to the left of it
			minNode = minNode->getLeft();
			//End loop
		}
		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		current->setData(minNode->getData());

		//Check if the second iterator has a left child.
		if (minNode2->hasLeft())
		{
			//Check if the left child stores the same data as the node we wanted to remove.
			if (minNode2->getLeft() == minNode)
			{
				//Set the second iterators left child to be the first iterators right child.
				minNode2->setLeft(minNode->getRight());
			}

		}
		//Check if the second iterator has a right child.
		if (minNode2->hasRight())
		{
			//Check if the right child contains the same data as the node we want to remove.
			if (minNode2->getRight() == minNode)
			{
				//Set the right child of the second iterator to be the right child of the first iterator.
				minNode2->setRight(minNode->getRight());
			}
		}
		//Delete the first iterator
		minNode = nullptr;

	}
	//Otherwise, if the node doesn't have a right child
	else
	{
		//check if the parent of the node to remove has a left child.
		if (parent->hasLeft())
		{
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (current == parent->getLeft())
			{
				//Set the left child of the parent node to be the left child of the node to remove.
				parent->setLeft(current->getLeft());
			}
		}

		//Check if the parent of the node to remove has a right child.
		if (parent->hasRight())
		{
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (current == parent->getRight())
			{
				//Set the right child of the parent node to be the left child of the node to remove.
				parent->setRight(current->getLeft());
			}
		}

		//Check if the node we want to remove is the root.
		if (current == m_root)
		{
			//Set the root to be its left child.
			m_root = current->getLeft();
		}
		//Delete the pointer that points to the node to remove.
		delete current;
	}

}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* current = m_root;
	TreeNode* parentNode = current;

	//Loop through the tree while the iterator isn't nullptr.
	while (current != nullptr)
	{
		//Check if the node has the data we want
		if (value == current->getData())
		{
			//Return the iterator
			return current;
;		}
		//If the node doesn't have the data we want, check to see if it's higher in value.
		else if (value > current->getData())
		{
			//Set the iterator to be its current right child.
			current = current->getRight();
		}
		//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (value < current->getData())
		{
			//Set the iterator to be its current left child.
			current = current->getLeft();
		}
		//end loop
	}
	//Return nullptr
	return nullptr;

}

void BinaryTree::draw(TreeNode* selected)
{
	draw(m_root, 340, 40, 140, selected);
}

bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	//Create two iterators: one that will point to the current node to compare the search value to,
	TreeNode* current = m_root;

	//and the other to hold a reference to the parent.
	TreeNode* parentNode = current;


	//Loop while the current node iterator isn't nullptr/
	while (current != nullptr)
	{
		//Check if the search value is the same as the current nodes data.
		if (searchValue == current->getData())
		{
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			nodeFound = current;
			nodeParent = parentNode;
			//Return true.
			return true;
		}
		//Check if the search value is greater than the value at the current node.
		else if (searchValue > current->getData())
		{
			//Set the parent node to be the current node.
			parentNode = current;
			//Set the current node to be the child to the right of the current node.
			current = current->getRight();
		}
		//Check if the search value is less than the value at the current node.
		else if (searchValue < current->getData())
		{
			//Set the parent node to be the current node.
			parentNode = current;
			//Set the current node to be its left child.
			current = current->getLeft();
		}
		//end loop
	}
	//Return false.
	return false;

}

void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	//Cuts horizontal spacing in half
	horizontalSpacing / -2;

	//Check if the current node exists
	if (currentNode)
	{
		//Checks for a left node
		if (currentNode->hasLeft())
		{
			//Draws left
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Checks for a right node
		if (currentNode->hasRight())
		{
			//Draw right
			DrawLine(x, y, x + horizontalSpacing, y + 90, RED);
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draw current
		currentNode->draw(x, y, (selected == currentNode));
	}


}