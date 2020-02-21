#include "lab4.h"
using namespace std;

int TBohr::GetSuffLink(int v){
    if (Bohr[v].suffLink == -1) //если еще не считали
        if (v==0||Bohr[v].par == 0) { //если v - корень или предок v - корень
            Bohr[v].suffLink = 0;
        }
        else {
            Bohr[v].suffLink = GetAutoMove(GetSuffLink(Bohr[v].par), Bohr[v].symb);
        }
    return Bohr[v].suffLink;
}
int TBohr::GetAutoMove(int v, string s){            // метод, реализующий действие ДКА
    auto autoPair = Bohr[v].autoMove.find(s);
    auto nextPair = Bohr[v].nextVertex.find(s);
    if (Bohr[v].autoMove.count(s) == 0) {
        if (Bohr[v].nextVertex.count(s) != 0){
            autoPair->second = nextPair->second;
        }
        else{
            if (v == 0) {
                autoPair->second = 0;
            }
            else {
                autoPair->second = GetAutoMove(GetSuffLink(v), s);
            }
        }
    }
       
    autoPair = Bohr[v].autoMove.find(s);
    return autoPair->second;
}
TBohr::TBohr(const string& s) {
    Pattern = s;
    Bohr.push_back(TBohrVertex(0, "#"));

    // разбиваем строку на несколько с делителем '?'
    string str = s;
    string delimiter = "?";
    size_t pos = 0;
    int jokers = 1;
    int i = -1;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        char t, l = 0;
        if((str.size()-1) != pos) {
            if(str[pos+1] == ' ') {
                t = 1;
            }
        }                                                   
        if(pos != 0) {
            if(str[pos-1] == ' ') {
                l = 1;
            }
        }
        token = str.substr(0, pos - l);
        if(token.size() > 0) {
            AddString(token);
            jokerCount.push_back(1);
            i++;
        }
        else {
            jokerCount[i]+=1;
        }
        str.erase(0, pos + delimiter.length() + t);
    }
    if(str.size() > 0) {
        AddString(str); // Разбили строку-образец на несколько строк, не содержащих джокеров
    }
}
void TBohr::AddString(const string& s) {   // добавляет строку в бор
    int num = 0;
    TStringIterator* it = new TStringIterator(s);
    while(!it->End()) {
        string str = it->Next();
        if( Bohr[num].nextVertex.count(str) == 0) {
            Bohr.push_back(TBohrVertex(num,str));
            Bohr[num].nextVertex.insert(pair<string, int>(str,Bohr.size() - 1));
        }
        num = Bohr[num].nextVertex.find(str)->second;
    }
    Bohr[num].flag = true;
    PatternSplit.push_back(s);
    Bohr[num].patternNumber = PatternSplit.size() - 1;
    delete it;
}
int TBohr::GetSuffFLink(int v) {      // циклический переход по суффиксным ссылкам, пока не будет ссылаться на конечную вершину
   if (Bohr[v].suffFLink == -1) {
      int u = GetSuffLink(v);
      if (u == 0)                     // либо v - корень, либо суф. ссылка v указывает на корень 
         Bohr[v].suffFLink = 0;
      else
         Bohr[v].suffFLink = (Bohr[u].flag) ? u : GetSuffFLink(u);
   }
   return Bohr[v].suffFLink;
}

void TBohr::FindAllPos(const string& s){         // сам алгоритм, находит вхождения каждого подобразца в отдельности и потом проверяет
    int u = 0;                                   // их относительный порядок
    TStringIterator* it = new TStringIterator(s);
    int i = 0;
    while(!it->End()) {
        string str = it->Next();
        u = GetAutoMove(u,str);;
        for(int v = u;v != 0;v = GetSuffFLink(v)) {
            if (Bohr[v].flag) {
                Positions.push_back(pair<string, int>(PatternSplit[Bohr[v].patternNumber], i - PatternLength(Bohr[v].patternNumber) + 2));
            }
        }
        i++;
    }
    delete it;
    for ( int i = 0; i < Positions.size(); i++ )            // проверка относительного порядка
    {
        if(CheckPosition(i, 0)) {
            std::cout << Pattern 
                  << ':'
                  << Positions[i].second   
                  << std::endl;
        }
    }
    
}
bool TBohr::CheckPosition(int positionIndex, int patternIndex) {            // метод рекурсивной проверки относительного порядка
    bool res = false;
    if(Positions[positionIndex].first == PatternSplit[patternIndex]) {
        if(patternIndex == PatternSplit.size()-1) {
            return true;
        }
        if(positionIndex == Positions.size()-1) {
            return false;
        }
        int i = 1;
        while(Positions[positionIndex + i].second - PatternLength(patternIndex) - Positions[positionIndex].second <= jokerCount[patternIndex]) {
            res = res || CheckPosition(positionIndex + i, patternIndex + 1);
            i++;
            if(positionIndex + i > Positions.size() - 1) {
                break;
            }
        }    
    }
    return res;
}
int TBohr::PatternLength(int index) {
    TStringIterator* it = new TStringIterator(PatternSplit[index]);
    int i = 0;
    while(!it->End()) {
        it->Next();
        i++;
    }
    return i;
}

int main(int argc, char *argv[]) {
    TBohr* bohr = new TBohr("cat ? dog ? cow");
    bohr->FindAllPos("cat cat dog dog cow");
    delete bohr;
}