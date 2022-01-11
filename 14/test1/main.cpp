#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
bool isValidWalk(std::vector<char> walk) {
  int n = 0,s = 0,w = 0,e = 0;
  if(walk.size() != 10)
  {
      return false;
  }
  for(auto it = walk.begin(); it != walk.end(); ++it)
  {
      if(*it == 'n') n+=1;
      if(*it == 's') s+=1;
      if(*it == 'w') w+=1;
      if(*it == 'e') e+=1;
  }
  cout << "n : " << n << "s : " << s << " " << w << " " << e << endl;
  if(n!=s or w!=e)
  {
      return false;
  }
  return true;
}

int main()
{
    vector<char> V= {'n'};
    /*cout << isValidWalk(V) << endl;
    V= {'n','s','n','s','n','s','n','s','n','s'};
    cout << isValidWalk(V) << endl;
    V= {'n','s'};
    cout << isValidWalk(V) << endl;
    V= {'n','s','n','s','n','s','n','s','n','s','n','s'};
    cout << isValidWalk(V) << endl;
    V= {'e','w','e','w','n','s','n','s','e','w'};
    cout << isValidWalk(V) << endl;
    V= {'n','s','e','w','n','s','e','w','n','s','e','w','n','s','e','w'};
    cout << isValidWalk(V) << endl;
    V= {'n','s','e','w','n','s','e','w','n','s'};
    cout << isValidWalk(V) << endl;
    V= {'s','e','w','n','n','s','e','w','n','s'};
    cout << isValidWalk(V) << endl;*/
    V= {'n','s','n','s','n','s','n','s','n','n'};
    cout << isValidWalk(V) << endl;
    //V= {'e','e','e','w','n','s','n','s','e','w'};
    //cout << isValidWalk(V) << endl;

}
