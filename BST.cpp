#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class node
{
public:
    int data;
    node *left;
    node *right;
    node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};
bool search(node* root,int val)
{
    if(root==NULL)
    return false;
    if(val>root->data)
    {
       return search(root->right,val);
    }
    if(val<root->data)
    {
       return search(root->left,val);
    }
    if(val==root->data)
    return true;
    
}
node *insert(node *root, int val)
{
    if (root == NULL)
    {
        return new node(val);
    }
    if (val < root->data)
    {
        root->left = insert(root->left, val);
    }
    else
    {
        root->right = insert(root->right, val);
    }
    return root;
}
void takeInput(node *&root)
{
    int data;
    cin >> data;
    while (data != -1)
    {
        root = insert(root, data);
        cin >> data;
    }
}

void lotrav(node *root)
{
    if (root == NULL)
        return;

    queue<node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        node *temp = q.front();
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
node* deleteFromBST(node* root,int val)
{
    if(root==NULL)
        return root;
    if(root->data==val)
    {
        //0 child
        if(root->left==NULL && root->right==NULL)
        {
            delete root;
            return NULL;
        }
        //1 child
        
        //left child
        if(root->left!=NULL && root->right==NULL)
        {
            node *temp=root->left;
            delete root;
            return temp;
        }
        //right child
        if(root->left==NULL && root->right!=NULL)
        {
            node *temp=root->right;
            delete root;
            return temp;
        }
        //2 child
        if(root->left!=NULL && root->right!=NULL)
        {
            node* temp=min_value(root->right);
            int mini=temp->data;
            root->data=mini; 
            root->right=deleteFromBST(root->right,mini); 
            return root;
        }
    }
    else if(val<root->data)
    {
        root->left=deleteFromBST(root-> left,val);
        return root;
    }
    else
    {
        root->right=deleteFromBST(root->right,val);   
        return root;    
    }
}
node* max_value(node* root)
{
    if(root==NULL)
    {
        cout<<"BST is empty"<<endl;
        return NULL;
    }
    if(root->right!=NULL)
    {
        return max_value(root->right);
    }
    else
        return root;
}
node* min_value(node* root)
{
    if(root==NULL)
    {
        cout<<"BST is empty"<<endl;
        return NULL;
    }
    if(root->left!=NULL)
    {
        return min_value(root->left);
    }
    else
        return root;
}
int main()
{
    int val;
    node *root = NULL;
    cout << "Enter data to input into BST: " << endl;
    takeInput(root);
    lotrav(root);
    cout << "Enter value to search: " << endl;
    cin>>val;
    cout<<search(root,val);
    return 0;
}