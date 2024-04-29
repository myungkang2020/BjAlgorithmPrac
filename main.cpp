#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct road{
    int goal;
    int time;
};
//
int main()
{
    // 도로 양방향, 웜홀 단방향
    int TC, N, M, W; // test 케이스 개수, 노드 개수, 도로 개수, 웜홀 개수
    cin >> TC;

    int maxN = 501;
    int node[maxN];
    vector<road> graph[maxN]; // 출발, {도착, 거리}
    // test case
    for(int i = 0; i < TC; ++i)
    {
        // initialize
        fill(&node[1], &node[N+1], INT32_MAX);
        for(int ig = 0; ig < (M+N+1); ++ig)
        {
            graph[ig].clear();
        }
        // input
        cin >> N >> M >> W;
        // input road
        for(int im = 0; im < M; im++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            graph[a].push_back({b,c});
            graph[b].push_back({a,c});
        }
        // input wormhold
        for(int iw = 0; iw < W; iw++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            graph[a].push_back({b,-c});
        }

        //bfs
        bool isDone = false;
        for(int j = 0; j < N; ++j)
        {
            queue<road> q; // 출발, 이동거리 
            q.push({j, 0});
            while(q.size())
            {
                if((q.front().goal == j) && (q.front().time < 0)) {
                    cout << "YES" << endl;
                    isDone = true;
                    break;
                }
                int cur = q.front().goal;
                int dist = q.front().time;
                for(int k = 0; k < graph[cur].size(); ++k)
                {
                    int nCur = graph[cur][k].goal;
                    int nDist = dist+graph[cur][k].time;
                    if(nDist > node[nCur]) { continue; } // 이동시간이 현재 이전에 도달한 시간보다 긴 경우라면 제외 
                    node[nCur] = nDist;
                    q.push({nCur, nDist});
                }
            }
            if(isDone)
            {
                break;
            }
            cout << "NO" << endl;
        }
    }
    
    return 0;
}