#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};
Node *buildtree(Node *root)
{
    cout << "Enter the data : " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    if (data == -1)
        return NULL;
    cout << "Data to insert in the left of " << data << endl;
    root->left = buildtree(root->left);
    cout << "Data to insert in the right of " << data << endl;
    root->right = buildtree(root->right);
    return root;
}
void lotrav(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (temp == NULL)
        {
            cout << endl;
            if (!q.empty())
                q.push(NULL);
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
}
void rotrav(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    stack<Node *> s;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        s.push(temp);

        if (temp == NULL)
        {
            if (!q.empty())
                q.push(NULL);
        }
        else
        {
            if (temp->right)
                q.push(temp->right);
            if (temp->left)
                q.push(temp->left);
        }
    }
    while (!s.empty())
    {
        Node *temp = s.top();
        s.pop();

        if (temp == NULL)
        {
            cout << endl;
        }
        else
        {
            cout << temp->data << " ";
        }
    }
}
// In Order -> LNR
void inorder(Node *root)
{
    stack<Node *> s;
    Node *currentNode = root;

    // INITIALIZE THE STACK (push all left nodes)
    while (currentNode != NULL)
    {
        s.push(currentNode);
        currentNode = currentNode->left;
    }

    // ITERATE
    Node *poppedNode = NULL;

    while (!s.empty())
    {
        poppedNode = s.top();
        s.pop();

        cout << poppedNode->data << "\t"; // print node

        currentNode = poppedNode->right;

        // Push all left nodes of the right subtree
        while (currentNode != NULL)
        {
            s.push(currentNode);
            currentNode = currentNode->left;
        }
    }
}
// Pre Order -> NLR
void preorder(Node *root)
{
    stack<Node *> s;
    s.push(root);
    while (!s.empty())
    {
        Node *temp = s.top();
        int n = temp->data;
        s.pop();
        cout << n << "\t";
        if (temp->right)
        {
            s.push(temp->right);
        }
        if (temp->left)
        {
            s.push(temp->left);
        }
    }
}
// Post Order -> LRN
void postorder(Node *root)
{
    stack<Node *> s1;
    stack<Node *> s2;
    s1.push(root);
    while (!s1.empty())
    {
        Node *temp = s1.top();
        s1.pop();
        s2.push(temp);
        if (temp->left)
        {
            s1.push(temp->left);
        }
        if (temp->right)
        {
            s1.push(temp->right);
        }
    }
    while (!s2.empty())
    {
        cout << s2.top()->data << "\t";
        s2.pop();
    }
}
int main()
{
    Node *root = NULL;
    // 1 3 7 -1 -1 9 -1 -1 5 11 -1 -1 -1
    root = buildtree(root);
    cout << "Level order Traversal : " << endl;
    lotrav(root);
    cout << "Reverse order Traversal : " << endl;
    rotrav(root);
    cout << endl;
    cout << "In order traversal is : ";
    inorder(root);
    cout << endl;
    cout << "Pre order traversal is : ";
    preorder(root);
    cout << endl;
    cout << "Post order traversal is : ";
    postorder(root);
    cout << endl;
}