#include <iostream>
#include <vector>
#include <string>
#define STATE_MAX 5000
#include <list>
#include <fstream>
using namespace std;

struct state_struct {
    int this_state, next_state;
    char input;
};
vector <state_struct> dfa[STATE_MAX];


void BFS(int s, int nodes, vector<state_struct> *dfa, string test,int ends[],int len_k)
{
    bool *visited = new bool[nodes];
    for(int i = 0; i < nodes; i++)
        visited[i] = false;

    list<int> queue;

    visited[s] = true;
    queue.push_back(s);
    int x=0;
    int start=s;
    vector <int> tati;
    for (int i=0;i<nodes;i++)
        tati.push_back(-2);
    int xs[nodes];
    for(int i=0;i<nodes;i++)
        xs[i]=-1;
    xs[start]=0;
    tati[start]=-1;
    int counting[nodes];
    for(int i=0;i<nodes;i++)
        counting[i]=1;
    while(!queue.empty())
    {
        int ok=0;
        s = queue.front();
        //cout << s << " ";
        queue.pop_front();
        for(auto&j:dfa[s])
        {
            x=xs[s];
            int cnt=1;
            if(j.this_state==j.next_state && j.input==test[xs[s]])
            {
                ok=1;
                while(j.input==test[x])
                {
                    x++;
                    cnt++;
                }
                xs[j.next_state]=x;
                counting[s]=cnt;
                visited[j.next_state]=true;
                break;
            }
        }
        for (auto&j:dfa[s])
        {
            //cout<<j.next_state<<" ";
            if (!visited[j.next_state] )
            {
                if (j.input==test[xs[s]])
                {
                    tati[j.next_state]=s;
                    xs[j.next_state]=xs[s]+1;
                    visited[j.next_state] = true;
                    queue.push_back(j.next_state);
                }
                else if(j.input=='#')
                {
                    tati[j.next_state]=s;
                    xs[j.next_state]=xs[s];
                    visited[j.next_state] = true;
                    queue.push_back(j.next_state);
                }
                else if(ok==1 && test[xs[s]-1]==j.input)
                {
                    counting[s]--;
                    tati[j.next_state]=s;
                    xs[j.next_state]=xs[s];
                    visited[j.next_state] = true;
                    queue.push_back(j.next_state);
                }
            }
        }
    }
    int mxm=0;
    for (int i=0;i<len_k;i++)
        if(xs[ends[i]]==test.size())
        {
            mxm=ends[i];
            break;
        }
    if (xs[mxm]==test.size())
    {
        int sol[STATE_MAX];
        int z=0;
        cout<<"DA"<<"\n";
        int temp=mxm;
        while(tati[temp]!=-1)
        {
            for (int j=0;j<counting[temp];j++)
            {
                sol[z]=temp;
                z++;
            }
            temp=tati[temp];
        }
        cout<<"Traseu: "<<start<<" ";
        for(int i=z-1;i>=0;i--)
            cout<<sol[i]<<" ";
        cout<<"\n";
    }
    else
        cout<<"NU"<<"\n";
}
// acelasi lucru cu vector <pair<int, string>> states;
// asemanator cu alias din linux

int main()
{

    ifstream ff;
    ff.open("teste.txt");
    // primul element din coada
    int n_states,n_arch;
    ff >> n_arch>>n_states;
    state_struct state;
    for (int i = 0; i < n_states; i++)
    {
        ff >> state.this_state >> state.next_state >> state.input;
        dfa[state.this_state].push_back(state);
    }
    int st;
    ff>>st;
    int k;
    ff>>k;
    int ends[k];
    for(int i=0;i<k;i++)
        ff>>ends[i];
    ff>>n_states;
    string z[n_states];
    for (int i=0;i<n_states;i++)
        ff>>z[i];
    for(int i=0;i<n_states;i++)
        BFS(st,n_arch,dfa,z[i],ends,k);
    return 0;
}
