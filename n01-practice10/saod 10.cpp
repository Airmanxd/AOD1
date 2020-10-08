#include <iostream>
using namespace std;

struct node
{
	int key;
	int height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};
int height(node* p)
{
	return p ? p->height : 0;
}	

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	int left_height = height(p->left);
	int right_height = height(p->right);
	p->height = (left_height > right_height ? left_height : right_height) + 1;
}

node* rotateright(node* p) 
{
	node* temp = p->left;
	p->left = temp->right;
	temp->right = p;
	fixheight(p);
	fixheight(temp);
	return temp;
}

node* rotateleft(node* p)
{
	node* temp = p->right;
	p->right = temp->left;
	temp->left = p;
	fixheight(p);
	fixheight(temp);
	return temp;
}

node* balance(node* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}

node* insert(node* p, int k)
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p){
	return p->left ? findmin(p->left) : p;
}
node* removemin(node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
node* remove(node* p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void print_tree(node* root, int k)
{
	string indent = "     ";
	for (int i = 0; i < k; i++)
	{
		indent += indent;
	}
	if (root->right)
		print_tree(root->right, k + 1);
	cout << indent << root->key << endl;
	if (root->left)
		print_tree(root->left, k + 1);
}

int main()
{
	int a;
	cin >> a;
	node* root = new node(a);
	cin >> a;
	while (a != 727)
	{
		root = insert(root, a);
		cin >> a;
	}
	print_tree(root, 0);
	return 0;
}