// UMBC - CMSC 341 - Fall 2023 - Proj2
#include "satnet.h"
int height(Sat* node) {
	if (node == nullptr) {
		return -1; // Height of an empty node is -1
	}
	return node->getHeight();
}

// Helper function to update the height of a node based on its children's heights
void updateHeight(Sat* node) {
	int leftHeight = height(node->getLeft());
	int rightHeight = height(node->getRight());
	node->setHeight(1 + max(leftHeight, rightHeight));
}

// Helper function to perform a left rotation
Sat* leftRotate(Sat* y) {
	Sat* x = y->getRight();
	Sat* T2 = x->getLeft();

	// Perform rotation
	x->setLeft(y);
	y->setRight(T2);

	// Update heights
	updateHeight(y);
	updateHeight(x);

	return x; // New root
}

// Helper function to perform a right rotation
Sat* rightRotate(Sat* x) {
	Sat* y = x->getLeft();
	Sat* T2 = y->getRight();

	// Perform rotation
	y->setRight(x);
	x->setLeft(T2);

	// Update heights
	updateHeight(x);
	updateHeight(y);

	return y; // New root
}

// Helper function to balance the tree after insertion
Sat* balance(Sat* node) {
	// Update height of the current node
	updateHeight(node);

	// Check balance factor
	int balanceFactor = height(node->getLeft()) - height(node->getRight());

	// Left heavy
	if (balanceFactor > 1) {
		if (height(node->getLeft()->getLeft()) >= height(node->getLeft()->getRight())) {
			return rightRotate(node);
		}
		else {
			node->setLeft(leftRotate(node->getLeft()));
			return rightRotate(node);
		}
	}
	// Right heavy
	if (balanceFactor < -1) {
		if (height(node->getRight()->getRight()) >= height(node->getRight()->getLeft())) {
			return leftRotate(node);
		}
		else {
			node->setRight(rightRotate(node->getRight()));
			return leftRotate(node);
		}
	}
	return node;
}


SatNet::SatNet() { m_root = nullptr; }
SatNet::~SatNet() { clear(); }
Sat* SatNet::insertHelper(Sat* node, const Sat& satellite) {
	if (node == nullptr) {
		// Create a new node
		return new Sat(satellite);
	}

	// Insertion based on the BST property
	if (satellite.getID() < node->getID()) {
		node->setLeft(insertHelper(node->getLeft(), satellite));
	}
	else if (satellite.getID() > node->getID()) {
		node->setRight(insertHelper(node->getRight(), satellite));
	}
	else {
		// Duplicate ID, do not insert
		return node;
	}

	// Update height
	updateHeight(node);

	// Rebalance the tree
	return balance(node);
}
void SatNet::insert(const Sat& satellite) {
	m_root = insertHelper(m_root, satellite);
}
void SatNet::clearHelper(Sat* node) {
	if (node != nullptr) {
		clearHelper(node->getLeft());
		clearHelper(node->getRight());
		delete node;
	}
}
void SatNet::clear() {
	// Implement the clear method to delete all nodes in the tree
	clearHelper(m_root);
	m_root = nullptr;
}

Sat* SatNet::removeHelper(Sat* node, int id) {
	if (node == nullptr) {
		return nullptr;
	}

	if (id < node->getID()) {
		node->setLeft(removeHelper(node->getLeft(), id));
	}
	else if (id > node->getID()) {
		node->setRight(removeHelper(node->getRight(), id));
	}
	else {
		// Node with the id to be deleted found

		// Node with only one child or no child
		if (node->getLeft() == nullptr || node->getRight() == nullptr) {
			Sat* temp = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();

			// No child case
			if (temp == nullptr) {
				temp = node;
				node = nullptr;
			}
			else {
				// One child case
				*node = *temp; // Copy the contents of the non-empty child
			}
			delete temp;
		}
		else {
			// Node with two children, get the inorder successor (smallest in the right subtree)
			Sat* temp = minValueNode(node->getRight());

			// Copy the inorder successor's data to this node
			*node = *temp;

			// Delete the inorder successor
			node->setRight(removeHelper(node->getRight(), temp->getID()));
		}
	}

	if (node == nullptr) {
		return node;
	}

	// Update height and balance
	updateHeight(node);
	return balance(node);
}
void SatNet::remove(int id) {
	// Implement the remove method to remove a satellite by id
	// Make sure to maintain the balance of the tree
	m_root = removeHelper(m_root, id);
}
Sat* SatNet::minValueNode(Sat* node) {
	Sat* current = node;
	while (current->getLeft() != nullptr) {
		current = current->getLeft();
	}
	return current;
}
void SatNet::dumpTree() const { 
	dump(m_root); }
void SatNet::dump(Sat* satellite) const {
	if (satellite != nullptr) {
		cout << "(";
		dump(satellite->m_left);//first visit the left child
		cout << satellite->m_id << ":" << satellite->m_height;//second visit the node itself
		dump(satellite->m_right);//third visit the right child
		cout << ")";
	}
}
void SatNet::listSatellitesHelper(Sat* node) const {
	if (node != nullptr) {
		listSatellitesHelper(node->getLeft());
		cout << "ID: " << node->getID() << ", State: " << node->getStateStr() << endl;
		listSatellitesHelper(node->getRight());
	}
}
void SatNet::listSatellites() const {
	listSatellitesHelper(m_root);
	cout << endl;
}
bool SatNet::setStateHelper(Sat* node, int id, STATE state) {
	if (node == nullptr) {
		return false;
	}

	if (id < node->getID()) {
		return setStateHelper(node->getLeft(), id, state);
	}
	else if (id > node->getID()) {
		return setStateHelper(node->getRight(), id, state);
	}
	else {
		// Node with the given id found, update its state
		node->setState(state);
		return true;
	}
}
bool SatNet::setState(int id, STATE state) {
	return setStateHelper(m_root, id, state);
}

Sat* SatNet::removeDeorbitedHelper(Sat* node) {
	if (node == nullptr) {
		return nullptr;
	}

	// Recursively remove deorbited satellites from left and right subtrees
	node->setLeft(removeDeorbitedHelper(node->getLeft()));
	node->setRight(removeDeorbitedHelper(node->getRight()));

	// If the current node is deorbited, delete it
	if (node->getState() == DEORBITED) {
		delete node;
		return nullptr;
	}

	return node;
}
void SatNet::removeDeorbited() {
	// Implement the removeDeorbited method to remove all satellites with DEORBITED state
	m_root = removeDeorbitedHelper(m_root);
}
bool SatNet::findSatelliteHelper(Sat* node, int id) const {
	if (node == nullptr) {
		return false;
	}
	if (id < node->getID()) {
		return findSatelliteHelper(node->getLeft(), id);
	}
	else if (id > node->getID()) {
		return findSatelliteHelper(node->getRight(), id);
	}
	else {
		// Node with the given id found
		return true;
	}
}
bool SatNet::findSatellite(int id) const {
	// Implement the findSatellite method to check if a satellite with a given id exists in the tree
	return findSatelliteHelper(m_root, id);
}
// Helper function to perform a deep copy of the tree
Sat* SatNet::deepCopy(const Sat* node) {
	if (node == nullptr) {
		return nullptr;
	}

	Sat* newNode = new Sat(node->getID(), node->getAlt(), node->getInclin(), node->getState());
	newNode->setLeft(deepCopy(node->getLeft()));
	newNode->setRight(deepCopy(node->getRight()));
	newNode->setHeight(std::max(height(newNode->getLeft()), height(newNode->getRight())) + 1);

	return newNode;
}
const SatNet& SatNet::operator=(const SatNet& rhs) {
	if (this != &rhs) {
		// Clear the current tree
		clear();

		// Implement copying logic here (deep copy)
		if (rhs.m_root) {
			m_root = deepCopy(rhs.m_root);
		}
	}
	return *this;
}
int SatNet::countSatellitesHelper(Sat* node, INCLIN degree) const {
	if (node == nullptr) {
		return 0;
	}
	int count = 0;
	if (node->getInclin() == degree) {
		count++;
	}
	count += countSatellitesHelper(node->getLeft(), degree);
	count += countSatellitesHelper(node->getRight(), degree);
	return count;
}
int SatNet::countSatellites(INCLIN degree) const {
	// Implement the countSatellites method to count satellites with a given inclination
	return countSatellitesHelper(m_root, degree);
}
