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
    
    TTreeNode* Nil;
public:
    TTreeNode* Root;
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
    void Transplant(TTreeNode* u, TTreeNode* v) {
        if (u->Parent == Nil) {
            Root = v;
        }
        else if( u == u->Parent->Left) {
            u->Parent->Left = v;
        }
        else {
            u->Parent->Right = v;
        }
        v->Parent = u->Parent;
    }
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
    void Delete(int value) {
        TTreeNode* z = Find(value);
        if(z == Nil) {
            return;
        }
        TTreeNode* y = z;
        TTreeNode* x = Nil;
        int yOriginalColor = y->NodeColor;
        if(z->Left == Nil) {
            x = z->Right;
            Transplant(z, z->Right);
        }
        else if(z->Right == Nil) {
            x = z->Left;
            Transplant(z, z->Left);
        }
        else {
            y = Minimum(z->Right);
            yOriginalColor = y->NodeColor;
            x = y->Right;
            if(y->Parent == z) {
                x->Parent = y;
            }
            else {
                Transplant(y, y->Right);
                y->Right = z->Right;
                y->Right->Parent = y;
            }
            Transplant(z, y);
            y->Left = z->Left;
            y->Left->Parent = y;
            y->NodeColor = z->NodeColor;
        }
        if(yOriginalColor == BLACK) {
            DeleteFixUp(x);
        }
    }
    void DeleteFixUp(TTreeNode* x) {
        while (x != Root && x->NodeColor == BLACK) {
            if(x == x->Parent->Left) {
                TTreeNode* w = x->Parent->Right;
                if (w->NodeColor == RED) {
                    w->NodeColor = BLACK;
                    x->Parent->NodeColor = RED;
                    LeftRotate(x->Parent);
                    w = x->Parent->Right;
                }
                if (w->Left->NodeColor == BLACK && w->Right->NodeColor == BLACK) {
                    w->NodeColor = RED;
                    x = x->Parent;
                }
                else if (w->Right->NodeColor == BLACK) {
                    w->Left->NodeColor = BLACK;
                    w->NodeColor = RED;
                    RightRotate(w);
                    w = x->Parent->Right;
                }
                else {
                    w->NodeColor = x->Parent->NodeColor;
                    x->Parent->NodeColor = BLACK;
                    w->Right->NodeColor = BLACK;
                    LeftRotate(x->Parent);
                    x = Root;
                }
            }
            else {
                TTreeNode* w = x->Parent->Left;
                if (w->NodeColor == RED) {
                    w->NodeColor = BLACK;
                    x->Parent->NodeColor = RED;
                    RightRotate(x->Parent);
                    w = x->Parent->Left;
                }
                if (w->Right->NodeColor == BLACK && w->Left->NodeColor == BLACK) {
                    w->NodeColor = RED;
                    x = x->Parent;
                }
                else if (w->Left->NodeColor == BLACK) {
                    w->Right->NodeColor = BLACK;
                    w->NodeColor = RED;
                    LeftRotate(w);
                    w = x->Parent->Left;
                }
                else {
                    w->NodeColor = x->Parent->NodeColor;
                    x->Parent->NodeColor = BLACK;
                    w->Left->NodeColor = BLACK;
                    RightRotate(x->Parent);
                    x = Root;
                }
            }
        }
        x->NodeColor = BLACK;
    }
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

