// CS300ProjectTwo.cpp
// CS 300 Project Two
// Matthew Maciak
// 4/14/2026
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//Define a structure to hold the course information
struct Course {
    string courseId;
    string name;
    vector<string> preRecs;
    Course() {

    }
};

//Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    //default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    delete root;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}



/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
    // remove node root courseID
    removeNode(root, courseId);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* curNode = new Node();
    curNode = this->root;

    // keep looping downwards until bottom reached or matching courseId found
    while (curNode != NULL) {
        // if match found, return current course
        if (curNode->course.courseId == courseId) {
            return curNode->course;
        }

        // if bid is smaller than current node then traverse left
        if (curNode->course.courseId > courseId) {
            curNode = curNode->left;
        }
        // else larger so traverse right
        else {
            curNode = curNode->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param Course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (course.courseId < node->course.courseId) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the left node
            this->addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output course information
        cout << node->course.courseId << ", " << node->course.name << endl;
        if (!node->course.preRecs.empty()) {
            cout << "Prerequisites: " << node->course.preRecs[0];
            for (int i = 1; i < node->course.preRecs.size(); ++i) {
                cout << ", " << node->course.preRecs[i];
            }
            cout << endl;
        }
        cout << endl;
        //InOder right
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output course information
        cout << node->course.courseId << ", " << node->course.courseId << ", " << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output course information
        cout << node->course.courseId << ", " << node->course.courseId << ", " << endl;
        //postOrder left
        postOrder(node->left);
        //postOrder right     
        postOrder(node->right);
    }
}

/**
 * Remove a course from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    // if node = nullptr return node
    if (node == nullptr) {
        return node;
    }
    // (otherwise recurse down the left subtree)
    if (courseId < node->course.courseId) {
        // check for match and if so, remove left node using recursive call 
        node->left = removeNode(node->left, courseId);

    }
    // (otherwise recurse down the right subtree)
    else if (courseId > node->course.courseId) {
        // check for match and if so, remove right node using recursive call
        node->right = removeNode(node->right, courseId);
    }
    // (otherwise no children so node is a leaf node)
    else {
        // if left node = nullptr && right node = nullptr delete node 
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return NULL;
        }
        // (otherwise check one child to the left)
        // if left node != nullptr && right node = nullptr delete node 
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;

        }
        // (otherwise check one child to the right)
        // if left node = nullptr && right node != nullptr delete node
        else if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // (otherwise more than one child so find the minimum)
        else {
            // create temp node to right
            Node* temp = node->right;
            // while left node is not nullptr keep moving temp left
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // make node bid (right) equal to temp course (left)
            node->course = temp->course;
            // remove right node using recursive call
            node->right = removeNode(node->right, temp->course.courseId);
        }
    }
    // return node
    return node;
}

//function to load csv file and populate BST with course objects
void populateBST(string filePath, BinarySearchTree* bst) {
    ifstream inFS;
    string line;
    string token;
    vector<string> tokens;

    string courseId;
    string name;
    vector <string> preRecs;

    inFS.open(filePath);
    if (!inFS.is_open()) {
        cout << "Error: could not open file" << endl;
    }

    //while there is a next line
    while (getline(inFS, line)) {

        stringstream ss(line);
        //seperate the line into tokens
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        //formating check
        if (tokens.size() < 2) {
            cout << "Error: Invalid format missing course number and/or title" << endl;
        }

        //sets course variables 
        courseId = tokens[0];
        name = tokens[1];

        //adds preRec courses to preRec list
        for (int i = 2; i < tokens.size(); i++) {
            //compares preRecs to existing courses must have a match to continue
            Course tempCourse = bst->Search(tokens[i]);
            if (tempCourse.courseId.empty()) {
                cout << "Error: invalid preRec format" << endl;
                courseId.clear();
                name.clear();
                preRecs.clear();
            }
            else {
                preRecs.push_back(tokens[i]);
            }
        }

        //if course variables are not empty create course object and add to bst
        if (!courseId.empty() && !name.empty()) {
            Course aCourse;
            aCourse.courseId = courseId;
            aCourse.name = name;
            for (int i = 0; i < preRecs.size(); ++i) {
                aCourse.preRecs.push_back(preRecs[i]);
            }
            bst->Insert(aCourse);
        }
        tokens.clear();
        
    }
    inFS.close();
    if (!inFS.is_open()) {
        cout << "Closing file" << endl;
    }
}

//Function to display the menu for the menuLoop()
void displayMenu() {
    cout << "Welcome to the course planner." << endl;
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << endl;
    cout << "What would you like to do?" << endl;
}

//Function to display the menu on a loop getting input and calling the correct functions
void menuLoop(Course course, BinarySearchTree* bst) {
    int input = 0;
    string file;
    string courseId;

    while (input != 9) {
        displayMenu();
        cout << "Enter input: ";
        cin >> input;
        switch (input) {
            case(1):
                //FIXME add load data structure code
                cout << "What is the file name?" << endl;
                cin >> file;
                cout << endl;
                cout << "Loading Data structure" << endl;
                populateBST(file, bst);
                break;
            case(2):
                //FIXME add print course list code
                cout << "Printing course list" << endl;
                bst->InOrder();
                break;
            case(3):
                //FIXME add print course code
                cout << "What course ID are you looking for? Enter in uppercase:" << endl;
                cin >> courseId;
                cout << endl;
                course = bst->Search(courseId);

                if (!course.courseId.empty()) {
                    cout << course.courseId << ", " << course.name << ", " << endl;
                    if (!course.preRecs.empty()) {
                        cout << "Prerequisites: ";
                        cout << course.preRecs[0];
                        for (int i = 1; i < course.preRecs.size(); ++i) {
                            cout << ", " << course.preRecs[i];
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
                else {
                    cout << "Course " << courseId << " was not found" << endl;
                }
                break;
            default:
                cout << input << " is not a valid input" << endl;
        }
    }
}


int main()
{
    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    menuLoop(course, bst);
}
