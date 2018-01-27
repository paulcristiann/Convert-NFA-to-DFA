#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

ifstream f("date.in");

unsigned int ns, nf, s;

vector<unsigned int> stariFinale;
vector< vector <pair <char,int> > > automatN(10001);
vector<char> simboluri;
vector<bool> marcat(10001);

vector<int> move(vector<int> stari, char simbol)
{
    for(int i=0; i<10001; i++)
        marcat[i] = 0;
    vector<int> stare;
    for(int i=0; i<stari.size(); i++)
    {
        for(int j=0; j<automatN[stari[i]].size(); j++)
            if(automatN[stari[i]].at(j).first == simbol && marcat[automatN[stari[i]].at(j).second] == 0)
            {
                marcat[automatN[stari[i]].at(j).second] = 1;
                stare.push_back(automatN[stari[i]].at(j).second);
            }
    }
    return stare;
}

int main(int argc, char** argv) {

    f>>ns>>nf>>s;
    unsigned int x;
    for(int i=0; i<nf; i++)
    {
        f>>x;
        stariFinale.push_back(x);
    }
    
    unsigned int stare1,stare2;
    char simbol;
    
    while(f>>stare1>>simbol>>stare2)
    {
        automatN[stare1].push_back(make_pair(simbol,stare2));
        bool gasit = 0;
        for(int i=0; i<simboluri.size(); i++)
            if(simboluri[i] == simbol)
                gasit = 1;
        if(gasit == 0)
            simboluri.push_back(simbol);
    }
    
    /* TESTE
    //afisare automat nedeterminist
    for(int i=0; i<ns; i++)
    {
        cout<<i<<": ";
        for(int j=0; j<automatN[i].size(); j++)
            cout<<"("<<automatN[i].at(j).first<<","<<automatN[i].at(j).second<<") ";
        cout<<endl;
    }
    
    cout<<"Stari finale:";
    //afisare stari finale
    for(int i=0; i<stariFinale.size(); i++)
        cout<<stariFinale[i]<<" ";
    cout<<endl;

    cout<<"Simbolurile aparute:";
    for(int i=0; i<simboluri.size(); i++)
        cout<<simboluri[i]<<" ";
    cout<<endl;
    
    cout<<"Functia move:";
    vector<int> ss;
    ss.push_back(0);
    //ss.push_back(1);
    //ss.push_back(2);
    vector<int> verif;
    verif = move(ss,'b');
    for(int i=0; i<verif.size(); i++)
        cout<<verif[i]<<" ";
    */ 
    
    //Conversie in AFD
    
    vector< vector <pair <char,int> > > automatD(10001);
    vector< vector <int> > Q;
    vector<int> ss;
    ss.push_back(0);
    for(int i=0; i<ss.size(); i++)
        cout<<ss[i]<<" ";
    cout<<endl;
    Q.push_back(ss);
    
    for(int i=0; i<Q.size(); i++)
    {
        for(int j=0; j<simboluri.size(); j++)
        {
            ss = move(Q[i],simboluri[j]);
            if(!ss.empty())
            {
                sort(ss.begin(),ss.end());
                bool gasit = 0;
                for(int z=0; z<Q.size(); z++)
                    if(Q[z] == ss)
                    {
                        gasit = 1;
                        automatD[i].push_back(make_pair(simboluri[j],z));
                    }
                if(gasit == 0)
                {
                    Q.push_back(ss);
                    for(int i=0; i<ss.size(); i++)
                        cout<<ss[i]<<" ";
                    cout<<endl;
                    automatD[i].push_back(make_pair(simboluri[j],Q.size()-1));
                }
            }
        }
    }
    
    //Stabilire stari finale
    vector<int> stariFinaleD;
    
    for(int i=0; i<10001; i++) //reinitializare vector de marcare
        marcat[i] = 0;
    
    for(int i=0; i<Q.size(); i++)
    {
        for(int j=0; j<Q[i].size(); j++)
            for(int z=0; z<stariFinale.size(); z++)
                if(Q[i].at(j) == stariFinale[z] && marcat[i] == 0)
                {
                    stariFinaleD.push_back(i);
                    marcat[i] = 1;
                }
    }
    
    /*// afisare stari AFD
    cout<<"Starile AFD sunt"<<endl;
    for(int i=0; i<Q.size(); i++)
    {
        cout<<i<<": ";
        for(int j=0; j<Q[i].size(); j++)
            cout<<Q[i].at(j)<<" ";
        cout<<endl;
    }
    cout<<endl;
    */
        
    //afisare AFD
    
    cout<<Q.size()<<" "<<stariFinaleD.size()<<" "<<simboluri.size()<<endl;
    for(int i=0; i<stariFinaleD.size(); i++)
        cout<<stariFinaleD[i]<<" ";
    cout<<endl;
    for(int i=0; i<Q.size(); i++)
        for(int j=0; j<automatD[i].size(); j++)
            cout<<i<<" "<<automatD[i].at(j).first<<" "<<automatD[i].at(j).second<<endl;
    
    return 0;

}