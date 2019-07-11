#include <iostream>
using namespace std;

struct TKeyValuePair {
    char Key[256];
    unsigned long long Value;
};

class TTree {
    enum TNodeColor { BLACK, RED};
    struct TTreeNode
    {
        TTreeNode* Left;
        TTreeNode* Right;
        TTreeNode* Parent;
        TNodeColor NodeColor;
        int Value;
        TTreeNode(int v, TTreeNode* p, TNodeColor nodeColor, TTreeNode* nil = 0) {
            Parent = p;
            Value = v;
            Left = nil;
            Right = nil;
            NodeColor = nodeColor;
        }
        ~TTreeNode() {
        }
    };
    
    TTreeNode* Nil;
    TTreeNode* Root;
public:
    TTree() {
        Nil = new TTreeNode(0,0, BLACK);
        Root = Nil;       
        Nil->Parent = Nil;
    }
    ~TTree() {
        DeleteMem(Root);
        delete Nil;
    }
    void DeleteMem(TTreeNode* z) {
        if(z->Left != Nil) {
            DeleteMem( z->Left);
        }
        if(z->Right != Nil) {
            DeleteMem( z->Right);
        }
        delete z;
    }
    void Printf() {
        Print(Root);
    }
    void Insert(int value);
    void FixUp(TTreeNode* z);
    void LeftRotate(TTreeNode* x);
    void RightRotate(TTreeNode* x);
    void Transplant(TTreeNode* u, TTreeNode* v);
    TTreeNode* Find( int value) {
        TTreeNode* z = Root;
        while(z != Nil) {
            if(value == z->Value) {
                return z;
            }
            if(value<z->Value) {
                z = z->Left;
            }
            else {
                z = z->Right;
            }
        }
        return Nil;
    }
    TTreeNode* Minimum(TTreeNode* z) {
        TTreeNode* y = z->Parent;
        while(z != Nil) {
            y = z;
            z = z->Left;
        }
        return y;
    }
    void Delete(int value);
    void DeleteFixUp(TTreeNode* x);
    void Print(TTreeNode* node, int i = 0) {
        if(node != Nil) {
            Print(node->Right, i + 4);
            for (int j = 0; j < i; j++) {
                cout << " ";
            }
            cout << node->Value << ":" << node->NodeColor << endl;
            Print(node->Left, i + 4);
        }
    }

    bool Check() {
        return CheckHeight();
    }
    bool Checkf(TTreeNode* z) {
        bool res = (z->Parent->NodeColor == RED)&&(z->NodeColor == RED);
        if(z != Nil) {
            res = res || Checkf(z->Left) || Checkf(z->Right);
        }
        return  res;
    }
    bool CheckHeight() {
        TTreeNode* z = Root;
        int blackHeight = 0;
        while(z != Nil) {
            if(z->NodeColor == BLACK) {
                blackHeight++;
            }
            z = z->Left;
        }
        return CheckHeightf(Root,0, blackHeight);

    }
    bool CheckHeightf(TTreeNode* z, int currentHeight, int blackHeight) {
        if(z == Nil) {
            return currentHeight == blackHeight;
        }
        if(z->NodeColor == BLACK) {
            currentHeight++;
        }
        return CheckHeightf(z->Left, currentHeight, blackHeight) && CheckHeightf(z->Left, currentHeight, blackHeight);
    }
};