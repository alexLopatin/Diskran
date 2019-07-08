#include "lab4.h"
using namespace std;

int TBohr::GetSuffLink(int v){
    if (Bohr[v].suffLink==-1) //если еще не считали
        if (v==0||Bohr[v].par==0) //если v - корень или предок v - корень
            Bohr[v].suffLink=0;
        else
            Bohr[v].suffLink=GetAutoMove(GetSuffLink(Bohr[v].par), Bohr[v].symb);
    return Bohr[v].suffLink;
}
int TBohr::GetAutoMove(int v, char ch){
    if (Bohr[v].autoMove[ch]==-1)
        if (Bohr[v].nextVertex[ch]!=-1)
            Bohr[v].autoMove[ch]=Bohr[v].nextVertex[ch];
        else
            if (v==0)
                Bohr[v].autoMove[ch]=0;
            else
                Bohr[v].autoMove[ch]=GetAutoMove(GetSuffLink(v), ch);
    return Bohr[v].autoMove[ch];
}
TBohr::TBohr(const string& s) {
    Pattern = s;
    Bohr.push_back(TBohrVertex(0, '#'));

    // split string with delimiter '?'
    string str = s;
    string delimiter = "?";
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
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
        token = str.substr(0, pos-l);
        cout << token << endl;
        AddString(token);
        str.erase(0, pos + delimiter.length()+t);
    }
    cout << str << endl;
    AddString(str);
}
void TBohr::AddString(const string& s) {
    int num = 0;

    for (int i = 0; i < s.length(); i++) {
        char ch = s[i] - 'a';
        if( Bohr[num].nextVertex[ch] == -1) {
            Bohr.push_back(TBohrVertex(num,ch));
            Bohr[num].nextVertex[ch] = Bohr.size()-1;
        }
        num = Bohr[num].nextVertex[ch];
    }
    
    Bohr[num].flag = true;
    PatternSplit.push_back(s);
    Bohr[num].patternNumber = PatternSplit.size() - 1;
}
bool TBohr::IsStringInBohr(const string& s) {
int num = 0;
for (int i = 0; i < s.length(); i++) {
    char ch = s[i] - 'a';
    if( Bohr[num].nextVertex[ch] == -1) {
        return false;
    }
    num = Bohr[num].nextVertex[ch];
}
return true;
}
int TBohr::GetSuffFLink(int v){ 
   if (Bohr[v].suffFLink==-1){
      int u = GetSuffLink(v);
      if (u==0) //либо v - корень, либо суф. ссылка v указывает на корень 
         Bohr[v].suffFLink=0;
      else
         Bohr[v].suffFLink=(Bohr[u].flag)?u:GetSuffFLink(u);
   }
   return Bohr[v].suffFLink;
}

void TBohr::FindAllPos(const string& s){
    int u=0;
    for(int i=0;i<s.length();i++){
        u=GetAutoMove(u,s[i]-'a');
        Check(u,i+1);
    }
}
void TBohr::Check(int v,int i){
    for(int u=v;u!=0;u=GetSuffFLink(u)){
        if (Bohr[u].flag) 
            cout<<i-PatternSplit[Bohr[u].patternNumber].length()+1<<" "<<PatternSplit[Bohr[u].patternNumber]<<endl;
    }
}


int main(int argc, char *argv[]) {
    TBohr* bohr = new TBohr("cat goat ? dog ? lamp nose airplane ? go ons");
    
    delete bohr;
}