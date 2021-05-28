#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
using namespace std;

class node {	// node class definition
public:
	string season;	
	string name;	
	string teamname;		
	int rebound;	
	int assist;
	int point;
	int color;  //0 means black 1 means red
	int rotation;	// 0 means left 1 means right
	node* left;
	node* right;
	node* parent;
	node* sibling;
	node(string season, string name, string teamname, int rebound, int assist, int point);
};

node::node(string season,string name,string teamname, int rebound,int assist,int point) {	// constructor
	this->season = season;
	this->name = name;
	this->teamname = teamname;
	this->rebound = rebound;
	this->assist = assist;
	this->point = point;
	this->color = 1;	// all nodes are initialized as red
}

class rbt {	//rbt class definition
public:
	node* root_ptr;	
	int highest_rebound, highest_assist, highest_point;	
	string highest_rebound_name, highest_assist_name, highest_point_name;
	rbt();
	void recolor(node* ptr, node* trav);	
	void leftrotate(node* ptr, node* trav);
	void rightrotate(node* ptr, node* trav);
	void insert(node* ptr);
	void print(node * ptr,int count);
};

rbt::rbt() {	// tree constructor
	root_ptr = NULL;		//root == null
	highest_rebound = -1;
	highest_assist = -1;
	highest_point = -1;
}

void rbt::insert(node* ptr) {
	if (root_ptr == NULL) {	//if no element then added element is root
		ptr->color = 0;	//root color is black
		ptr->rotation = -1;	// root rotation is -1
		root_ptr = ptr;	//rootptr points ptr
		root_ptr->parent = NULL;	//root has no parent
		root_ptr->sibling = NULL;	// root has no sibling
	}
	else {
		node* trav = root_ptr;	// trav = root
		while (true) {
			if (ptr->name.compare(trav->name) < 0) { // compare with trav if smaller go left			
				if(trav->left != NULL) {	// if trav->left is not null then ptr needs be compared with trav left
					trav = trav->left;
				}
				else {
					trav->left = ptr;	// if trav->left is NULL then trav->left is ptr
					ptr->parent = trav;	//ptr->parent is trav
					ptr->rotation = 0;	// ptr rotation is 0 since it is left child
					ptr->sibling = trav->right;	// ptr sibling can be null
					if (trav->right) {	// if trav has right node then its sibling is new added node
						trav->right->sibling = ptr;
					}
					if (trav->color == 0) {	//if ptr->parent is black then there is no problem
						break;
					}
					else {
						recolor(ptr, trav);	// if parent is red then it needs to recolor or rotations 
						break;
					}
				}
			}
			else if (ptr->name.compare(trav->name) > 0) { // compare with trav if bigger go right
				if (trav->right != NULL) {// if trav->right is not null then ptr needs be compared with trav right
					trav = trav->right;
				}
				else {
					trav->right = ptr;	// if trav->right is NULL then trav->right is ptr
					ptr->parent = trav;	//ptr->parent is trav
					ptr->rotation = 1;	// ptr rotation is 1 since it is right child
					ptr->sibling = trav->left;	// ptr sibling can be null
					if (trav->left) {	// if trav has left node then its sibling is new added node
						trav->left->sibling = ptr;
					}
					if (trav->color == 0) {	//if ptr->parent is black then there is no problem
						break;
					}
					else {
						recolor(ptr, trav);	// if parent is red then it needs to recolor or rotations
						break;
					}
				}
			}
			else if (ptr->name.compare(trav->name) == 0) { // if 2 names are equal then update existing node
				trav->rebound += ptr->rebound;	//update rebound
				trav->assist += ptr->assist;	//update assist
				trav->point += ptr->point;		//update point
				if (highest_rebound < trav->rebound) {	// compare with highest rebound if greater change highest rebound
					highest_rebound = trav->rebound;
					highest_rebound_name = trav->name;
				}
				if (highest_assist < trav->assist) {	// compare with highest assist if greater change highest assist
					highest_assist = trav->assist;
					highest_assist_name = trav->name;
				}
				if (highest_point < trav->point) {	// compare with highest point if greater change highest point
					highest_point = trav->point;
					highest_point_name = trav->name;
				}
				break;	//Since there is no addition tree properties can not be violated

			}
		}
	}
}

void rbt::recolor(node* ptr, node* trav) {
	if (ptr->color != trav->color) {	// if colors are not equal return
	}
	else if (trav->color == 1) {	 
		if (!(trav->sibling) || trav->sibling->color == 0) {	//parents sibling is not avaliable or black 
			if (trav->rotation == 0) {	// if parent is left child of the grandparent
				if (ptr->rotation == 1) {	// if ptr is right child of the trav	LR case transform to LL case
					leftrotate(ptr, trav);	//rotate left
					node* temp = ptr;	// change trav and ptr 
					ptr = trav;
					trav = temp;
				}
				trav->color = 0;	// make trav black
				trav->parent->color = 1;	//make trav->parent red
				trav->parent->left = trav->right;	// grandparents left pointer will point to right pointer of trav
				if (trav->parent->right != NULL) {	//if there are elements in trav->parent->right
					trav->parent->right->sibling = ptr->sibling;	// then its sibling will change	(ptr->sibling is trav->parent->left)
				}
				trav->sibling = trav->parent->sibling;	// travs sibling will be its parents sibling
				if (trav->parent->sibling != NULL) {	// if sibling is not null
					trav->parent->sibling->sibling = trav;	//then siblings sibling will be trav
				}
				ptr->sibling =  trav->parent;	//ptr->sibling will be trav->parent
				trav->parent->sibling = ptr;	//trav->parent->sibling will be ptr
				if (trav->parent->left != NULL) {	//if trav->parent->left(it was trav->right in beginning) is not null
					trav->parent->left->rotation = 0;	//its rotation is changed now it is left child
					trav->parent->left->sibling = trav->parent->right;	// its sibling will change
					trav->parent->left->parent = trav->parent;	// its parent is trac->parent
				}
				trav->rotation = trav->parent->rotation;	//trav rotation will be its parent rotation
				trav->parent->rotation = 1;	//trav parent is right child of trav in rotated tree
				trav->right = trav->parent;	// trav->parent is trav->right
				trav->parent = trav->parent->parent;	// trav->parent is trav->parent->parent
				trav->right->parent = trav;	//trav->right is trav->parent in the beginning now it is right child of trav
				if (trav->rotation == -1) {	// if trav becomes root node
					root_ptr = trav;	// root_ptr points trav
				}
				else if (trav->rotation == 0) {
					trav->parent->left = trav;	// if it is left child trav->parent->left is trav
				}
				else if (trav->rotation == 1) {
					trav->parent->right = trav; // if it is right child trav->parent->right is trav
				}
			}
			else if (trav->rotation == 1) { // if parent is right child of the grandparent
				if (ptr->rotation == 0) {	// if ptr is left child of the trav	RL case transform to RR case
					rightrotate(ptr, trav);	//rotate left
					node* temp = ptr;	// change trav and ptr
					ptr = trav;
					trav = temp;
				}
				trav->color = 0;	// make trav black
				trav->parent->color = 1;	//make trav->parent red
				trav->parent->right = trav->left;	// grandparents right pointer will point to left pointer of trav
				if (trav->parent->left) {	//if there are elements in trav->parent->left
					trav->parent->left->sibling = ptr->sibling;	//then siblings sibling will be trav
				}
				trav->sibling = trav->parent->sibling;	// travs sibling will be its parents sibling
				if (trav->parent->sibling != NULL) {	// if trav->parent->sibling is no null
					trav->parent->sibling->sibling = trav;	// then its sibling will change
				}
				ptr->sibling = trav->parent;	//prt->sibling will change
				trav->parent->sibling = ptr;	// trav->parent sibling will be ptr
				if (trav->parent->right) {	//if trav->parent->right(it was trav->left in beginning) is not null
					trav->parent->right->rotation = 1;	//its rotation is changed now it is right child
					trav->parent->right->sibling = trav->parent->left;	// its sibling will change
					trav->parent->right->parent = trav->parent;	// its parent will change
				}
				trav->rotation = trav->parent->rotation;	// trav->rotation will be its parents rotation
				trav->parent->rotation = 0;	// trav->parent rotation will be 0 since it is left child now
				trav->left = trav->parent;	// trav->left is trav->parent
				trav->parent = trav->parent->parent;	// trav->parent is trav->parent->parent
				trav->left->parent = trav;	// trav->left->parent is trav
				if (trav->rotation == -1) {	//if trav is root
					root_ptr = trav;	// root ptr points to trav
				}
				else if (trav->rotation == 0) {
					trav->parent->left = trav;	// if trav is left child its parents left is trav
				}
				else if (trav->rotation == 1) {
					trav->parent->right = trav;	// if trav is right child its parents right is trav
				}
			}
		}
		else if (trav->sibling->color == 1) {	// parents sibling is avaliable and it is red then only coloring operations
			trav->sibling->color = 0;	// uncle was red not it is black
			trav->color = 0;	// parent was red now it is black
			if (trav->parent != root_ptr) {	// if grand parent is not root
				trav->parent->color = 1;	// make grandparent red
				recolor(trav->parent, trav->parent->parent);	// call recursively because grandparents father can be red
			}													// check that probability
		}
	}
}
void rbt::leftrotate(node* ptr, node* trav) {
	trav->right = ptr->left;	// trav->right is ptr->left
	if (trav->right) {	// if trav right is not null
		trav->right->parent = trav;	// its parent is trav
		trav->right->rotation = 1;	// its rotation is 1 right child
		trav->right->sibling = trav->left;	//its sibling is trav->left
	}
	if (trav->left) {	// if trav->left is not null
		trav->left->sibling = trav->right;	// its sibling is trav->right
	}
	ptr->left = trav;	// ptr->left is trav
	ptr->parent = trav->parent;	// ptr->parent is trav->parent
	ptr->parent->left = ptr;	// ptr->parent->left is ptr 
	trav->parent = ptr;	//trav->parent is ptr
	ptr->rotation = trav->rotation;	// ptr->rotation is trav->rotation
	ptr->sibling = trav->sibling;	// ptr->sibling is trav->sibling
	if (ptr->sibling) {	//if ptr->sibling is not null
		ptr->sibling->sibling = ptr;	// then its sibling is ptr
	}
	trav->sibling = ptr->right;	// trav->sibling is ptr->right
	if (ptr->right) {	// if ptr->right is not null
		ptr->right->sibling = trav;	// then its sibling is trav
	}
}

void rbt::rightrotate(node * ptr, node * trav) {
	trav->left = ptr->right;	// trav->left is ptr->right
	if (trav->left) {	// if trav ->left is not null
		trav->left->rotation = 0;	// its rotation is 0 left child
		trav->left->sibling = trav->right;	//its sibling is trav->right
		trav->left->parent = trav;	// its parent is trav
	}
	if (trav->right) {	// if trav->right is not null
		trav->right->sibling = trav->left;	// its sibling is trav->left
	}
	ptr->right = trav;	// ptr->right is trav
	ptr->parent = trav->parent;	// ptr->parent is trav->parent
	trav->parent = ptr;		// trav->parent is ptr 
	ptr->parent->right = ptr;	//ptr->parent->left is ptr
	if (trav->sibling != NULL) {	//if trav->sibling is not null
		trav->sibling->sibling = ptr;		//then its sibling will  be ptr
	}
	ptr->sibling = trav->sibling;	//ptr->sibling will be trav->sibling
	trav->sibling = ptr->left;	//trav->sibling will be ptr->left
	if (ptr->left != NULL) {	// trav->sibling is not null
		ptr->left->sibling = trav;	//its sibling will be trav
	}	
	ptr->rotation = 1;	//ptr->rotation will be 1 right child now
}

void rbt::print(node* trav,int count) {	// preorder traversal print count holds depth of the node
	for (int i = 0; i < count; i++) {
		cout << "-";
	}
	if (trav->color == 1) {
		cout << "(RED) " << trav->name << "\n";
	}
	else {
		cout << "(BLACK) " << trav->name << "\n";
	}
	if (trav->left != NULL) {
		print(trav->left, count + 1);
	}
	if (trav->right != NULL) {
		print(trav->right, count + 1);
	}
}

int main() {

	ifstream File;
	File.open("euroleague.csv");

	if (!File) {
		cout << "File can not be opened";
	}
	rbt *tree = new rbt(); //tree is created	
	int once = 0;	//used for printing tree only once
	string name, season, teamname, header, tempstring, season_compare,previous_name;
	int rebound, assist, point;
	getline(File, header);	// for reading header
	while(true) {
		stringstream ss(header);
		getline(File, season, ',');	// read season
		if (season != season_compare && tree->highest_rebound != -1) {	// if season is changed and it is not on the first step of loop
			cout << "End of the " << season_compare << " Season" << "\n";
			cout << "Max Points: " << tree->highest_point << " - Player Name: " << tree->highest_point_name << "\n";
			cout << "Max Assists: " << tree->highest_assist << " - Player Name: " << tree->highest_assist_name << "\n";
			cout << "Max Rebs: " << tree->highest_rebound << " - Player Name: " << tree->highest_rebound_name << "\n";
			season_compare = season;
			if (once == 0) {	//print the tree for season 1
				tree->print(tree->root_ptr, 0);
				once = 1;
			}
		}
		getline(File, name, ',');	//read name
		if (previous_name == name) {	// if previous name and new name is same then file is finished
			break;
		}
		getline(File, teamname, ',');	//read teamname
		getline(File, tempstring, ',');	//read rebound
		rebound = stoi(tempstring);	//convert to integer
		getline(File, tempstring, ',');	//read assist
		assist = stoi(tempstring);	//convert to integer
		getline(File, tempstring, '\n');	//read point
		point = stoi(tempstring);	//convert to integer
		if (tree->highest_rebound == -1) {	// give first values on the first player
			tree->highest_rebound = rebound;
			tree->highest_rebound_name = name;
			tree->highest_point = point;
			tree->highest_point_name = name;
			tree->highest_assist = assist;
			tree->highest_assist_name = name;
			season_compare = season;
		}
		if (tree->highest_rebound < rebound) {	//this is useful on season 1 too
			tree->highest_rebound = rebound;
			tree->highest_rebound_name = name;
		}
		if (tree->highest_assist < assist) {
			tree->highest_assist = assist;
			tree->highest_assist_name = name;
		}
		if (tree->highest_point < point) {
			tree->highest_point = point;
			tree->highest_point_name = name;
		}
		previous_name = name;	// hold the previous name for file end situation
		node *addnode = new node(season, name, teamname, rebound, assist, point); // create node
		tree->insert(addnode);	// insert node to tree
	}
}