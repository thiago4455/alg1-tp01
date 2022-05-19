#include <iostream>
#include <queue>
using namespace std;

struct Position{
    int posX;
    int posY;
};

bool operator==(const Position p1, const Position p2){
    return p1.posX == p2.posX && p1.posX == p2.posY;
}

bool operator>(const Position p1, const Position p2){
    if(p1.posX==p2.posX)
        return p1.posY > p2.posY;
    return p1.posX > p2.posX;
    }

int dijkstras_pathfinder(vector<vector<bool>>& map, int n, int m, Position spos, Position dpos);

struct Person{
    char name;
    Position pos;
    int bike = -1;
    int *priorities;
};

int main(){
    int v; cin >> v;
    int n; cin >> n;
    int m; cin >> m;

    Person persons[v];
    Position bikes[v];

    vector<vector<bool>> map(n,vector<bool>(m));
    for (int i = 0; i < n; i++)
    {
       for (int j = 0; j < m; j++)
        {
            char p; cin >> p;
            if(p >= 'a' && p <= 'a'+v){
                int personIndex = p - 'a';
                persons[personIndex].name = p;
                persons[personIndex].pos.posX = j;
                persons[personIndex].pos.posY = i;
                persons[personIndex].bike = -1;
            } else if (p >= '0' && p <= '0'+v){
                int bikeIndex = p - '0';
                bikes[bikeIndex].posX = j;
                bikes[bikeIndex].posY= i;
            }
            map[i][j] = (p != '-');
        }
    }

    for (int i = 0; i < v; i++)
    {
       int *priorities = new int[v];
       for (int j = 0; j < v; j++)
        {
            cin >> priorities[j];
        }
        persons[i].priorities = priorities;
    }

    for (int i = 0; i < v; i++)
    {
        int highest_priorities[v];
        highest_priorities[0] = 0; // 0
        int n = -1;
        for (int j = 0; j < v; j++)
        {
            if(persons[j].bike >= 0 || (n > -1 && persons[j].priorities[i] < persons[highest_priorities[0]].priorities[i]))
                continue;
            if (persons[j].priorities[i] == persons[highest_priorities[0]].priorities[i])
                n++;
            else
                n = 0;

            highest_priorities[n] = j;
        }
        
        if(n == 0)
            persons[highest_priorities[0]].bike = i;
        else{
            // Get person from highest_priorities with lowest distance to bike i
            int lowest_distance = 2000; //Start with max distance possible
            int closest_person;
            for (int k = 0; k < n; k++)
            {
                int d = dijkstras_pathfinder(map, n, m, persons[highest_priorities[k]].pos, bikes[i]);
                
                if(d < lowest_distance){
                    lowest_distance = d;
                    closest_person = highest_priorities[k];
                }
            }
            persons[closest_person].bike = i;
        }
    }

    for (int i = 0; i < v; i++)
    {
       cout << persons[i].name << " " << persons[i].bike << "\n";
    }

    return 0;
}

struct Node{
    Position pos;
    int distance;
};

bool operator>(const Node& n1, const Node& n2){
    if(n1.distance==n2.distance)
        return n1.pos > n2.pos;
    return n1.distance > n2.distance;
}

// Find shortest distance between source and destination on map
int dijkstras_pathfinder(vector<vector<bool>>& map, int n, int m, // Map array and dimensions
    Position spos, Position dpos){ // Source and destination positions

    priority_queue <Node, vector<Node>, greater<Node>> heap;
    heap.push({spos, 0});


    while (!heap.empty())
    {
        Node nd = heap.top();
        heap.pop();

        if(nd.pos == dpos)
            return nd.distance;
            
        // Verify boundaries for earch adjacent position and add to heap
        if(nd.pos.posX > 0 && map[nd.pos.posY][nd.pos.posX-1])
            heap.push({{nd.pos.posX-1,nd.pos.posY}, nd.distance + 1});
        if(nd.pos.posX+1 < m && map[nd.pos.posY][nd.pos.posX+1])
            heap.push({{nd.pos.posX+1,nd.pos.posY}, nd.distance + 1});
        if(nd.pos.posY > 0 && map[nd.pos.posY-1][nd.pos.posX])
            heap.push({{nd.pos.posX,nd.pos.posY-1}, nd.distance + 1});
        if(nd.pos.posY+1 < n && map[nd.pos.posY+1][nd.pos.posX])
            heap.push({{nd.pos.posX,nd.pos.posY+1}, nd.distance + 1});

        // Mark node as visited
        map[nd.pos.posY][nd.pos.posX] = false;
    }
    return n+m;
}