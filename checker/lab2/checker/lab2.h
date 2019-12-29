#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct TKeyValuePair {
    char Key[257];
    unsigned long long Value;
    TKeyValuePair(){
        memset(Key,255,256);
        Value = 0;
    }
};

class TTree {
    enum TNodeColor { BLACK, RED};
    struct TTreeNode
    {
        TTreeNode* Left;
        TTreeNode* Right;
        TTreeNode* Parent;
        TNodeColor NodeColor;
        TKeyValuePair Value;
        TTreeNode(TKeyValuePair v, TTreeNode* p, TNodeColor nodeColor, TTreeNode* nil = 0) {
            Parent = p;
            Value = v;
            Left = nil;
            Right = nil;
            NodeColor = nodeColor;
        }
        ~TTreeNode() {
        }
    };
    
    TTreeNode* Nil = 0;
public:
    TTreeNode* Root = 0;
    void Write(std::ostream &out, TTreeNode* z) const {
        out << z->Value.Key << ' ' << z->Value.Value << endl;
        if(z->Left != Nil) {
            Write(out, z->Left);
        }
        if(z->Right != Nil) {
            Write(out, z->Right);
        }
    }

    friend std::ostream & operator << (std::ostream &out, const TTree & obj)
    {
        obj.Write(out, obj.Root);
        return out;
    }
    friend std::istream& operator >> (std::istream& in, TTree& obj) {
        TKeyValuePair pair;
        while(in >> pair.Key >> pair.Value) {
            obj.Insert(pair);
        }
        return in;
    }

    TTree() {
        Nil = new TTreeNode(TKeyValuePair(),0, BLACK);
        Root = Nil;
        Root->Left = Nil;
        Root->Right = Nil;      
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
    void Insert(TKeyValuePair value);
    void FixUp(TTreeNode* z);
    void LeftRotate(TTreeNode* x);
    void RightRotate(TTreeNode* x);
    void Transplant(TTreeNode* u, TTreeNode* v);
    TTreeNode* Find(TKeyValuePair value) {
        TTreeNode* z = Root;

        while(z != Nil) {
            
            int cmp = strcasecmp(value.Key, z->Value.Key);
            if(cmp == 0) {
                return z;
            }
            if(cmp < 0) {
                z = z->Left;
            }
            else {
                z = z->Right;
            }
        }
        return 0;
    }
    TTreeNode* Minimum(TTreeNode* z) {
        TTreeNode* y = z->Parent;
        while(z != Nil) {
            y = z;
            z = z->Left;
        }
        return y;
    }
    void Delete(TKeyValuePair value);
    void DeleteFixUp(TTreeNode* x);
    
    void Printf() {
        Print(Root);
    }
    void Print(TTreeNode* node, int i = 0) {
        if(node != Nil) {
            Print(node->Right, i + 4);
            for (int j = 0; j < i; j++) {
                cout << " ";
            }
            cout << node->Value.Key << ":" << node->Value.Value << endl;
            Print(node->Left, i + 4);
        }
    }
    /*
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
    */
};