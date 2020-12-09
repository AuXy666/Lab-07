#include<iostream>
using namespace std;

bool searchChecker = false;
class node
{
public:
	int val;
	node* left;
	node* right;
};

class binarySearch_Tree
{
public:
	node* root;
	int iCounter;
	int leafCount;
	int internalCount;
	binarySearch_Tree()
	{
		root = NULL;
		iCounter = 0;
		leafCount = 0;
		internalCount = 0;
	}
	node* newNode(int item)
	{
		node* temp = new node;
		temp->val = item;
		temp->left = temp->right = NULL;
		return temp;
	}
	void rootInsert(int temp)
	{
		if (root == NULL)
		{
			root = newNode(temp);
		}
	}
	node* insert(node* temp1, int temp2)
	{

		if (temp1 == NULL)
		{
			temp1 = newNode(temp2);
			return temp1;
		}

		if (temp2 < temp1->val)
		{
			temp1->left = insert(temp1->left, temp2);
		}
		else if (temp2 > temp1->val)
		{
			temp1->right = insert(temp1->right, temp2);
		}

		return temp1;
	}
	node* search(node* temp, int key)
	{

		if (temp == NULL)
		{
			return temp;
		}
		if (temp->val == key)
		{
			searchChecker = true;
			return temp;
		}


		if (temp->val < key)
		{
			return search(temp->right, key);
		}

		return search(temp->left, key);
	}
	int height(node* temp)
	{
		int leftSide;
		int rightSide;
		if (temp == NULL)
			return -1;
		else
		{
			
			leftSide = height(temp->left);
			rightSide = height(temp->right);

			if (leftSide > rightSide)
			{
				leftSide++;
				return leftSide;
			}
			else
			{
				rightSide++;
				return rightSide;
			}
		}
	}

	int getLevel(node* temp, int key)
	{
		return getLevelUtil(temp, key, 1);
	}

	int getLevelUtil(node* temp,int key, int temp2)
	{
		if (temp == NULL)
			return 0;

		if (temp->val == key)
			return temp2;

		int downlevel = getLevelUtil(temp->left,
			key, temp2 + 1);
		if (downlevel != 0)
			return downlevel;

		downlevel = getLevelUtil(temp->right,
			key, temp2 + 1);
		return downlevel;
	}
	int degree(node* temp, int key)
	{
		node* keyNode;
		keyNode=search(temp, key);
		if(keyNode==NULL)
		{
			return -1;
		}
		else if (keyNode->left != NULL && keyNode->right == NULL)
		{
			return 1;
		}
		else if (keyNode->left == NULL && keyNode->right != NULL)
		{
			return 1;
		}
		else if (keyNode->left != NULL && keyNode->right != NULL)
		{
			return 2;
		}
		else if (keyNode->left == NULL && keyNode->right == NULL)
		{
			return 0;
		}
	}
	int totalNodes(node* temp)
	{
		if (temp == NULL)
		{
			return 0;
		}

		iCounter++;

		totalNodes(temp->left);

		totalNodes(temp->right);
		return iCounter;
	}
	bool isLeaf(node* temp, int key)
	{
		node* Leaf = search(temp, key);
		if (Leaf == NULL)
		{
			return false;
		}
		else if (Leaf->left == NULL && Leaf->right == NULL)
		{
			return true;
		}
	}
	bool isNonLeaf(node* temp, int key)
	{
		node* NonLeaf = search(temp, key);
		if (NonLeaf == NULL)
		{
			return false;
		}
		else if (NonLeaf->left == NULL && NonLeaf->right == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool isParent(node* temp, int key1,int key2)
	{
		node* key1Node = search(temp, key1);
		node* key2Node = search(temp, key2);
		if (temp == NULL || key1Node == NULL || key2Node == NULL)
		{
			return false;
		}
		else if (key1Node->left == key2Node)
		{
			return true;
		}
		else if (key1Node->right == key2Node)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isChild(node* temp, int key1,int key2)
	{
		node* key1Node = search(temp, key1);
		node* key2Node = search(temp, key2);
		if (temp == NULL||key1Node==NULL||key2Node==NULL)
		{
			return false;
		}
		else if (key1Node->left == key2Node)
		{
			return true;
		}
		else if (key1Node->right == key2Node)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
	bool IsSibling(node* temp, int key1,int key2)
	{
		if (temp==NULL)
		{
			return false;
		}
		if (temp->left!=NULL && temp->right!=NULL)
		{
			if (temp->left->val == key1 && temp->right->val == key2)
			{
				return true;
			}
			else if (temp->right->val == key2 && temp->left->val == key1)
			{
				return true;
			}
		}

		if (temp->left!=NULL)
			IsSibling(temp->left, key1,key2);

		if (temp->right!=NULL)
			IsSibling(temp->right, key1,key2);
	}
	bool isDescendant(node* temp, int key1,int key2)
	{
		node* key1Node = search(temp, key1);
		node* key2Node = search(temp, key2);
		if (temp == NULL || key1Node == NULL || key2Node == NULL)
		{
			return false;
		}
		if (key2 > key1)
		{
			searchChecker = false;
			key1Node = search(key1Node->right, key2);
			if (searchChecker == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (key2 < key1)
		{
			searchChecker = false;
			key1Node = search(key1Node->left, key2);
			if (searchChecker == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}
	bool isSuccessor(node* temp, int key1, int key2)
	{
		node* key1Node = search(temp, key1);
		node* key2Node = search(temp, key2);
		if (temp == NULL || key1Node == NULL || key2Node == NULL)
		{
			return false;
		}
		if (key2 > key1)
		{
			searchChecker = false;
			key1Node = search(key1Node->right, key2);
			if (searchChecker == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (key2 < key1)
		{
			searchChecker = false;
			key1Node = search(key1Node->left, key2);
			if (searchChecker == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}
	int leaf_counter(node* temp)
	{
		if (temp == NULL)
		{
			return 0;
		}
		else if(temp->left==NULL && temp->right==NULL)
		{ 
			return 1;	
		}
		else
		{
			return leaf_counter(temp->left) + leaf_counter(temp->right);
		}
	}
	int internal_counter(node* temp)
	{
		
		if (temp == NULL)
		{
			return 0;
		}
		else if (temp->left == NULL && temp->right == NULL)
		{
			return 0;
		}
		return 1 + internal_counter(temp->left) + internal_counter(temp->right);

	}
	void inorder(node* root)
	{
		if (root == NULL)
		{
			return;
		}

		inorder(root->left);

		cout << root->val << " ";

		inorder(root->right);
	}
	void preorder(node* root)
	{
		if (root == NULL)
			return;

		cout << root->val << " ";

		preorder(root->left);

		preorder(root->right);
	}
	void postorder(node* root)
	{
		if (root == NULL)
			return;

		postorder(root->left);

		postorder(root->right);

		cout << root->val << " ";
	}
	


};


int main()
{
	binarySearch_Tree b1;
	bool loopCounter = true;
	int loopInput;
	int input;
	while (loopCounter)
	{
		cout << "Press 1 to enter Root of Binary Search Tree" << endl;
		cout << "Press 2 to insert into Binary Search tree" << endl;
		cout << "Press 3 to find max height of Binary Search Tree" << endl;
		cout << "Press 4 to find level of a node in Binary Search Tree" << endl;
		cout << "Press 5 to find degree of a node in Binary Search Tree" << endl;
		cout << "Press 6 to find total number of nodes in Binary Search Tree" << endl;
		cout << "Press 7 to find if the node is leaf in Binary Search Tree" << endl;
		cout << "Press 8 to find if the node is non leaf in Binary Search Tree" << endl;
		cout << "Press 9 to find if the node is parent in Binary Search Tree" << endl;
		cout << "Press 10 to find if the node is child in Binary Search Tree" << endl;
		cout << "Press 11 to find if the node is Descendent in Binary Search Tree" << endl;
		cout << "Press 12 to find if the node is Successor in Binary Search Tree" << endl;
		cout << "Press 13 to find if the node is Sibling in Binary Search Tree" << endl;
		cout << "Press 14 to find number of leafs in Binary Search Tree" << endl;
		cout << "Press 15 to find number of internal nodes in Binary Search Tree" << endl;
		cout << "Press 16 to inorder traversal" << endl;
		cout << "Press 17 to Preorder traversal" << endl;
		cout << "Press 18 to Postorder traversal" << endl;
		cout << "Press 19 to end" << endl;
		cin >> loopInput;
		system("cls");
		if (loopInput == 1)
		{
			cout << "Enter Value = ";
			cin >> input;
			b1.rootInsert(input);
			cout << endl;
		}
		else if (loopInput == 2)
		{
			cout << "Enter Value = ";
			cin >> input;
			b1.insert(b1.root, input);
			cout << endl;

		}
		else if (loopInput == 3)
		{
			
			cout << "Following is the height of Binary Search Tree " << endl;
			cout << b1.height(b1.root) << endl;
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 4)
		{
			int value;
			cout << "Enter value of Key = ";
			cin >> value;
			cout << b1.getLevel(b1.root, value) << endl;
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 5)
		{
			int value;
			int d;
			cout << "Enter value of Key = ";
			cin >> value;
			d=b1.degree(b1.root, value);
			if (d == -1)
			{
				cout << "Key value not found" << endl;
			}
			cout << "Degree of this node is = " << d << endl;
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 6)
		{
			cout << "Total Number of nodes in this binary search tree are = " << endl;
			cout << b1.totalNodes(b1.root) << endl;
			cout << endl;
		}
		else if (loopInput == 7)
		{
			int value;
			cout << "Enter key value = ";
			cin >> value;
			if (b1.isLeaf(b1.root, value) == true)
			{
				cout << "It is leaf node" << endl;
				cout << endl;
			}
			else
			{
				cout << "It is not leaf node" << endl;
				cout << endl;
			}
			system("pause");
			system("cls");
		}

		else if (loopInput == 8)
		{
			int value;
			cout << "Enter key value = ";
			cin >> value;
			if (b1.isNonLeaf(b1.root, value) == true)
			{
				cout << "It is Non-leaf node" << endl;
				cout << endl;
			}
			else
			{
				cout << "It is not Non-leaf node" << endl;
				cout << endl;
			}
			system("pause");
			system("cls");
		}
		else if (loopInput == 9)
		{
			int value1, value2;
			cout << "Enter key 1 value = ";
			cin >> value1;
			cout << "Enter key 2 value = ";
			cin >> value2;
			if (b1.isParent(b1.root, value1, value2) == true)
			{
				cout << "Key 1 is parent of Key 2" << endl;
				cout << endl;
			}
			else
			{
				cout << "Key 1 is not a parent of Key 2" << endl;
			}
			system("pause");
			system("cls");
		}
		else if (loopInput == 10)
		{
			int value1,value2;
			cout << "Enter key 1 value = ";
			cin >> value1;
			cout << "Enter key 2 value = ";
			cin >> value2;
			if (b1.isChild(b1.root, value1,value2) == true)
			{  
				cout << "Key 2 is child of Key 1" << endl;
				cout << endl;
			}
			else
			{
				cout << "Key 2 is not a child of Key 1" << endl;
			}
			system("pause");
			system("cls");
		}
		else if (loopInput == 11)
		{
			int value1, value2;
			cout << "Enter Key 1 = ";
			cin >> value1;
			cout << "Enter Key 2 = ";
			cin >> value2;
			if (b1.isDescendant(b1.root, value1, value2) == true)
			{
				cout << "Key 1 is descendant of Key 2 " << endl;
				cout << endl;
			}
			else
			{
				cout << "Key 1 is not descendant of Kye 2" << endl;
			}
			system("pause");
			system("cls");
		}
		else if (loopInput == 12)
		{
			int value1, value2;
			cout << "Enter Key 1 = ";
			cin >> value1;
			cout << "Enter Key 2 = ";
			cin >> value2;
			if (b1.isSuccessor(b1.root, value1, value2) == true)
			{
				cout << "Key 2 is sucessor of Key 1 " << endl;
				cout << endl;
			}
			else
			{
				cout << "Key 2 is not sucessor of Kye 1" << endl;
			}
			system("pause");
			system("cls");
		}
		else if (loopInput == 13)
		{
			int value1, value2;
			cout << "Enter Key 1 = ";
			cin >> value1;
			cout << "Enter Key 2 = ";
			cin >> value2;
			if (b1.IsSibling(b1.root, value1, value2) == true)
			{
				cout << "These nodes are siblings" << endl;
				cout << endl;
			}
			else
			{
				cout << "These node are not siblings" << endl;
			}
			system("pause");
			system("cls");
		}
		else if (loopInput == 14)
		{
			cout << "Number of leaf nodes in this tree are = ";
			cout << b1.leaf_counter(b1.root) << endl;
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 15)
		{
			cout << "Number of internal nodes in this tree are = ";
			cout << b1.internal_counter(b1.root) << endl;
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 16)
		{
			cout << "Inorder = " << endl;
			b1.inorder(b1.root);
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 17)
		{
			cout << "Preorder = " << endl;
			b1.preorder(b1.root);
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 18)
		{
			cout << "Postorder = " << endl;
			b1.postorder(b1.root);
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (loopInput == 19)
		{
			loopCounter = false;
		}
	}

}
