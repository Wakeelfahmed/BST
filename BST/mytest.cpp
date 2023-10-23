#include "satnet.h"
#include <iostream>
using namespace std;

class Tester {
public:
	// Test the insertion function for a normal case.
	static bool testInsertion() {
		SatNet network;
		Sat satellite(12345, MI208, I53, ACTIVE);

		network.insert(satellite);

		// Check if the satellite exists in the tree
		return network.findSatellite(12345);
	}

	// Test the insertion function for an edge case.
	static bool testInsertionEdgeCase() {
		SatNet network;
		Sat satellite1(10000, MI208, I53, ACTIVE);
		Sat satellite2(99999, MI350, I97, ACTIVE);

		network.insert(satellite1);
		network.insert(satellite2);

		// Check if both satellites exist in the tree
		return network.findSatellite(10000) && network.findSatellite(99999);
	}

	// Test the insertion function for an error case (duplicate ID).
	static bool testInsertionErrorCase() {
		SatNet network;
		Sat satellite1(10000, MI208, I53, ACTIVE);
		Sat satellite2(10000, MI350, I97, ACTIVE);  // Duplicate ID

		network.insert(satellite1);
		network.insert(satellite2);

		// Check if the second insertion fails (duplicate ID)
		if (network.countSatellites(I97) == 0) {
			//cout << "Not inserted";
			return 1;
		}
		return 0;
		//return !network.findSatellite(10000);
	}

	// Test whether the tree is balanced after a decent number of insertions (300 insertions).
	static bool testBalancingAfterInsertions() {
		SatNet network;
		for (int id = MINID; id <= MINID + 300; id++) {
			Sat satellite(id, MI208, I53, ACTIVE);
			network.insert(satellite);
		}

		// Check if the tree is balanced (height difference <= 1)
		return isBalanced(network.m_root);
	}

	// Test whether the BST property is preserved after all insertions.
	static bool testBSTPropertyAfterInsertions() {
		SatNet network;
		for (int id = MINID; id <= MINID + 300; id++) {
			Sat satellite(id, MI208, I53, ACTIVE);
			network.insert(satellite);
		}

		// Check if the BST property is preserved
		return isBST(network.m_root, MINID, MINID + 300);
	}

	// Test the remove function for a normal case.
	static bool testRemoval() {
		SatNet network;
		Sat satellite(12345, MI208, I53, ACTIVE);

		network.insert(satellite);
		network.remove(12345);

		// Check if the satellite is removed from the tree
		return !network.findSatellite(12345);
	}

	// Test the remove function for an edge case.
	static bool testRemovalEdgeCase() {
		SatNet network;
		Sat satellite1(10000, MI208, I53, ACTIVE);
		Sat satellite2(99999, MI350, I97, ACTIVE);

		network.insert(satellite1);
		network.insert(satellite2);
		network.remove(99999);

		// Check if the second satellite is removed from the tree
		return !network.findSatellite(99999);
	}

	// Test whether the tree is balanced after multiple removals.
	static bool testBalancingAfterRemovals() {
		SatNet network;
		int i = 1, to_break = 155;
		for (int id = MINID; id <= MINID + 300; id++) {
			Sat satellite(id, MI208, I53, ACTIVE);
			network.insert(satellite);
			//cout << i << endl;
			i++;

			//if (i == to_break)
				//break;
		}
		i = 1;
		for (int id = MINID + 150; id <= MINID + 300; id++) {
			network.remove(id);
			i++;
			//if (i == to_break)
				//break;
		}

		// Check if the tree is balanced (height difference <= 1)
		//return 1;
		bool isBalanced_temp = isBalanced(network.m_root);
		network.clear();
		return isBalanced_temp;
	}

	// Test whether the BST property is preserved after multiple removals.
	static bool testBSTPropertyAfterRemovals() {
		SatNet network;
		for (int id = MINID; id <= MINID + 300; id++) {
			Sat satellite(id, MI208, I53, ACTIVE);
			network.insert(satellite);
		}
		for (int id = MINID + 150; id <= MINID + 300; id++) {
			network.remove(id);
		}
		// Check if the BST property is preserved
		return isBST(network.m_root, MINID, MINID + 149);

	}
		//return isBST(network.m_root, MINID, MINID + 299); // Update the range to match the removed elements.

	// Test the removeDeorbited() functionality.
	static bool testRemoveDeorbited() {
		SatNet network;
		Sat satellite1(12345, MI208, I53, DEORBITED);
		Sat satellite2(67890, MI215, I70, ACTIVE);
		Sat satellite3(98765, MI340, I97, DEORBITED);

		network.insert(satellite1);
		network.insert(satellite2);
		network.insert(satellite3);

		network.removeDeorbited();

		// Check if deorbited satellites are removed
		return !network.findSatellite(12345) && !network.findSatellite(98765) && network.findSatellite(67890);
	}

	// Test the countSatellites(...) functionality.
	static bool testCountSatellites() {
		SatNet network;
		Sat satellite1(10001, MI208, I53, ACTIVE);
		Sat satellite2(10002, MI208, I53, ACTIVE);
		Sat satellite3(10003, MI340, I97, ACTIVE);
		Sat satellite4(10004, MI350, I53, ACTIVE);
		Sat satellite5(10005, MI215, I70, ACTIVE);

		network.insert(satellite1);
		network.insert(satellite2);
		network.insert(satellite3);
		network.insert(satellite4);
		network.insert(satellite5);

		int count = network.countSatellites(I53);

		// Check if the count of satellites with inclination I53 is correct
		return count == 3;
	}

	// Test the findSatellite(...) functionality for a normal case.
	static bool testFindSatellite() {
		SatNet network;
		Sat satellite(12345, MI208, I53, ACTIVE);

		network.insert(satellite);

		// Check if the findSatellite function returns true for an existing satellite
		return network.findSatellite(12345);
	}

	// Test the findSatellite(...) functionality for an error case.
	static bool testFindSatelliteErrorCase() {
		SatNet network;
		Sat satellite(12345, MI208, I53, ACTIVE);

		network.insert(satellite);

		// Check if the findSatellite function returns false for a non-existing satellite
		return !network.findSatellite(99999);
	}

	// Test the assignment operator for a normal case.
	static bool testAssignmentOperator() {
		SatNet network1;
		SatNet network2;
		Sat satellite(12345, MI208, I53, ACTIVE);

		network1.insert(satellite);
		network2 = network1;

		// Check if the assignment operator copied the satellite correctly
		return network2.findSatellite(12345);
	}

	// Test the assignment operator for an error case (empty object to empty object).
	static bool testAssignmentOperatorErrorCase() {
		SatNet network1;
		SatNet network2;

		network2 = network1;

		// Check if the assignment operator handles copying from an empty object to another empty object
		return !network2.findSatellite(12345);
	}

	// Helper function to check if the tree is balanced.
	static bool isBalanced(Sat* node) {
		if (node == nullptr) {
			return true;
		}

		int leftHeight = getHeight(node->getLeft());
		int rightHeight = getHeight(node->getRight());

		if (abs(leftHeight - rightHeight) <= 1 && isBalanced(node->getLeft()) && isBalanced(node->getRight())) {
			return true;
		}

		return false;
	}

	// Helper function to get the height of a node.
	static int getHeight(Sat* node) {
		if (node == nullptr) {
			return 0;
		}

		return node->getHeight();
	}

	// Helper function to check if the tree satisfies the BST property.
	static bool isBST(Sat* node, int minValue, int maxValue) {
		if (node == nullptr) {
			return true;
		}

		int id = node->getID();

		if (id < minValue || id > maxValue) {
			return false;
		}

		return isBST(node->getLeft(), minValue, id - 1) && isBST(node->getRight(), id + 1, maxValue);
	}
};

int main() {
	// Run test cases
	//bool testResult1 = Tester::testInsertion();  //bool testResult2 = Tester::testInsertionEdgeCase();	//bool testResult3 = Tester::testInsertionErrorCase();
	//bool testResult4 = Tester::testBalancingAfterInsertions();
	//bool testResult5 = Tester::testBSTPropertyAfterInsertions();
	//bool testResult6 = Tester::testRemoval();
	//bool testResult7 = Tester::testRemovalEdgeCase();

	//bool testResult8 = Tester::testBalancingAfterRemovals();
	//bool testResult9 = Tester::testBSTPropertyAfterRemovals();

	//bool testResult10 = Tester::testRemoveDeorbited();
	//bool testResult11 = Tester::testCountSatellites();
	//bool testResult12 = Tester::testFindSatellite();
	//bool testResult13 = Tester::testFindSatelliteErrorCase();
	//bool testResult14 = Tester::testAssignmentOperator();
	//bool testResult15 = Tester::testAssignmentOperatorErrorCase();

	cout << "Test 1: Insertion (Normal Case) - " << (Tester::testInsertion() ? "Passed" : "FAILED") << endl;
	cout << "Test 2: Insertion (Edge Case) - " << (Tester::testInsertionEdgeCase() ? "Passed" : "FAILED") << endl;
	cout << "Test 3: Insertion (Error Case) - " << (Tester::testInsertionErrorCase() ? "Passed" : "FAILED") << endl;
	cout << "Test 4: Balancing After Insertions - " << (Tester::testBalancingAfterInsertions() ? "Passed" : "FAILED") << endl;
	cout << "Test 5: BST Property After Insertions - " << (Tester::testBSTPropertyAfterInsertions() ? "Passed" : "FAILED") << endl;
	cout << "Test 6: Removal (Normal Case) - " << (Tester::testRemoval() ? "Passed" : "FAILED") << endl;
	cout << "Test 7: Removal (Edge Case) - " << (Tester::testRemovalEdgeCase() ? "Passed" : "FAILED") << endl;

	cout << "Test 8: Balancing After Removals - " << (Tester::testBalancingAfterRemovals() ? "Passed" : "FAILED") << endl;
	cout << "Test 9: BST Property After Removals - " << (Tester::testBSTPropertyAfterRemovals() ? "Passed" : "FAILED") << endl;

	cout << "Test 10: Remove Deorbited - " << (Tester::testRemoveDeorbited() ? "Passed" : "FAILED") << endl;
	cout << "Test 11: Count Satellites - " << (Tester::testCountSatellites() ? "Passed" : "FAILED") << endl;
	cout << "Test 12: Find Satellite (Normal Case) - " << (Tester::testFindSatellite() ? "Passed" : "FAILED") << endl;
	cout << "Test 13: Find Satellite (Error Case) - " << (Tester::testFindSatelliteErrorCase() ? "Passed" : "FAILED") << endl;
	cout << "Test 14: Assignment Operator (Normal Case) - " << (Tester::testAssignmentOperator() ? "Passed" : "FAILED") << endl;
	cout << "Test 15: Assignment Operator (Error Case) - " << (Tester::testAssignmentOperatorErrorCase() ? "Passed" : "FAILED") << endl;

	return 0;
}
