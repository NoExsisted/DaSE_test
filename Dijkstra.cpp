#include <iostream>
using namespace std;
const int MAX = 100000005; 
struct Info
{
    bool visit;
    int value;
};

class Graph
{
private:
    int vexnum;//结点
    int arcnum;//边数
    int **arc;//邻接矩阵（边的权重）
    Info *info;//结点信息
public:
    Graph(int vexnum, int arcnum);
    void creat();
    void Dijkstra(int begin);
    void print(int begin);
};

Graph::Graph(int vexnum, int arcnum)
{
    this->vexnum = vexnum;
    this->arcnum = arcnum;
    arc = new int *[vexnum];
    info = new Info[vexnum];
    int i, j;
    for(i = 0; i < vexnum; i++)
    {
        arc[i] = new int [vexnum];
        for(j = 0; j < vexnum; j++)
        {
            arc[i][j] = MAX;
        }
    }
}

void Graph::creat()
{
    int start, end, weight;
    int count = 0;
    while(count < this->arcnum)
    {
        cin>>start>>end>>weight;
        count++;
        if(start == end || weight > arc[start - 1][end -1])//一些特殊情况要处理//
        continue;
        arc[start - 1][end - 1] = weight;
    }
}

void Graph::Dijkstra(int begin)
{
    int i;
    for(i = 0; i < this->vexnum; i++)
    {
        info[i].value = arc[begin - 1][i];
    }
    info[begin - 1].value = 0;
    info[begin - 1].visit = true;
    int count = 1;
    while(count != this->vexnum)
    {
        int temp = begin;
        int min = MAX;
        for(i = 0; i < this->vexnum; i++)
        {
            if(min > info[i].value && !info[i].visit)
            {
                min = info[i].value;
                temp = i;
            }
        }
        for(i = 0; i < this->vexnum; i++)
        {
            if(!info[i].visit && arc[temp][i] != MAX)
            {
                if((info[temp].value + arc[temp][i]) < info[i].value)//松弛
                {
                    info[i].value = info[temp].value + arc[temp][i];
                }
            }
        }
        info[temp].visit = true;
        count++;
    }
}

void Graph::print(int begin)
{
    int i = this->vexnum - 1;
    if(info[i].value != MAX)
    cout<<info[i].value<<endl;
    else
    cout<<-1<<endl;
}

int main()
{
    int n, m;
    //int vexnum, arcnum;
    cin>>n>>m;
    //vexnum = n;
    //arcnum = m;
    Graph graph(n, m);
    graph.creat();
    graph.Dijkstra(1);
    graph.print(1);
    return 0;
}