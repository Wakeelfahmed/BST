// UMBC - CMSC 341 - Fall 2023 - Proj2
#include "satnet.h"
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

void SatNet::clear() {

}

void SatNet::remove(int id) {

}

void SatNet::dumpTree() const {
	dump(m_root);
}

void SatNet::dump(Sat* satellite) const {
	if (satellite != nullptr) {
		cout << "(";
		dump(satellite->m_left);//first visit the left child
		cout << satellite->m_id << ":" << satellite->m_height;//second visit the node itself
		dump(satellite->m_right);//third visit the right child
		cout << ")";
	}
}
void SatNet::listSatellites() const {

}
bool SatNet::setState(int id, STATE state) {

}
void SatNet::removeDeorbited() {

}
bool SatNet::findSatellite(int id) const {

}
const SatNet& SatNet::operator=(const SatNet& rhs) {
	// Implement the assignment operator to create a deep copy of rhs
	// Make sure to handle memory properly
	if (this != &rhs) {
		clear(); // Clear the current tree

		// Implement copying logic here (deep copy)
	}
	return *this;
}
int SatNet::countSatellites(INCLIN degree) const {

}
