#include "bstree.h"

template < class DT, class KF >
BSTreeNode<DT, KF>::BSTreeNode(const DT& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
    dataItem = nodeDataItem;
    left = leftPtr;
    right = rightPtr;
}

template < class DT, class KF >
BSTree<DT, KF>::BSTree()
{
    root = nullptr;
}

template < class DT, class KF >
BSTree<DT, KF>::~BSTree()
{
    clear();
}

//--------------------------------------------------------------------

// Insert

template < class DT, class KF >
void BSTree<DT, KF>::insert(const DT& newDataItem)
{
    insertSub(root, newDataItem);
}

template < class DT, class KF >
void BSTree<DT, KF>::insertSub(BSTreeNode<DT, KF>*& p, const DT& newDataItem)
{
    if (p == nullptr)
    {
        p = new BSTreeNode<DT, KF>(newDataItem, nullptr, nullptr);
    }
    else if (isFull())
    {
        cout << "Error : Full Tree" << endl;
    }
    else
    {
        if (p->dataItem.getKey() == newDataItem.getKey()) 
        {
            cout << "Error : Already Inserted Element" << endl;
        }
        else if (p->dataItem.getKey() > newDataItem.getKey())
        {
            insertSub(p->left, newDataItem);
        }
        else if (p->dataItem.getKey() < newDataItem.getKey())
        {
            insertSub(p->right, newDataItem);
        }
    }
}

//--------------------------------------------------------------------

// Retrieve

template < class DT, class KF >
bool BSTree<DT, KF>::retrieve(KF searchKey, DT& searchDataItem) const
{
    return retrieveSub(root, searchKey, searchDataItem);
}

template < class DT, class KF >
bool BSTree<DT, KF>::retrieveSub(BSTreeNode<DT, KF>* p, KF searchKey, DT& searchDataItem) const
{
    if (p == nullptr)
        return false;
    else if (p->dataItem.getKey() < searchKey)
        return retrieveSub(p->right,searchKey,searchDataItem);
    else if (p->dataItem.getKey() > searchKey)
        return retrieveSub(p->left, searchKey, searchDataItem);
    else if (p->dataItem.getKey() == searchKey)
    {
        searchDataItem = p->dataItem;
        return true;
    }
}

//--------------------------------------------------------------------

// Remove

template < class DT, class KF >
bool BSTree<DT, KF>::remove(KF deleteKey)
{
    return removeSub(root,deleteKey);
}

template < class DT, class KF >
bool BSTree<DT, KF>::removeSub(BSTreeNode<DT, KF>*& p, KF deleteKey)
{
    if (p == nullptr)
    {
        return false;
    }
    else if (p->dataItem.getKey() < deleteKey)
    {
        return removeSub(p->right, deleteKey);
    }
    else if (p->dataItem.getKey() > deleteKey)
    {
        return removeSub(p->left, deleteKey);
    }
    else if (p->dataItem.getKey() == deleteKey)
    {
        BSTreeNode<DT, KF>* temp = p;
        if (p->left == nullptr && p->right == nullptr)
        {
            p = nullptr;
            delete temp;
        }
        else if (p->left == nullptr && p->right != nullptr)
        {
            p = p->right;
            delete temp;
        }
        else if (p->left != nullptr && p->right == nullptr)
        {
            p = p->left;
            delete temp;
        }
        else
        {
            BSTreeNode<DT, KF>* replacePtr;
            temp = p->left;
            cutRightmost(temp, replacePtr);
            p->dataItem.setKey(replacePtr->dataItem.getKey());
            removeSub(p->left, replacePtr->dataItem.getKey());
        }
        return true;
    }
    else
        return false;
}

template < class DT, class KF >
void BSTree<DT, KF>::cutRightmost(BSTreeNode<DT, KF>*& r, BSTreeNode<DT, KF>*& delPtr)
{
    if (r == nullptr) {
        delPtr = nullptr;
    }
    while (r->right != nullptr) 
    {
        r = r->right;
    }
    delPtr = r;
}

//--------------------------------------------------------------------

// Write Keys

template < class DT, class KF >
void BSTree<DT, KF>::writeKeys() const
{
    writeKeysSub(root);
}

template < class DT, class KF >
void BSTree<DT, KF>::writeKeysSub(BSTreeNode<DT, KF>* p) const
{
    if (p != nullptr)
    {
        writeKeysSub(p->left);
        cout << p->dataItem.getKey() << " ";
        writeKeysSub(p->right);
    }
}

//--------------------------------------------------------------------

// Clear

template < class DT, class KF >
void BSTree<DT, KF>::clear()
{
    if (root == nullptr)
        cout << "Error : Already Empty" << endl;
    else
    {
        clearSub(root);
        root = nullptr;
    }
}

template < class DT, class KF >
void BSTree<DT, KF>::clearSub(BSTreeNode<DT, KF>* p)
{
    BSTreeNode <DT, KF>* temp;
    if (p != nullptr)
    {
        temp = p;
        clearSub(p->right);
        clearSub(p->left);
        delete temp;
    }
}

//--------------------------------------------------------------------

// Empty / Full

template < class DT, class KF >
bool BSTree<DT, KF>::isEmpty() const
{
    if (root == nullptr)
        return true;
    else
        return false;
}

template < class DT, class KF >
bool BSTree<DT, KF>::isFull() const
{
    BSTreeNode<DT, KF>* temp = new(nothrow)BSTreeNode<DT, KF> (DT(), nullptr, nullptr);
    if (temp == nullptr)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

// Show Structure

template < class DT, class KF >
void BSTree<DT, KF>::showStructure() const
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

template < class DT, class KF >
void BSTree<DT, KF>::showSub(BSTreeNode<DT, KF>* p, int level) const
{
    int j;   // Loop counter

    if (p != 0)
    {
        showSub(p->right, level + 1);         // Output right subtree
        for (j = 0; j < level; j++)    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();  // Output key
        if ((p->left != 0) &&           // Output "connector"
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        cout << endl;
        showSub(p->left, level + 1);          // Output left subtree
    }
}

//--------------------------------------------------------------------

// In-lab 2
template < class DT, class KF >
int BSTree<DT, KF>::getHeight() const
{
    return getHeightSub(root);
}

template < class DT, class KF >
int BSTree<DT, KF>::getHeightSub(BSTreeNode<DT, KF>* p) const
{

    if(p == nullptr)
        return 0;
    else
        return max(getHeightSub(p->left), getHeightSub(p->right)) + 1;
}

//--------------------------------------------------------------------
//
// In-lab 3
template < class DT, class KF >
void BSTree<DT, KF>::writeLessThan(KF searchKey) const
{
    writeLTSub(root, searchKey);
}

template < class DT, class KF >
void BSTree<DT, KF>::writeLTSub(BSTreeNode <DT, KF>* p, const KF searchKey) const
{
    if (p != nullptr)
    {
        if (p->dataItem.getKey() >= searchKey)
            writeLTSub(p->left, searchKey);
        else if (p->dataItem.getKey() < searchKey)
        {
            writeLTSub(p->left, searchKey);
            cout << p->dataItem.getKey() << " ";
            writeLTSub(p->right, searchKey);
        }
    }
}