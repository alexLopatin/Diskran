#include "lab2.h"
using namespace std;
void TTree::Insert(TKeyValuePair value) {

    if(Root == Nil) {
        Root = new TTreeNode(value, Nil, BLACK, Nil);
        return;
    }
    TTreeNode* z = Root;
    TTreeNode* y = Nil;
    while(z != Nil) {
        y = z;
        int cmp = strcmp(value.Key, z->Value.Key);
        if(cmp < 0) {
            z = z->Left;
        }
        else {
            z = z->Right;
        }
    }
    int cmp = strcmp(value.Key, y->Value.Key);
    if(cmp < 0) {
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
void TTree::Delete(TKeyValuePair value) {
        TTreeNode* z = Find(value);
        if(z == 0) {
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
        delete z;
        if(yOriginalColor == BLACK) {
            DeleteFixUp(x);
        }
    }
void TTree::DeleteFixUp(TTreeNode* x) {
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
void TTree::Transplant(TTreeNode* u, TTreeNode* v) {
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

int main(int argc, char *argv[]) {
    TTree* RBtree = new TTree();
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    ofstream outDictionary;
    ifstream inDictionary;
    while (!inFile.eof()) {
        char command[256];
        TKeyValuePair pair;
        inFile >> command;
        switch(command[0]){
            case '+':
                inFile >> pair.Key;
                inFile >> pair.Value;
                if(RBtree->Find(pair) == 0 ){
                    RBtree->Insert(pair);
                    outFile << "OK" << endl;
                }
                else {
                    outFile << "Exist" << endl;
                }
                break;
            case '-':
                inFile >> pair.Key;
                if(RBtree->Find(pair) != 0 ){
                    RBtree->Delete(pair);
                    outFile << "OK" << endl;
                }
                else {
                    outFile << "NoSuchWord" << endl;
                }
                break;
            case '!':
                char commFile[4];

                inFile >> commFile;
                if(strcmp(commFile, "Save") == 0) {
                    char path[256];
                    inFile >> path;
                    outDictionary.open(path);
                    outDictionary << *RBtree;
                    outDictionary.close();
                    outFile << "OK" << endl;
                }
                else if (strcmp(commFile, "Load") == 0) {
                    char path[256];
                    inFile >> path;
                    inDictionary.open(path);
                    RBtree = new TTree();
                    inDictionary >> *RBtree;
                    inDictionary.close();
                    outFile << "OK" << endl;
                }
                break;

            default:
                strcpy(pair.Key, command);
                auto node = RBtree->Find(pair);
                if(node != 0 ){
                    outFile << "OK: " << node->Value.Value << endl;
                }
                else {
                    outFile << "NoSuchWord" << endl;
                }
                break;
        }
    }
    inFile.close();
    outFile.close();
    delete RBtree;
}