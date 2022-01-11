#include <iostream>
#include <vector>

using namespace std;
class BestTravel
{
public:
    static int chooseBestSum(int t, int k, std::vector<int>& ls);
};
int chooseBestSum(int t, int k, std::vector<int>& ls)
{
    //unsigned int i = 0;
    std::vector<int> sumAll;
    int sum = 0;
    for(int i = 0; i <= ls.size(); ++i)
    {
        for(int j= i+1; j<=ls.size(); ++j)
        {
            for (int k = j+1; k <= ls.size(); ++k)
            {
                sumAll.push_back(ls[i] + ls[j] + ls[k]);
            }
        }
    }
    for(auto it = begin(sumAll); it!= end(sumAll); ++it)
    {
        //cout << "i am here" << endl;
        //std::cout << *it << std::endl;
        if(*it > sum)
        {
            sum = *it;
        }

    }
    return sum;

}

int main()
{
    vector<int> ts = {50, 55, 56, 57, 58};
    int n = chooseBestSum(163, 3, ts);
    cout << n<< endl;
    return 0;
}
