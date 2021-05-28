#include <iostream>
#include<string>
using namespace std;

class node {	// node class definition
public:
	int* x;
	int* y;
	char* z;
	int elementcount;
	node* parent;
	node** pointerarr;
	node(int max_keys, int max_child);
	bool isleaf;
};

node::node(int max_keys, int max_child) {
	x = new int[max_keys];
	y = new int[max_keys];
	z = new char[max_keys];
	parent = NULL;
	elementcount = 0;
	isleaf = true;
	pointerarr = new node * [max_child];
	for (int c = 0; c < max_child + 1; c++) {
		pointerarr[c] = NULL;
	}
}
class btree {	// tree class definition
public:
	node* root_ptr;
	int min_keys, min_child, max_keys, max_child;
	char sort_by;
	btree(int a, int b, int c, int d, char e);
	void insert(int x1, int x2, char c1);
	void inserttoleafz(node* ptr, int x1, int x2, char c1);
	void inserttoleafx(node* ptr, int x1, int x2, char c1);
	void inserttoleafy(node* ptr, int x1, int x2, char c1);
	void inserttononleafz(node* ptr, node* pointer, node* pointtr, int x1, int x2, char c1);
	void inserttononleafx(node* ptr, node* pointer, node* pointtr, int x1, int x2, char c1);
	void inserttononleafy(node* ptr, node* pointer, node* pointtr, int x1, int x2, char c1);
	void splitnode(node* ptr);
	void printtree(node* ptr);
	void deletechar(char del);
	void deletex(int del);
	void deletey(int del);
	void deleteleafz(node* ptr, int left_el_ct, int right_el_ct, char del);
	void deleteleafx(node* ptr, int left_el_ct, int right_el_ct, int del);
	void deleteleafy(node* ptr, int left_el_ct, int right_el_ct, int del);
	void deleteinternalnodex(node* ptr, int del);
	void deleteinternalnodey(node* ptr, int del);
	void deleteinternalnodez(node* ptr, char del);
};

btree::btree(int min_keys, int min_child, int max_keys, int max_child, char sort_by) {
	this->root_ptr = NULL;
	this->min_keys = min_keys;
	this->min_child = min_child;
	this->max_keys = max_keys;
	this->max_child = max_child;
	this->sort_by = sort_by;
}

void btree::insert(int x1, int x2, char c1) {
	if (root_ptr == NULL) {
		node* trav = new node(max_keys, max_child);
		root_ptr = trav;
		trav->x[0] = x1;
		trav->y[0] = x2;
		trav->z[0] = c1;
		trav->elementcount++;
	}
	else {
		if (sort_by == 'x') {
			node* trav = root_ptr;
			int i = 0;
			while (true)
			{
				if (trav->isleaf) {
					if (trav->elementcount == max_keys) {
						splitnode(trav);
						trav = root_ptr;
						i = 0;
					}
					else {
						inserttoleafx(trav, x1, x2, c1);
						i = 0;
						break;
					}
				}
				else {
					if (x1 > trav->x[i]) {
						i++;
						if (trav->elementcount == i) {
							trav = trav->pointerarr[i];
							i = 0;
						}
					}
					else {
						trav = trav->pointerarr[i];
						i = 0;
					}
				}
			}
		}
		else if (sort_by == 'y') {
			node* trav = root_ptr;
			int i = 0;
			while (true)
			{
				if (trav->isleaf) {
					if (trav->elementcount == max_keys) {
						splitnode(trav);
						trav = root_ptr;
						i = 0;
					}
					else {
						inserttoleafy(trav, x1, x2, c1);
						i = 0;
						break;
					}
				}
				else {
					if (x2 > trav->y[i]) {
						i++;
						if (trav->elementcount == i) {
							trav = trav->pointerarr[i];
							i = 0;
						}
					}
					else {
						trav = trav->pointerarr[i];
						i = 0;
					}
				}
			}
		}
		else if (sort_by == 'z') {
			node* trav = root_ptr;
			int i = 0;
			while (true)
			{
				if (trav->isleaf) {
					if (trav->elementcount == max_keys) {
						splitnode(trav);
						trav = root_ptr;
						i = 0;
					}
					else {
						inserttoleafz(trav, x1, x2, c1);
						i = 0;
						break;
					}
				}
				else {
					if (c1 > trav->z[i]) {
						i++;
						if (trav->elementcount == i) {
							trav = trav->pointerarr[i];
							i = 0;
						}
					}
					else {
						trav = trav->pointerarr[i];
						i = 0;
					}
				}
			}
		}
	}
}

void btree::splitnode(node* ptr) {
	node* newnode = new node(max_keys, max_child);
	for (int x = max_child / 2; x < max_keys; x++) {
		if (!(ptr->isleaf)) {
			if (ptr->pointerarr[x] != NULL) {
				ptr->pointerarr[x]->parent = newnode;
			}
		}
		newnode->pointerarr[x - (max_child / 2)] = ptr->pointerarr[x];
		ptr->pointerarr[x] = NULL;
		newnode->x[x - (max_child / 2)] = ptr->x[x];
		ptr->x[x] = NULL;
		newnode->y[x - (max_child / 2)] = ptr->y[x];
		ptr->y[x] = NULL;
		newnode->z[x - (max_child / 2)] = ptr->z[x];
		ptr->z[x] = NULL;
		newnode->elementcount++;
		ptr->elementcount--;
	}
	if (!(ptr->isleaf)) {
		if (ptr->pointerarr[max_keys] != NULL) {
			ptr->pointerarr[max_keys]->parent = newnode;
		}
	}
	newnode->pointerarr[(max_child / 2) - 1] = ptr->pointerarr[max_keys];
	ptr->pointerarr[max_keys] = NULL;
	newnode->parent = ptr->parent;
	if (ptr->isleaf) {
		newnode->isleaf = true;
	}
	else {
		newnode->isleaf = false;
	}
	if (ptr->parent == NULL) {
		node* nparent = new node(max_keys, max_child);
		nparent->isleaf = false;
		newnode->parent = nparent;
		ptr->parent = nparent;
		nparent->pointerarr[0] = ptr;
		nparent->pointerarr[1] = newnode;
		if (ptr == root_ptr) {
			root_ptr = nparent;
		}
		nparent->x[0] = ptr->x[max_keys / 2];
		nparent->y[0] = ptr->y[max_keys / 2];
		nparent->z[0] = ptr->z[max_keys / 2];
		nparent->elementcount++;
		ptr->elementcount--;
		ptr->x[max_keys / 2] = NULL;
		ptr->y[max_keys / 2] = NULL;
		ptr->z[max_keys / 2] = NULL;
	}
	else {
		if (ptr->parent->elementcount == max_keys) {
			splitnode(ptr->parent);
		}
		if (sort_by == 'z') {
			inserttononleafz(ptr->parent, ptr, newnode, ptr->x[max_keys / 2], ptr->y[max_keys / 2], ptr->z[max_keys / 2]);
		}
		else if (sort_by == 'x') {
			inserttononleafx(ptr->parent, ptr, newnode, ptr->x[max_keys / 2], ptr->y[max_keys / 2], ptr->z[max_keys / 2]);
		}
		else {
			inserttononleafy(ptr->parent, ptr, newnode, ptr->x[max_keys / 2], ptr->y[max_keys / 2], ptr->z[max_keys / 2]);
		}
		ptr->x[max_keys / 2] = NULL;
		ptr->y[max_keys / 2] = NULL;
		ptr->z[max_keys / 2] = NULL;
		ptr->elementcount--;

	}
}

void btree::inserttoleafz(node* ptr, int x1, int x2, char c1) {
	for (int x = 0; x < ptr->elementcount; x++) {
		if (c1 < ptr->z[x]) {
			for (int i = ptr->elementcount; i > x; i--) {
				ptr->z[i] = ptr->z[i - 1];
				ptr->y[i] = ptr->y[i - 1];
				ptr->x[i] = ptr->x[i - 1];
			}
			ptr->z[x] = c1;
			ptr->x[x] = x1;
			ptr->y[x] = x2;
			ptr->elementcount++;
			return;
		}
	}
	ptr->z[ptr->elementcount] = c1;
	ptr->x[ptr->elementcount] = x1;
	ptr->y[ptr->elementcount] = x2;
	ptr->elementcount++;
}

void btree::inserttoleafx(node* ptr, int x1, int x2, char c1) {
	for (int x = 0; x < ptr->elementcount; x++) {
		if (x1 < ptr->x[x]) {
			for (int i = ptr->elementcount; i > x; i--) {
				ptr->z[i] = ptr->z[i - 1];
				ptr->y[i] = ptr->y[i - 1];
				ptr->x[i] = ptr->x[i - 1];
			}
			ptr->z[x] = c1;
			ptr->x[x] = x1;
			ptr->y[x] = x2;
			ptr->elementcount++;
			return;
		}
	}
	ptr->z[ptr->elementcount] = c1;
	ptr->x[ptr->elementcount] = x1;
	ptr->y[ptr->elementcount] = x2;
	ptr->elementcount++;
}

void btree::inserttoleafy(node* ptr, int x1, int x2, char c1) {
	for (int x = 0; x < ptr->elementcount; x++) {
		if (x2 < ptr->y[x]) {
			for (int i = ptr->elementcount; i > x; i--) {
				ptr->z[i] = ptr->z[i - 1];
				ptr->y[i] = ptr->y[i - 1];
				ptr->x[i] = ptr->x[i - 1];
			}
			ptr->z[x] = c1;
			ptr->x[x] = x1;
			ptr->y[x] = x2;
			ptr->elementcount++;
			return;
		}
	}
	ptr->z[ptr->elementcount] = c1;
	ptr->x[ptr->elementcount] = x1;
	ptr->y[ptr->elementcount] = x2;
	ptr->elementcount++;
}

void btree::inserttononleafz(node* ptr, node* pointer, node* pointtr, int x1, int x2, char c1) {
	if (ptr->parent) {
		ptr = ptr->parent->pointerarr[ptr->parent->elementcount];
		for (int i = 0; i < ptr->parent->elementcount; i++) {
			if (c1 < ptr->parent->z[i]) {
				ptr = ptr->parent->pointerarr[i];
			}
		}
	}
	for (int x = 0; x < ptr->elementcount; x++) {
		if (c1 < ptr->z[x]) {
			for (int i = ptr->elementcount; i > x; i--) {
				ptr->z[i] = ptr->z[i - 1];
				ptr->y[i] = ptr->y[i - 1];
				ptr->x[i] = ptr->x[i - 1];
				ptr->pointerarr[i + 1] = ptr->pointerarr[i];
			}
			ptr->pointerarr[x] = pointer;
			ptr->pointerarr[x + 1] = pointtr;
			ptr->z[x] = c1;
			ptr->x[x] = x1;
			ptr->y[x] = x2;
			ptr->elementcount++;
			return;
		}
	}
	ptr->z[ptr->elementcount] = c1;
	ptr->x[ptr->elementcount] = x1;
	ptr->y[ptr->elementcount] = x2;
	ptr->pointerarr[ptr->elementcount] = pointer;
	ptr->pointerarr[ptr->elementcount + 1] = pointtr;
	ptr->elementcount++;
}

void btree::inserttononleafx(node* ptr, node* pointer, node* pointtr, int x1, int x2, char c1) {
	if (ptr->parent) {
		ptr = ptr->parent->pointerarr[ptr->parent->elementcount];
		for (int i = 0; i < ptr->parent->elementcount; i++) {
			if (x1 < ptr->parent->x[i]) {
				ptr = ptr->parent->pointerarr[i];
			}
		}
	}
	for (int x = 0; x < ptr->elementcount; x++) {
		if (x1 < ptr->x[x]) {
			for (int i = ptr->elementcount; i > x; i--) {
				ptr->z[i] = ptr->z[i - 1];
				ptr->y[i] = ptr->y[i - 1];
				ptr->x[i] = ptr->x[i - 1];
				ptr->pointerarr[i + 1] = ptr->pointerarr[i];
			}
			ptr->pointerarr[x] = pointer;
			ptr->pointerarr[x + 1] = pointtr;
			ptr->z[x] = c1;
			ptr->x[x] = x1;
			ptr->y[x] = x2;
			ptr->elementcount++;
			return;
		}
	}
	ptr->z[ptr->elementcount] = c1;
	ptr->x[ptr->elementcount] = x1;
	ptr->y[ptr->elementcount] = x2;
	ptr->pointerarr[ptr->elementcount] = pointer;
	ptr->pointerarr[ptr->elementcount + 1] = pointtr;
	ptr->elementcount++;
}

void btree::inserttononleafy(node* ptr, node* pointer, node* pointtr, int x1, int x2, char c1) {
	if (ptr->parent) {
		ptr = ptr->parent->pointerarr[ptr->parent->elementcount];
		for (int i = 0; i < ptr->parent->elementcount; i++) {
			if (x2 < ptr->parent->y[i]) {
				ptr = ptr->parent->pointerarr[i];
			}
		}
	}
	for (int x = 0; x < ptr->elementcount; x++) {
		if (x2 < ptr->y[x]) {
			for (int i = ptr->elementcount; i > x; i--) {
				ptr->z[i] = ptr->z[i - 1];
				ptr->y[i] = ptr->y[i - 1];
				ptr->x[i] = ptr->x[i - 1];
				ptr->pointerarr[i + 1] = ptr->pointerarr[i];
			}
			ptr->pointerarr[x] = pointer;
			ptr->pointerarr[x + 1] = pointtr;
			ptr->z[x] = c1;
			ptr->x[x] = x1;
			ptr->y[x] = x2;
			ptr->elementcount++;
			return;
		}
	}
	ptr->z[ptr->elementcount] = c1;
	ptr->x[ptr->elementcount] = x1;
	ptr->y[ptr->elementcount] = x2;
	ptr->pointerarr[ptr->elementcount] = pointer;
	ptr->pointerarr[ptr->elementcount + 1] = pointtr;
	ptr->elementcount++;
}


int main() {
	int node_count;
	cin >> node_count;
	int degree;
	cin >> degree;
	int min_keys = degree - 1;
	int max_keys = (degree * 2) - 1;
	int max_child = degree * 2;
	char sort_by;
	cin >> sort_by;
	btree* tree = new btree(min_keys, degree, max_keys, max_child, sort_by); 
	while (node_count > 0) {
		int x1, x2;
		char c1;
		cin >> x1 >> x2 >> c1;
		tree->insert(x1, x2, c1);
		node_count--;
	}
	if (sort_by == 'z') {
		char deleth;
		cin >> deleth;
		tree->deletechar(deleth);
	}
	else if(sort_by == 'x'){
		int deleth;
		cin >> deleth;
		tree->deletex(deleth);
	}
	else {
		int deleth;
		cin >> deleth;
		tree->deletey(deleth);
	}
	tree->printtree(tree->root_ptr);
}

void btree::printtree(node* ptr) {
	for (int x = 0; x < ptr->elementcount; x++) {
		cout << "(" << ptr->x[x] << "," << ptr->y[x] << "," << ptr->z[x] << ")";
	}
	cout << "\n";
	for (int x = 0; x < ptr->elementcount + 1; x++) {
		if (ptr->pointerarr[x] != NULL) {
			printtree(ptr->pointerarr[x]);
		}
	}
}

void btree::deletechar(char del) {
	node* trav = new node(max_keys, max_child);
	trav = root_ptr;
	int left_el_count = 0;
	int right_el_count = 0;
	while (true) {
		if (!(trav->isleaf)) {
			for (int x = 0; x < trav->elementcount; x++) {
				if (del == trav->z[x]) {
					deleteinternalnodez(trav,del);
					return;
				}
				if (del < trav->z[x]) {
					if (x != 0) {
						left_el_count = trav->pointerarr[x - 1]->elementcount;
					}
					else {
						left_el_count = 0;
					}
					if (x != trav->elementcount) {
						right_el_count = trav->pointerarr[x + 1]->elementcount;
					}
					else {
						right_el_count = 0;
					}
					trav = trav->pointerarr[x];
					break;
				}
				if (x == trav->elementcount - 1 && del > trav->z[x]) {
					left_el_count = trav->pointerarr[trav->elementcount - 1]->elementcount;
					right_el_count = 0;
					trav = trav->pointerarr[trav->elementcount];
					break;
				}
			}
		}
		deleteleafz(trav,left_el_count,right_el_count, del);
		break;
	}
}

void btree::deletex(int del) {
	node* trav = new node(max_keys, max_child);
	trav = root_ptr;
	int left_el_count = 0;
	int right_el_count = 0;
	while (true) {
		if (!(trav->isleaf)) {
			for (int x = 0; x < trav->elementcount; x++) {
				if (del == trav->x[x]) {
					deleteinternalnodex(trav, del);
					return;
				}
				if (del < trav->x[x]) {
					if (x != 0) {
						left_el_count = trav->pointerarr[x - 1]->elementcount;
					}
					else {
						left_el_count = 0;
					}
					if (x != trav->elementcount) {
						right_el_count = trav->pointerarr[x + 1]->elementcount;
					}
					else {
						right_el_count = 0;
					}
					trav = trav->pointerarr[x];
					break;
				}
				if (x == trav->elementcount - 1 && del > trav->x[x]) {
					left_el_count = trav->pointerarr[trav->elementcount - 1]->elementcount;
					right_el_count = 0;
					trav = trav->pointerarr[trav->elementcount];
					break;
				}
			}
		}
		deleteleafx(trav, left_el_count, right_el_count, del);
		break;
	}
}

void btree::deletey(int del) {
	node* trav = new node(max_keys, max_child);
	trav = root_ptr;
	int left_el_count = 0;
	int right_el_count = 0;
	while (true) {
		if (!(trav->isleaf)) {
			for (int x = 0; x < trav->elementcount; x++) {
				if (del == trav->y[x]) {
					deleteinternalnodey(trav, del);
					return;
				}
				if (del < trav->y[x]) {
					if (x != 0) {
						left_el_count = trav->pointerarr[x - 1]->elementcount;
					}
					else {
						left_el_count = 0;
					}
					if (x != trav->elementcount) {
						right_el_count = trav->pointerarr[x + 1]->elementcount;
					}
					else {
						right_el_count = 0;
					}
					trav = trav->pointerarr[x];
					break;
				}
				if (x == trav->elementcount - 1 && del > trav->y[x]) {
					left_el_count = trav->pointerarr[trav->elementcount - 1]->elementcount;
					right_el_count = 0;
					trav = trav->pointerarr[trav->elementcount];
					break;
				}
			}
		}
		deleteleafy(trav, left_el_count, right_el_count, del);
		break;
	}
}

void btree::deleteleafz(node* trav, int left_el_ct, int right_el_ct, char del) {
	if (trav->elementcount > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->z[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;
	}
	else if (left_el_ct > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->z[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
		index = 0;
		for (int x = 0; x < trav->parent->elementcount + 1; x++) {
			if (trav == trav->parent->pointerarr[x]) {
				index = x;
				break;
			}
		}
		inserttoleafz(trav, trav->parent->x[index - 1], trav->parent->y[index - 1], trav->parent->z[index - 1]);
		trav->parent->x[index - 1] = trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav->parent->y[index - 1] = trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav->parent->z[index - 1] = trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav = trav->parent->pointerarr[index - 1];
		del = trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount - 1];
		index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->z[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;		
	}
	else if (right_el_ct > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->z[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
		index = 0;
		for (int x = 0; x < trav->parent->elementcount + 1; x++) {
			if (trav == trav->parent->pointerarr[x]) {
				index = x;
				break;
			}
		}
		inserttoleafz(trav, trav->parent->x[index], trav->parent->y[index], trav->parent->z[index]);
		trav->parent->x[index] = trav->parent->pointerarr[index + 1]->x[0];
		trav->parent->y[index] = trav->parent->pointerarr[index + 1]->y[0];
		trav->parent->z[index] = trav->parent->pointerarr[index + 1]->z[0];
		del = trav->parent->pointerarr[index + 1]->z[0];
		trav = trav->parent->pointerarr[index + 1];
		index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->z[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
	}
	else{
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->z[x]) {
			index = x;
			break;
		}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;
		index = 0;
		if (left_el_ct > 0) {
			for (int x = 0; x < trav->parent->elementcount + 1; x++) {
				if (trav == trav->parent->pointerarr[x]) {
					index = x;
					break;
				}
			}
			trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->x[index - 1];
			trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->y[index - 1];
			trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->z[index - 1];
			trav->parent->pointerarr[index - 1]->elementcount++;
			for (int x = 0; x < trav->elementcount; x++) {
				trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount] = trav->x[x];
				trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount] = trav->y[x];
				trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount] = trav->z[x];
				trav->parent->pointerarr[index - 1]->elementcount++;
			}
			for (int x = index; x < trav->parent->elementcount - 1; x++) {
				trav->parent->x[x - 1] = trav->parent->x[x];
				trav->parent->y[x - 1] = trav->parent->y[x];
				trav->parent->z[x - 1] = trav->parent->z[x];
				trav->parent->pointerarr[x] = trav->parent->pointerarr[x + 1];
			}
			trav->parent->elementcount--;
			node* ntrav = trav->parent;
			delete trav;
			if (ntrav->elementcount < min_keys && ntrav != root_ptr) {// n
				ntrav->z[ntrav->elementcount] = '~';
				ntrav->x[ntrav->elementcount] = 0;
				ntrav->y[ntrav->elementcount] = 0;
				ntrav->elementcount++;
			}
		}
		else if (right_el_ct > 0) {
			for (int x = 0; x < trav->parent->elementcount + 1; x++) {
				if (trav == trav->parent->pointerarr[x]) {
					index = x;
					break;
				}
			}
			inserttoleafz(trav->parent->pointerarr[index + 1],trav->parent->x[index], trav->parent->y[index], trav->parent->z[index]);
			for (int x = 0; x < trav->elementcount; x++) {
				inserttoleafz(trav->parent->pointerarr[index + 1], trav->x[x], trav->y[x], trav->z[x]);
			}
			for (int x = index; x < trav->parent->elementcount - 1; x++) {
				trav->parent->x[x] = trav->parent->x[x + 1];
				trav->parent->y[x] = trav->parent->y[x + 1];
				trav->parent->z[x] = trav->parent->z[x + 1];
				trav->parent->pointerarr[x] = trav->parent->pointerarr[x + 1];
			}
			trav->parent->x[trav->parent->elementcount - 1] = NULL;
			trav->parent->y[trav->parent->elementcount - 1] = NULL;
			trav->parent->z[trav->parent->elementcount - 1] = NULL;
			trav->parent->pointerarr[trav->parent->elementcount - 1] = trav->parent->pointerarr[trav->parent->elementcount];
			trav->parent->pointerarr[trav->parent->elementcount]= NULL;
			trav->parent->elementcount--;
			delete trav;
		}
	}
}


void btree::deleteleafx(node* trav, int left_el_ct, int right_el_ct, int del) {
	if (trav->elementcount > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->x[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;
	}
	else if (left_el_ct > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->x[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
		index = 0;
		for (int x = 0; x < trav->parent->elementcount + 1; x++) {
			if (trav == trav->parent->pointerarr[x]) {
				index = x;
				break;
			}
		}
		inserttoleafx(trav, trav->parent->x[index - 1], trav->parent->y[index - 1], trav->parent->z[index - 1]);
		trav->parent->x[index - 1] = trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav->parent->y[index - 1] = trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav->parent->z[index - 1] = trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav = trav->parent->pointerarr[index - 1];
		del = trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount - 1];
		index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->x[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
	}
	else if (right_el_ct > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->x[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
		index = 0;
		for (int x = 0; x < trav->parent->elementcount + 1; x++) {
			if (trav == trav->parent->pointerarr[x]) {
				index = x;
				break;
			}
		}
		inserttoleafx(trav, trav->parent->x[index], trav->parent->y[index], trav->parent->z[index]);
		trav->parent->x[index] = trav->parent->pointerarr[index + 1]->x[0];
		trav->parent->y[index] = trav->parent->pointerarr[index + 1]->y[0];
		trav->parent->z[index] = trav->parent->pointerarr[index + 1]->z[0];
		del = trav->parent->pointerarr[index + 1]->x[0];
		trav = trav->parent->pointerarr[index + 1];
		index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->x[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
	}
	else {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->x[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;
		index = 0;
		if (left_el_ct > 0) {
			for (int x = 0; x < trav->parent->elementcount + 1; x++) {
				if (trav == trav->parent->pointerarr[x]) {
					index = x;
					break;
				}
			}
			trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->x[index - 1];
			trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->y[index - 1];
			trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->z[index - 1];
			trav->parent->pointerarr[index - 1]->elementcount++;
			for (int x = 0; x < trav->elementcount; x++) {
				trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount] = trav->x[x];
				trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount] = trav->y[x];
				trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount] = trav->z[x];
				trav->parent->pointerarr[index - 1]->elementcount++;
			}
			for (int x = index; x < trav->parent->elementcount - 1; x++) {
				trav->parent->x[x - 1] = trav->parent->x[x];
				trav->parent->y[x - 1] = trav->parent->y[x];
				trav->parent->z[x - 1] = trav->parent->z[x];
				trav->parent->pointerarr[x] = trav->parent->pointerarr[x + 1];
			}
			trav->parent->elementcount--;
			node* ntrav = trav->parent;
			delete trav;
			if (ntrav->elementcount < min_keys && ntrav != root_ptr) {// n
				ntrav->z[ntrav->elementcount] = '~';
				ntrav->x[ntrav->elementcount] = 0;
				ntrav->y[ntrav->elementcount] = 0;
				ntrav->elementcount++;
			}
		}
		else if (right_el_ct > 0) {
			for (int x = 0; x < trav->parent->elementcount + 1; x++) {
				if (trav == trav->parent->pointerarr[x]) {
					index = x;
					break;
				}
			}
			inserttoleafx(trav->parent->pointerarr[index + 1], trav->parent->x[index], trav->parent->y[index], trav->parent->z[index]);
			for (int x = 0; x < trav->elementcount; x++) {
				inserttoleafx(trav->parent->pointerarr[index + 1], trav->x[x], trav->y[x], trav->z[x]);
			}
			for (int x = index; x < trav->parent->elementcount - 1; x++) {
				trav->parent->x[x] = trav->parent->x[x + 1];
				trav->parent->y[x] = trav->parent->y[x + 1];
				trav->parent->z[x] = trav->parent->z[x + 1];
				trav->parent->pointerarr[x] = trav->parent->pointerarr[x + 1];
			}
			trav->parent->x[trav->parent->elementcount - 1] = NULL;
			trav->parent->y[trav->parent->elementcount - 1] = NULL;
			trav->parent->z[trav->parent->elementcount - 1] = NULL;
			trav->parent->pointerarr[trav->parent->elementcount - 1] = trav->parent->pointerarr[trav->parent->elementcount];
			trav->parent->pointerarr[trav->parent->elementcount] = NULL;
			trav->parent->elementcount--;
			delete trav;
		}
	}
}


void btree::deleteleafy(node* trav, int left_el_ct, int right_el_ct, int del) {
	if (trav->elementcount > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->y[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;
	}
	else if (left_el_ct > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->y[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
		index = 0;
		for (int x = 0; x < trav->parent->elementcount + 1; x++) {
			if (trav == trav->parent->pointerarr[x]) {
				index = x;
				break;
			}
		}
		inserttoleafz(trav, trav->parent->x[index - 1], trav->parent->y[index - 1], trav->parent->z[index - 1]);
		trav->parent->x[index - 1] = trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav->parent->y[index - 1] = trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav->parent->z[index - 1] = trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount - 1];
		trav = trav->parent->pointerarr[index - 1];
		del = trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount - 1];
		index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->y[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;		
	}
	else if (right_el_ct > min_keys) {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->y[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
		index = 0;
		for (int x = 0; x < trav->parent->elementcount + 1; x++) {
			if (trav == trav->parent->pointerarr[x]) {
				index = x;
				break;
			}
		}
		inserttoleafz(trav, trav->parent->x[index], trav->parent->y[index], trav->parent->z[index]);
		trav->parent->x[index] = trav->parent->pointerarr[index + 1]->x[0];
		trav->parent->y[index] = trav->parent->pointerarr[index + 1]->y[0];
		trav->parent->z[index] = trav->parent->pointerarr[index + 1]->z[0];
		del = trav->parent->pointerarr[index + 1]->y[0];
		trav = trav->parent->pointerarr[index + 1];
		index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->y[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;	
	}
	else {
		int index = 0;
		for (int x = 0; x < trav->elementcount; x++) {
			if (del == trav->y[x]) {
				index = x;
				break;
			}
		}
		for (int x = index; x < trav->elementcount - 1; x++) {
			trav->z[x] = trav->z[x + 1];
			trav->y[x] = trav->y[x + 1];
			trav->x[x] = trav->x[x + 1];
		}
		trav->z[trav->elementcount - 1] = NULL;
		trav->x[trav->elementcount - 1] = NULL;
		trav->y[trav->elementcount - 1] = NULL;
		trav->elementcount--;
		index = 0;
		if (left_el_ct > 0) {
			for (int x = 0; x < trav->parent->elementcount + 1; x++) {
				if (trav == trav->parent->pointerarr[x]) {
					index = x;
					break;
				}
			}
			trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->x[index - 1];
			trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->y[index - 1];
			trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount] = trav->parent->z[index - 1];
			trav->parent->pointerarr[index - 1]->elementcount++;
			for (int x = 0; x < trav->elementcount; x++) {
				trav->parent->pointerarr[index - 1]->x[trav->parent->pointerarr[index - 1]->elementcount] = trav->x[x];
				trav->parent->pointerarr[index - 1]->y[trav->parent->pointerarr[index - 1]->elementcount] = trav->y[x];
				trav->parent->pointerarr[index - 1]->z[trav->parent->pointerarr[index - 1]->elementcount] = trav->z[x];
				trav->parent->pointerarr[index - 1]->elementcount++;
			}
			for (int x = index; x < trav->parent->elementcount - 1; x++) {
				trav->parent->x[x - 1] = trav->parent->x[x];
				trav->parent->y[x - 1] = trav->parent->y[x];
				trav->parent->z[x - 1] = trav->parent->z[x];
				trav->parent->pointerarr[x] = trav->parent->pointerarr[x + 1];
			}
			trav->parent->elementcount--;
			node* ntrav = trav->parent;
			delete trav;
			if (ntrav->elementcount < min_keys && ntrav != root_ptr) {// n
				ntrav->z[ntrav->elementcount] = '~';
				ntrav->x[ntrav->elementcount] = 0;
				ntrav->y[ntrav->elementcount] = 0;
				ntrav->elementcount++;
			}
		}
		else if (right_el_ct > 0) {
			for (int x = 0; x < trav->parent->elementcount + 1; x++) {
				if (trav == trav->parent->pointerarr[x]) {
					index = x;
					break;
				}
			}
			inserttoleafy(trav->parent->pointerarr[index + 1], trav->parent->x[index], trav->parent->y[index], trav->parent->z[index]);
			for (int x = 0; x < trav->elementcount; x++) {
				inserttoleafy(trav->parent->pointerarr[index + 1], trav->x[x], trav->y[x], trav->z[x]);
			}
			for (int x = index; x < trav->parent->elementcount - 1; x++) {
				trav->parent->x[x] = trav->parent->x[x + 1];
				trav->parent->y[x] = trav->parent->y[x + 1];
				trav->parent->z[x] = trav->parent->z[x + 1];
				trav->parent->pointerarr[x] = trav->parent->pointerarr[x + 1];
			}
			trav->parent->x[trav->parent->elementcount - 1] = NULL;
			trav->parent->y[trav->parent->elementcount - 1] = NULL;
			trav->parent->z[trav->parent->elementcount - 1] = NULL;
			trav->parent->pointerarr[trav->parent->elementcount - 1] = trav->parent->pointerarr[trav->parent->elementcount];
			trav->parent->pointerarr[trav->parent->elementcount] = NULL;
			trav->parent->elementcount--;
			delete trav;
		}
	}
}



void btree::deleteinternalnodez(node* trav,char del) {
	int index = 0;
	for (int x = 0; x < trav->elementcount; x++) {
		if (del == trav->z[x]) {
			index = x;
			break;
		}
	}
	int target_index;
	node* target = trav->pointerarr[index];
	while (true) {
		if (target->isleaf) {
			target_index = target->elementcount - 1;
			break;
		}
		target = target->pointerarr[target->elementcount];
	}
	if (target->elementcount > min_keys) {
		int a = target->x[target_index];
		int b = target->y[target_index];
		char c = target->z[target_index];
		deletechar(c);
		trav->z[index] = c;
		trav->x[index] = a;
		trav->y[index] = b;
		return;
	}
	target = trav->pointerarr[index + 1];
	while (true) {
		if (target->isleaf) {
			target_index = 0;
			break;
		}
		target = target->pointerarr[0];
	}
	if (target->elementcount > min_keys) {
		int a = target->x[target_index];
		int b = target->y[target_index];
		char c = target->z[target_index];
		deletechar(c);
		trav->z[index] = c;
		trav->x[index] = a;
		trav->y[index] = b;
		return;
	}
	target = trav->pointerarr[index];
	while (true) {
		if (target->isleaf) {
			target_index = target->elementcount - 1;
			break;
		}
		target = target->pointerarr[target->elementcount];
	}
	int a = target->x[target_index];
	int b = target->y[target_index];
	char c = target->z[target_index];
	deletechar(c);
	trav->z[index] = c;
	trav->x[index] = a;
	trav->y[index] = b;
}

void btree::deleteinternalnodex(node* trav, int del) {
	int index = 0;
	for (int x = 0; x < trav->elementcount; x++) {
		if (del == trav->x[x]) {
			index = x;
			break;
		}
	}
	int target_index;
	node* target = trav->pointerarr[index];
	while (true) {
		if (target->isleaf) {
			target_index = target->elementcount - 1;
			break;
		}
		target = target->pointerarr[target->elementcount];
	}
	if (target->elementcount > min_keys) {
		int a = target->x[target_index];
		int b = target->y[target_index];
		char c = target->z[target_index];
		deletex(a);
		trav->z[index] = c;
		trav->x[index] = a;
		trav->y[index] = b;
		return;
	}
	target = trav->pointerarr[index + 1];
	while (true) {
		if (target->isleaf) {
			target_index = 0;
			break;
		}
		target = target->pointerarr[0];
	}
	if (target->elementcount > min_keys) {
		int a = target->x[target_index];
		int b = target->y[target_index];
		char c = target->z[target_index];
		deletex(a);
		trav->z[index] = c;
		trav->x[index] = a;
		trav->y[index] = b;
		return;
	}
	target = trav->pointerarr[index];
	while (true) {
		if (target->isleaf) {
			target_index = target->elementcount - 1;
			break;
		}
		target = target->pointerarr[target->elementcount];
	}
	int a = target->x[target_index];
	int b = target->y[target_index];
	char c = target->z[target_index];
	deletex(a);
	trav->z[index] = c;
	trav->x[index] = a;
	trav->y[index] = b;
}

void btree::deleteinternalnodey(node* trav, int del) {
	int index = 0;
	for (int x = 0; x < trav->elementcount; x++) {
		if (del == trav->y[x]) {
			index = x;
			break;
		}
	}
	int target_index;
	node* target = trav->pointerarr[index];
	while (true) {
		if (target->isleaf) {
			target_index = target->elementcount - 1;
			break;
		}
		target = target->pointerarr[target->elementcount];
	}
	if (target->elementcount > min_keys) {
		int a = target->x[target_index];
		int b = target->y[target_index];
		char c = target->z[target_index];
		deletey(b);
		trav->z[index] = c;
		trav->x[index] = a;
		trav->y[index] = b;
		return;
	}
	target = trav->pointerarr[index + 1];
	while (true) {
		if (target->isleaf) {
			target_index = 0;
			break;
		}
		target = target->pointerarr[0];
	}
	if (target->elementcount > min_keys) {
		int a = target->x[target_index];
		int b = target->y[target_index];
		char c = target->z[target_index];
		deletey(b);
		trav->z[index] = c;
		trav->x[index] = a;
		trav->y[index] = b;
		return;
	}
	target = trav->pointerarr[index];
	while (true) {
		if (target->isleaf) {
			target_index = target->elementcount - 1;
			break;
		}
		target = target->pointerarr[target->elementcount];
	}
	int a = target->x[target_index];
	int b = target->y[target_index];
	char c = target->z[target_index];
	deletey(b);
	trav->z[index] = c;
	trav->x[index] = a;
	trav->y[index] = b;
}