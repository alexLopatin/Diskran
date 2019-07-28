 ConsoleApplication50.cpp определяет точку входа для консольного приложения.


#include stdafx.h
#include iostream
#include string
#include vector
#include map
using namespace std;


int currentStringCount = 0;

class TNode {
	int Right;					 [Left; Right)
public
	int Left;
	int GetRight() {
		return ((Right == -1)  currentStringCount  Right);
	}
	TNode Parent;
	mapchar, TNode Edges;
	TNode SuffLink;
	TNode(int left, int right)  Left(left), Right(right) {
		SuffLink = this;
	}
};

string s;
TNode head;


enum Rules {EXTENSION, BRANCH, SPLIT_EDGE, EMPTY, DONTDOANY};

struct TState {
	TNode CurrentNode;
	int CurPosInEdge = 0;
	int CurPosInSuf;
	int LeftIndexSuf;
	int RightIndexSuf;
	TState(TNode currentNode, int leftIndexSuf, int rightIndexSuf) CurrentNode(currentNode), LeftIndexSuf(leftIndexSuf), RightIndexSuf(rightIndexSuf), CurPosInSuf(leftIndexSuf) {}
	Rules Go() {
		if (CurPosInSuf == RightIndexSuf) {
			cout  EMPTY  endl;
			return EMPTY;
		}
		if (CurPosInEdge == CurrentNode-GetRight()) {
			if (CurrentNode-Edges.find(s[CurPosInSuf]) != CurrentNode-Edges.end()) {
				CurrentNode = CurrentNode-Edges[s[CurPosInSuf]];
				CurPosInEdge = CurrentNode-Left;
			}
			else {
				if (CurrentNode-Edges.size() == 0 && CurrentNode != head) {
					return EXTENSION;
				}
				else {
					return BRANCH;
				}
			}
		}
		else {
			if (s[CurPosInSuf] == s[CurPosInEdge]) {
				CurPosInSuf++;
				CurPosInEdge++;
			}
			else {
				return SPLIT_EDGE;
			}
		}
		return DONTDOANY;
	}
};

void InsertSuffix(int leftSuf, int rightSuf, TNode node);

void GoToNextSuffix(TNode fromWhereWeGo, int CurPosInEdge, int rightSuf) {
	TNode suffNode = fromWhereWeGo-Parent-SuffLink;
	InsertSuffix(rightSuf - CurPosInEdge + fromWhereWeGo-Left - (fromWhereWeGo-Parent != head), rightSuf, suffNode);
	cout  goes to next suffix  endl;
}

TNode lastInnerVertex = 0;

int lastNotEmpty = 0;

void InsertSuffix(int leftSuf, int rightSuf, TNode node = head) {
	if (leftSuf = rightSuf) {
		return;
	}
	TState state = new TState(node, leftSuf, rightSuf);
	int rule = DONTDOANY;
	while (rule == DONTDOANY) {
		rule = state-Go();
	}
	if (rule == EMPTY) {
		state-CurPosInEdge--;
		if (lastInnerVertex != 0) {
			lastInnerVertex-SuffLink = state-CurrentNode-Parent;
			lastInnerVertex = 0;
		}
		return;
	}
	else if (rule == EXTENSION) {
		state-CurrentNode-Right++;
	}
	else if (rule == BRANCH) {
		TNode newNode = new TNode(rightSuf - 1, -1);  -1 - currentStringCount
		state-CurrentNode-Edges[s[rightSuf - 1]] = newNode;
		newNode-Parent = state-CurrentNode;
		if (lastInnerVertex != 0) {
			lastInnerVertex-SuffLink = state-CurrentNode;
			lastInnerVertex = 0;
		}
		state-CurrentNode = newNode;
		lastNotEmpty = leftSuf + 1;
		lastNotEmpty++;
	}
	else if (rule == SPLIT_EDGE) {
		TNode newParent = new TNode(state-CurrentNode-Left, state-CurPosInEdge);
		int left = state-CurrentNode-Left;
		state-CurrentNode-Left = state-CurPosInEdge;
		newParent-Parent = state-CurrentNode-Parent;
		newParent-Parent-Edges[s[left]] = newParent;
		state-CurrentNode-Parent = newParent;
		TNode newNode = new TNode(rightSuf - 1, -1);  -1 - currentStringCount
		newNode-Parent = newParent;
		newParent-Edges[s[rightSuf - 1]] = newNode;
		newParent-Edges[s[state-CurPosInEdge]] = state-CurrentNode;
		state-CurrentNode = newParent;
		state-CurPosInEdge = state-CurrentNode-GetRight();
		if (lastInnerVertex != 0) {
			lastInnerVertex-SuffLink = state-CurrentNode;
		}
		lastInnerVertex = state-CurrentNode;
		lastNotEmpty = leftSuf;
	}
	TNode cur = state-CurrentNode;
	int curPos = state-CurPosInEdge;
	
	if (rule == SPLIT_EDGE) {
		rule = 2;
	}
	delete state;
	if (rule != DONTDOANY) {
		GoToNextSuffix(cur, curPos, rightSuf);
	}
}

void BuildTree() {
	for (int i = 1; i = s.length(); i++) {
		for (int j = 0; j  i; j++) {
			currentStringCount = i;
			InsertSuffix(j, i);
		}
	}

}

void TreeInit() {
	head = new TNode(0, 0);
	head-Parent = head;
	head-SuffLink = head;
}

int countOfSuffs = 0;

void PrintSuff(TNode cur = head, string str = ) {
	if (cur-Edges.size() == 0) {
		countOfSuffs++;
		cout  str  endl;
	}
	else {
		for (mapchar, TNodeiterator it = cur-Edges.begin(); it != cur-Edges.end(); ++it)
		{
			
			PrintSuff(it-second, str + s.substr(it-second-Left, it-second-GetRight() - it-second-Left));
		}
	}
	
}

void FindAll(string tmplt, TNode node = head) {
	
}

int main()
{
	s = banantrutyuiyiyuiyertretfghfhgjnbmbnuiyiuyijbanantrutyuiyiyuiyertretfghfhgjnbmbnuiyiuyijnkjhkjhjtyutyurtyfgbvnbmbnmjhklllllhhggfrtoooooooooosdpoooouooiuoioouiououiaavabababrtutyjhgjfgjrtfrtyryedfghgrgergergerhfgjghmbnmfhtasnkjhkjhjtyutyurtyfgbvnbmbnmjhklllllhhggfrtoooooooooosdpoooouooiuoioouiououiaavabababrtutyjhgjfgjrtfrtyryedfghgrgergergerhfgjghmbnmfhtabanantrutyuiyiyuiyertretfghfhgjnbmbnuiyiuyijnkjhkjhjtyutyurtyfgbvnbmbnmjhklllllhhggfrtoooooooooosdpoooouooiuoioouiououiaavabababrtutyjhgjfgjrtfrtyryedfghgrgergergerhfgjghmbnmfhtass;
	s = wehopeyouwillmaintainyourmembershipandwillencourageboththelibrariesyouuseandalsootherindividualstojoinMembershipconveysmanybenefitsforyouandforthewideracademiccommunityconcernedfortheunderstandingofmedievaltexts$;
	cout  s length   s.length()  endl;
	TreeInit();
	BuildTree();
	PrintSuff();
	cout  count of suffs   s.length()  endl;
	FindAll(courage);
    return 0;
}

