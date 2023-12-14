#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "hash.hpp"
//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
int main () {
using namespace std;
using namespace std::chrono;

ifstream input = ifstream("WarAndPeace.txt");

auto start = steady_clock::now();
cout << "Parsing War and Peace" << endl;

size_t nombre_lu = 0;
bool b = false;
vector<string> x;
vector<pair<string,int>> v;

HashMap<string,int>  h (100);
std::vector<pair<string,int> > t;
// prochain mot lu
string word;
// une regex qui reconnait les caractères anormaux (négation des lettres)
regex re( R"([^a-zA-Z])");
while (input >> word) {
// élimine la ponctuation et les caractères spéciaux
word = regex_replace ( word, re, "");
// passe en lowercase
transform(word.begin(),word.end(),word.begin(),::tolower);

// word est maintenant "tout propre"
if (nombre_lu % 100 == 0)
// on affiche un mot "propre" sur 100
cout << nombre_lu << ": "<< word << endl;
nombre_lu++;
h.put(word,1);
// for(string x : v) {
//    if(x == word){
//     v<word> = v<word>
//     break;
//    }
// }
// if(b == false){
// v.push_back(word);
// }
// b= false;
// for(auto& p : v) {
// if(p.first == word){
// p.second ++;
// b=true;
// break;
// }
// }
// if(b == false){
// v.push_back(make_pair(word,1));
// }
// b= false;




}
input.close();

cout << "Finished Parsing War and Peace" << endl;

for(auto& p : v) {

if(p.first == "war"){
cout<< "Found a total of war" <<  p.second<< " different words." ;

}
if(p.first == "peace"){
cout<< "Found a total of peace" <<  p.second<< " different words." ;

}
if(p.first == "toto"){
cout<< "Found a total of toto" <<  p.second<< " different words." ;

}
}
auto end = steady_clock::now();
cout << "Parsing took "
<< duration_cast<milliseconds>(end - start).count()
<< "ms.\n";
//cout << "Found a total of " << v.size() << " different words." ;



cout << "Found a total of " << nombre_lu << " words." << endl;

return 0;
}