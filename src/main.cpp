#include <iostream>
using namespace std;

struct Person{
    char name;
    int posX;
    int posY;
    int bike = -1;
    int *priorities;
};

int main(){
    int v; cin >> v;
    int n; cin >> n;
    int m; cin >> m;

    Person persons[v];

    char map[n][m];
    for (int i = 0; i < n; i++)
    {
       for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if(map[i][j] >= 'a' && map[i][j] <= 'a'+v){
                int personIndex = map[i][j] - 'a';
                persons[personIndex].name = map[i][j];
                persons[personIndex].posX = j;
                persons[personIndex].posY = i;
            }
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
        highest_priorities[0] = 0;
        int n = -1;
        for (int j = 0; j < v; j++)
        {
            if(persons[j].bike >= 0 || persons[j].priorities[i] < persons[highest_priorities[0]].priorities[i])
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
            // Calcular distancia entre os highest_priorities e i, e pegar o menor
            // cout << "N fiz isso ainda\n";
        }
    }

    for (int i = 0; i < v; i++)
    {
       cout << persons[i].name << " " << persons[i].bike << "\n";
    }

    // limpar o new q eu usei ali em cima 

    return 0;
}