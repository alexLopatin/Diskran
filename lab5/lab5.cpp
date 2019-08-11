#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <map>
using namespace std;


int pos = -1;

class TNode {
	int Right;					// [Left; Right)
public:
	int Left;
	int GetRight() {
		return ((Right == -1) ? (pos + 1) : Right);
	}
	map<char, TNode*> Edges;
	TNode* SuffLink;
	TNode(int left, int right) : Left(left), Right(right) {
		SuffLink = 0;
	}
	int EdgeLength() {
		return GetRight() - Left;
	}
};

string s;
TNode* head;

TNode* activeNode = head;
int activeLength = 0;
int remainderT = 0;
int activeEdgePos = 0;

char ActiveEdge() {
	return s[activeEdgePos];
}

TNode* lastInnerVertex = 0;

void AddSuffixLink(TNode* suffNode) {
	if (lastInnerVertex != 0) {
		lastInnerVertex->SuffLink = suffNode;
	}
	lastInnerVertex = suffNode;
}

void Extend(char c) {
	pos++;
	remainderT++;
	lastInnerVertex = 0;
	while (remainderT > 0) {
		if (activeLength == 0) {
			activeEdgePos = pos;
		}
		if (activeNode->Edges[ActiveEdge()] == 0) {
			TNode* leaf = new TNode(pos, -1);
			activeNode->Edges[ActiveEdge()] = leaf;
			AddSuffixLink(activeNode);
		}
		else {
			TNode* next = activeNode->Edges[ActiveEdge()];
			if (activeLength >= next->EdgeLength() ) {
				activeLength -= next->EdgeLength();
				activeEdgePos += next->EdgeLength();
				activeNode = next;
				continue;
			}
			if (s[next->Left + activeLength] == c) {
				activeLength++;
				AddSuffixLink(activeNode);
				break;
			}
			TNode* split = new TNode(next->Left, next->Left + activeLength);
			activeNode->Edges[ActiveEdge()] = split;
			TNode* leaf = new TNode(pos, -1);
			split->Edges[c] = leaf;
			next->Left += activeLength;
			split->Edges[s[next->Left]] = next;
			AddSuffixLink(split);
		}
		remainderT--;
		if (activeNode == head && activeLength > 0) { //rule 1
			activeLength--;
			activeEdgePos = pos - remainderT + 1;
		}
		else {
			activeNode = activeNode->SuffLink > 0 ? activeNode->SuffLink : head; //rule 3
		}
	}
}


void BuildTree() {
	for (int i = 0; i < s.length(); i++) {
		Extend(s[i]);
	}
}

void DeleteTree(TNode* cur = head) {
	for (map<char, TNode*>::iterator it = cur->Edges.begin(); it != cur->Edges.end(); ++it) {
		DeleteTree(it->second);
	}
	delete cur;
}

void TreeInit() {
	head = new TNode(0, 0);
	head->SuffLink = head;
	activeNode = head;
}

vector<int> suffixArray;

void GetAllSuffixes(TNode* cur = head, int suffLength = 0) {
	if (cur->Edges.size() == 0 ) {
		
		suffixArray.push_back(cur->GetRight() - suffLength);
	}
	else {
		for (map<char, TNode*>::iterator it = cur->Edges.begin(); it != cur->Edges.end(); ++it) {
			GetAllSuffixes(it->second, 
				suffLength + it->second->GetRight() - it->second->Left);
		}
	}
	
}


int RightBinSearch(int l, int r, int i, string tmplt) {
	if(tmplt[i] > s[suffixArray[r] + i] &&
		tmplt[i] < s[suffixArray[l] + i]) {
		return r;
	}
	while( l < r) {
		int m = (l + r) / 2;
		if(s[suffixArray[m] + i] > tmplt[i]) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}
	return r;
}

int LeftBinSearch(int l, int r, int i, string tmplt) {
	if(tmplt[i] > s[suffixArray[r] + i] &&
		tmplt[i] < s[suffixArray[l] + i]) {
		return l;
	}
	while( l < r) {
		int m = (l + r) / 2;
		if(s[suffixArray[m] + i] < tmplt[i]) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return l;
}

void FindAll(string tmplt) {
	int l = 0;
	int r = suffixArray.size();
	for( int i = 0; i < tmplt.length(); i++) {
		l = LeftBinSearch(l, r, i, tmplt);
		r = RightBinSearch(l, r, i, tmplt);
		cout << l << ":" << r << endl;
	}
}

void GenerateString(int length) {
	srand(time(0));
	for (int i = 0; i < length; i++) {
		s += char(rand() % 26 + 97);
	}
	s += '$';
}

int main()
{
	GenerateString(100000);  // check linear time
	//s = "howeverwhenthenumberofdocumentstosearchispotentiallylargeorthequantityofsearchqueriestoperformissubstantialtheproblemoffulltextsearchisoftendivided$";
	TreeInit();
	BuildTree();
	GetAllSuffixes();
	DeleteTree();
	//for( int i = 0; i < suffixArray.size(); i++) {
		//cout << s.substr(suffixArray[i], s.length() - suffixArray[i]) << endl;
	//}
	cout << "s length: " << s.length() << endl;
	cout << "count of suffixes: " << suffixArray.size() << endl;
	//FindAll("e");
    return 0;
}