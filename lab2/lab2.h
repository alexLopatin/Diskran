#include <iostream>
using namespace std;



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
        ~TTreeNode();
    };
    TTreeNode* Root;
    TTreeNode* Nil;
public:
    
    TTree() {
        Nil = new TTreeNode(0,0, BLACK);
        Root = Nil;       
        Nil->Parent = Nil;
    }
    void Printf() {
        Print(Root);
    }
    void Insert(int value);
    void FixUp(TTreeNode* z);
    void LeftRotate(TTreeNode* x);
    void RightRotate(TTreeNode* x);
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

