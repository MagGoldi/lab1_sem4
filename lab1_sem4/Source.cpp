#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>

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

    void Print_Node(const std::string & prefix, const Node * node, bool isLeft) {
        if (node != nullptr){
            std::cout << prefix;
            std::cout << (isLeft ? "ГДД" : "АДД");

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

    bool Contains_Node(const Node * head, int val){
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

void main_menu()
{
    system("cls");
    cout<<"1) Create a binary search Tree"<<endl;
    cout<<"2) Calculate the average time"<<endl;
    cout<<"3) Individual task"<<endl;
    cout<<"4) Finish the program"<<endl;
    cout<<"Answer: ";
}

void menu_2() {
     system("cls");
     cout<<"1) Add a Node"<<endl;
     cout<<"2) Delete a Node"<<endl;
     cout<<"3) Print a binary tree"<<endl;
     cout<<"4) Find the Node"<<endl;
     cout<<"5) Back"<< endl;
     cout<<"Answer: ";
}

void menu_3() {

}

int main() {
    Tree test;
    int answer_main = 0;
    int answer_1 = 0;
    int value = 0;


    while (true) {
        main_menu();
        cin >> answer_main;

        if (answer_main == 1) {
            while (true) {
                menu_2();
                cin >> answer_1;
                if (answer_1 == 1) {
                    cout << "Input value:" << endl;
                    cin << value;


                }
                else if (answer_1 == 2) {

                }
                else if (answer_1 == 3) {

                }
                else if (answer_1 == 4) {

                }
                else if (answer_1 == 5) {

                }
                else{
                    //не ломай
                }
            }
        }
        if (answer_main == 2) {

        }
        if (answer_main == 3) {

        }
        if (answer_main == 4) {
            return 0;
        }
        //добавить что бы не ломалось все
        

    }

}