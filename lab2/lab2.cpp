#include "lab2.h"
using namespace std;
void TTree::Insert(int value) {
    if(Root == Nil) {
        Root = new TTreeNode(value, Nil, BLACK, Nil);
        return;
    }
    TTreeNode* z = Root;
    TTreeNode* y = Nil;
    while(z != Nil) {
        y = z;
        if(value<z->Value) {
            z = z->Left;
        }
        else {
            z = z->Right;
        }
    }
    if(value < y->Value) {
        y->Left =  new TTreeNode(value, y, RED, Nil);
        FixUp(y->Left);
    }
    else {
        y->Right =  new TTreeNode(value, y, RED, Nil);
        FixUp(y->Right);
    }
}
void TTree::FixUp(TTreeNode* z) {
    while((z != Root) && z->Parent->NodeColor == RED) {
        if(z->Parent == z->Parent->Parent->Left) {         
            TTreeNode* y = z->Parent->Parent->Right;
            if(y->NodeColor == RED) {
                z->Parent->NodeColor = BLACK;
                y->NodeColor = BLACK;
                z->Parent->Parent->NodeColor = RED;
                z = z->Parent->Parent;
            }
            else if (z == z->Parent->Right) {
                z = z->Parent;
                LeftRotate(z);
            }
            else {
                z->Parent->NodeColor = BLACK;
                z->Parent->Parent->NodeColor = RED;
                RightRotate(z->Parent->Parent);
            }
        }
        else {
            TTreeNode* y = z->Parent->Parent->Left;
            if( y->NodeColor == RED) {
                z->Parent->NodeColor = BLACK;
                y->NodeColor = BLACK;
                z->Parent->Parent->NodeColor = RED;
                z = z->Parent->Parent;
            }
            else if (z == z->Parent->Left) {
                z = z->Parent;
                RightRotate(z);
            }
            else {
                z->Parent->NodeColor = BLACK;
                z->Parent->Parent->NodeColor = RED;
                LeftRotate(z->Parent->Parent);
            }
        }
    }
    Nil->NodeColor = BLACK;
    Root->NodeColor = BLACK;
}
void TTree::LeftRotate(TTreeNode* x) {
    if( x == Nil ) {
        return;
    }
    TTreeNode* y = x->Right;
    x->Right = y->Left;
    if( y->Left != Nil) {
        y->Left->Parent = x;
    }
    y->Parent = x->Parent;
    if(x->Parent == Nil) {
        Root = y;
    }
    else if(x == x->Parent->Left) {
        x->Parent->Left = y;
    }
    else {
        x->Parent->Right = y;
    }
    y->Left = x;
    x->Parent = y;
}
void TTree::RightRotate(TTreeNode* x) {
    if( x == Nil ) {
        return;
    }
    TTreeNode* y = x->Left;
    x->Left = y->Right;
    if( y->Right != Nil) {
        y->Right->Parent = x;
    }
    y->Parent = x->Parent;
    if(x->Parent == Nil) {
        Root = y;
    }
    else if(x == x->Parent->Right) {
        x->Parent->Right = y;
    }
    else {
        x->Parent->Left = y;
    }
    y->Right = x;
    x->Parent = y;
}
int main(int argc, char *argv[]) {
    TTree* RBtree = new TTree();
    RBtree->Insert(1);
    RBtree->Insert(2);
    RBtree->Insert(3);
    RBtree->Insert(4);
    RBtree->Insert(5);
    RBtree->Insert(6);
    RBtree->Insert(7);
    RBtree->Insert(8);
    RBtree->Insert(0);
    RBtree->Printf();
    RBtree->Delete(6);
    RBtree->Printf();
    //cout << RBtree->Minimum(RBtree->Root)->Value << endl;
    delete RBtree;
}