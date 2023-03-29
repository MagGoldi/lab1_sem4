#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>

#include<vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class Tree {
private:
    Node* root;

    void Copy(const Node* const old, Node* nevv) {
        if (!old) {
            nevv = NULL;
            return;
        }
        nevv = new Node;
        nevv->data = old->data;
        Copy(old->left, nevv->left);
        Copy(old->right, nevv->right);
    }

    void Clear(Node*& Head) {
        if (!Head) return;
        else {
            Clear(Head->left);
            Clear(Head->right);
            delete Head;
        }
    }

    void Print_Node(const std::string& prefix, const Node* node, bool isLeft) {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "ÃÄÄ" : "ÀÄÄ");

            std::cout << node->data << std::endl;
            Print_Node(prefix + (isLeft ? "|   " : "    "), node->left, true);
            Print_Node(prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }

    bool Insert_Node(Node*& Head, int val)
    {
        if (!Head)
        {
            Head = new Node;
            Head->data = val;
            Head->left = Head->right = NULL;
            return true;
        }
        else if (val < Head->data)
            return Insert_Node(Head->left, val);
        else if (val > Head->data)
            return Insert_Node(Head->right, val);
        else
            return false;
    }

    bool Contains_Node(const Node* head, int val) {
        if (!head)
            return false;
        else if (val < head->data)
            return Contains_Node(head->left, val);
        else if (val > head->data)
            return Contains_Node(head->right, val);
        else
            return true;

    }

    Node* Erase_Node(Node* Head, int val) {
        if (!Head) return Head;
        else if (val < Head->data) Head->left = Erase_Node(Head->left, val);
        else if (val > Head->data) Head->right = Erase_Node(Head->right, val);
        else {
            if (!Head->left && !Head->right) {
                delete Head;
                Head = NULL;
            }
            else if (!Head->left) {
                Node* tmp = Head;
                Head = Head->right;
                delete tmp;
            }
            else if (!Head->right) {
                Node* tmp = Head;
                Head = Head->left;
                delete tmp;
            }
            else {
                Node* tmp = Minimum(Head->right);
                Head->data = tmp->data;
                Head->right = Erase_Node(Head->right, tmp->data);
            }
        }
        return Head;
    }

    Node* Minimum(Node* Head)
    {
        while (Head->left) Head = Head->left;
        return Head;
    }

public:
    Tree();
    Tree(const Tree&);
    ~Tree();
    bool Insert(int);
    bool Contains(int x);
    bool Erase(int x);
    void Print();
    Tree& operator=(const Tree& src);
};

Tree::Tree() {
    root = NULL;
}

Tree::Tree(const Tree& old)
{
    Copy(old.root, root);
}

Tree::~Tree()
{
    Clear(root);
}

Tree& Tree::operator=(const Tree& tmp)
{
    if (this == &tmp) return *this;
    Clear(root);
    Copy(root, tmp.root); //!!!!root 
    return *this;
}

void Tree::Print()
{
    Print_Node("", root, false);
    cout << endl;
}

bool Tree::Insert(int x)
{
    return Insert_Node(root, x);
}

bool Tree::Contains(int x)
{
    return Contains_Node(root, x);
}

bool Tree::Erase(int x) {
    if (!Contains(x)) return false;
    root = Erase_Node(root, x);
    return true;
}

bool find_value(std::vector<int>& vector, int value) {
    for (int i = 0; i < vector.size(); i++)
    {
        if (vector[i] == value)
            return true;
    }
    return false;
}

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}
void fill_tree(int n, int cycles)
{
    double result = 0;
    for (int i = 0; i < cycles; i++)
    {
        Tree test_time;
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < n; j++)
        {
            test_time.Insert(lcg());
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        result += duration.count();
    }
    cout << "filling of binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " microseconds" << endl;
}

void contains_tree(int n, int cycles)
{
    Tree test_time;
    for (int i = 0; i < n; i++)
    {
        test_time.Insert(lcg());
    }
    long double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        test_time.Contains(lcg());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "searching in binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void insert_tree(int n, int cycles)
{
    Tree test_time;
    for (int i = 0; i < n; i++)
    {
        test_time.Insert(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        Tree tmp = test_time;
        auto start = std::chrono::high_resolution_clock::now();
        tmp.Insert(lcg());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "addition in binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}
void erase_tree(int n, int cycles)
{
    Tree test_time;
    for (int i = 0; i < n; i++)
    {
        test_time.Insert(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        Tree tmp = test_time;
        auto start = std::chrono::high_resolution_clock::now();
        tmp.Erase(lcg());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "deleting in binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}
void fill_vector(int n, int cycles)
{
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        std::vector<int> test_time(n);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            test_time.push_back(lcg());
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        result += duration.count();
    }
    cout << "filling of vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " microseconds" << endl;
}

void contains_vector(int n, int cycles)
{
    std::vector<int> test_time(n);
    for (int i = 0; i < n; i++)
    {
        test_time.push_back(lcg());
    }
    long double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::find(test_time.begin(), test_time.end(), lcg());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "searching in vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void insert_vector(int n, int cycles)
{
    std::vector<int> test_time(n);
    for (int i = 0; i < n; i++)
    {
        test_time.push_back(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        std::vector<int> tmp = test_time;
        auto start = std::chrono::high_resolution_clock::now();
        tmp.push_back(lcg());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "addition in vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void erase_vector(int n, int cycles)
{
    std::vector<int> test_time(n);
    for (int i = 0; i < n; i++)
    {
        test_time.push_back(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        std::vector<int> tmp = test_time;
        auto start = std::chrono::high_resolution_clock::now();
        tmp.erase(std::remove(tmp.begin(), tmp.end(), lcg()), tmp.end());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "deleting in vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void main_menu()
{
    system("cls");
    cout << "1) Create a binary search Tree" << endl;
    cout << "2) Calculate the average time" << endl;
    cout << "3) Individual task" << endl;
    cout << "4) Finish the program" << endl;
    cout << "Answer: ";
}

void menu_2() {
    system("cls");
    cout << "1) Add a Node" << endl;
    cout << "2) Delete a Node" << endl;
    cout << "3) Print a binary tree" << endl;
    cout << "4) Find the Node" << endl;
    cout << "5) Back" << endl;
    cout << "Answer: ";
}

int main() {
    Tree test;
    Tree task;
    int answer_main = 0;
    int answer_1 = 0;
    int value = 0;

    bool f1 = true;

    while (f1) {
        main_menu();
        cin >> answer_main;

        if (answer_main == 1) {

            bool f2 = true;

            while (f2) {
                menu_2();
                cin >> answer_1;

                if (answer_1 == 1) {
                    cout << "Input value:" << endl;
                    cin >> value;
                    if (test.Insert(value) == true) cout << "Value add" << endl;
                    else cout << "The value is already in the tree" << endl;
                    system("pause");
                    f1 = true;
                }

                else if (answer_1 == 2) {
                    cout << "Value: ";
                    cin >> value;
                    if (test.Erase(value) == true) cout << "Value deleted" << endl;
                    else cout << "There is no such value in the tree" << endl;
                    system("pause");
                    f1 = true;
                }

                else if (answer_1 == 3) {
                    test.Print();
                    system("pause");
                    f1 = true;
                }

                else if (answer_1 == 4) {
                    cout << "Value: ";
                    cin >> value;
                    if (test.Contains(value)) cout << "This element is present in the tree" << endl;
                    else cout << "This element is NOT present in the tree" << endl;
                    system("pause");
                    f1 = true;

                }

                else if (answer_1 == 5) {
                    f2 = false;
                }

                else {
                    cout << "you clicked something wrong... try again" << endl;
                    system("pause");
                    f1 = true;
                }
            }
        }
        if (answer_main == 2) {

            fill_tree(1000, 100);
            fill_tree(10000, 100);
            fill_tree(100000, 100);
            cout << endl;
            fill_vector(1000, 100);
            fill_vector(10000, 100);
            fill_vector(100000, 100);
            cout << endl;
            cout << "end fill test" << endl;

            cout << endl;
            cout << endl;
            contains_tree(1000, 1000);
            contains_tree(10000, 1000);
            contains_tree(100000, 1000);
            cout << endl;
            contains_vector(1000, 1000);
            contains_vector(10000, 1000);
            contains_vector(100000, 1000);
            cout << endl;
            cout << endl;

            insert_tree(1000, 1000);
            insert_tree(10000, 1000);
            insert_tree(100000, 1000);
            cout << endl;
            insert_vector(1000, 1000);
            insert_vector(10000, 1000);
            insert_vector(100000, 1000);
            cout << endl;
            cout << endl;

            erase_tree(1000, 1000);
            erase_tree(10000, 1000);
            erase_tree(100000, 1000);
            cout << endl;
            erase_vector(1000, 1000);
            erase_vector(10000, 1000);
            erase_vector(100000, 1000);
            cout << endl << endl;

            system("pause");
            f1 = true;
        }
        if (answer_main == 3) {
            std::vector<int> old_vector = { 2, 3, 3, 4, 5, 6, 5, 7 };
            std::vector<int> new_vector;
            cout << "vector: [";
            for (int i = 0; i < old_vector.size(); i++)
            {
                if (find_value(new_vector, old_vector[i]) == false && task.Insert(old_vector[i]) == false)
                {
                    new_vector.push_back(old_vector[i]);
                }
                cout << old_vector[i] << ", ";
            }
            cout << "]" << endl;

            cout << "new vector: [";
            for (int i = 0; i < new_vector.size(); i++)
            {
                cout << new_vector[i] << ", ";
            }
            cout << "]" << endl;
            system("pause");
            f1 = true;
        }
        if (answer_main == 4) {
            return 0;
        }
        else if (answer_main != 1 && answer_main != 2 && answer_main != 3 && answer_main != 4) {
            cout << "you clicked something WWWrong... try again" << endl;
            system("pause");
        }
    }
}