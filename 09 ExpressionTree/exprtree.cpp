//--------------------------------------------------------------------
//		Lab 12									exprtree.cpp
//
//--------------------------------------------------------------------

#include "exprtree.h"

//--------------------------------------------------------------------

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
    dataItem = elem;
    left = leftPtr;
    right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
{
    root = nullptr;
}

ExprTree::~ExprTree()
{
    clear();
}

//--------------------------------------------------------------------

void ExprTree::build()
{
    buildSub(root);
}

void ExprTree::buildSub(ExprTreeNode*& p)
{
    char prefix;
    cin >> prefix;

    if (prefix)
    {
        if (prefix == '+' || prefix == '-' || prefix == '*' || prefix == '/')
        {
            p = new ExprTreeNode(prefix, nullptr, nullptr);
            buildSub(p->left);
            buildSub(p->right);
        }
        else
            p = new ExprTreeNode(prefix, nullptr, nullptr);
    }
}

//--------------------------------------------------------------------

void ExprTree::expression() const
{
    exprSub(root);
}

void ExprTree::exprSub(ExprTreeNode* p) const
{
    if (p != nullptr)
    {
        if (p->left == nullptr && p->right == nullptr)
        {
            cout << p->dataItem;
        }
        else
        {
            cout << "(";
            exprSub(p->left);
            cout << p->dataItem;
            exprSub(p->right);
            cout << ")";
        }
    }
}

//--------------------------------------------------------------------

float ExprTree::evaluate() const
{
    return evaluateSub(root);
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{
     if (p->dataItem != '+' && p->dataItem != '-' && p->dataItem != '*' && p->dataItem != '/')
     {
         return (float)(p->dataItem - '0');
     }
     else
     {
         switch (p->dataItem)
         {
         case'+':
             return (float) evaluateSub(p->left) + evaluateSub(p->right);
             break;
         case'-':
             return (float) evaluateSub(p->left) - evaluateSub(p->right);
             break;
         case'*':
             return (float) evaluateSub(p->left) * evaluateSub(p->right);
             break;
         case'/':
             return (float) evaluateSub(p->left) / evaluateSub(p->right);
             break;
         default:
             cout << "Error : Invalid Command" << endl;
             break;
         }
     }
}

//--------------------------------------------------------------------

void ExprTree::clear()
{
    clearSub(root);
    root = nullptr;
}

void ExprTree::clearSub(ExprTreeNode* p)
{
    ExprTreeNode* temp;
    if (p != nullptr)
    {
        temp = p;
        clearSub(temp->left);
        clearSub(temp->right);
        delete temp;
    }
}

//--------------------------------------------------------------------

void ExprTree::showStructure() const
{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
    int j;

    if (p != 0)
    {
        showSub(p->right, level + 1);
        for (j = 0; j < level; j++)
            cout << "\t";
        cout << " " << p->dataItem;
        if ((p->left != 0) &&
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        cout << endl;
        showSub(p->left, level + 1);
    }
}

//--------------------------------------------------------------------
ExprTree::ExprTree(const ExprTree& valueTree)
{
    root = nullptr;
    copySub(root,valueTree.root);
}


void ExprTree::copySub(ExprTreeNode*& dest, ExprTreeNode* source)
{
    if (source)
    {
        dest = new ExprTreeNode(source->dataItem, nullptr, nullptr);
        if (source->left != nullptr)
            copySub(dest->left, source->left);

        if (source->right != nullptr)
            copySub(dest->right, source->right);
    }
}

//--------------------------------------------------------------------
void ExprTree::commute()
{
    commuteSub(root);
}


void ExprTree::commuteSub(ExprTreeNode*& p)
{
    if (p)
    {
        if (p->left != nullptr || p->right != nullptr)
        {
            ExprTreeNode* T = p->left;
            p->left = p->right;
            p->right = T;
        }

        commuteSub(p->left);
        commuteSub(p->right);
    }
}