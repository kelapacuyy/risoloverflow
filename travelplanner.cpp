#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

pair<vector<vector<double>> *, vector<vector<double>> *> readcsv(unordered_map<int, string> &cities, string path)
{
    vector<vector<double>> *adjacency_vector_dist = new vector<vector<double>>();
    vector<vector<double>> *adjacency_vector_price = new vector<vector<double>>();
    vector<string> lokasi;
    ifstream file;
    file.open(path, ios::in);
    string line, origin, destination, dis, prc;
    double distance, price;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);

        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, dis, ',');
        getline(ss, prc);
        distance = stod(dis);
        price = stod(prc);

        bool origin_ada = false, destination_ada = false;
        int p, q;
        for (int i = 0; i < lokasi.size(); ++i)
        {
            if (lokasi[i] == origin)
            {
                origin_ada = true;
                p = i;
            }
            if (lokasi[i] == destination)
            {
                destination_ada = true;
                q = i;
            }
        }
        if (!origin_ada)
        {
            cities[lokasi.size()] = origin;
            lokasi.push_back(origin);
            p = lokasi.size() - 1;
            adjacency_vector_dist->push_back(vector<double>(lokasi.size(), INT_MAX));
            adjacency_vector_price->push_back(vector<double>(lokasi.size(), INT_MAX));
            for (int a = 0; a < lokasi.size() - 1; ++a)
            {
                (*adjacency_vector_dist)[a].push_back(INT_MAX);
                (*adjacency_vector_price)[a].push_back(INT_MAX);
            }
        }
        if (!destination_ada)
        {
            cities[lokasi.size()] = destination;
            lokasi.push_back(destination);
            q = lokasi.size() - 1;
            adjacency_vector_dist->push_back(vector<double>(lokasi.size(), INT_MAX));
            adjacency_vector_price->push_back(vector<double>(lokasi.size(), INT_MAX));
            for (int a = 0; a < lokasi.size() - 1; ++a)
            {
                (*adjacency_vector_dist)[a].push_back(INT_MAX);
                (*adjacency_vector_price)[a].push_back(INT_MAX);
            }
        }

        (*adjacency_vector_dist)[p][q] = distance;
        (*adjacency_vector_price)[p][q] = price;

        // for (int i = 0; i < adjacency_vector_dist.size(); ++i) {
        //     for (int j = 0; j < adjacency_vector[i].size(); ++j) {
        //         cout << adjacency_vector[i][j] << ' ';
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    return make_pair(adjacency_vector_dist, adjacency_vector_price);
}

typedef pair<double, int> Pair;

double dijkstra(vector<vector<double>> graph, int start, int end, unordered_map<int, string> &cities)
{
    int n = graph.size();
    vector<double> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        for (int i = 0; i < graph[u].size(); ++i)
        {
            int weight = graph[u][i];

            if (dist[u] + weight < dist[i])
            {
                dist[i] = dist[u] + weight;
                prev[i] = u;
                pq.push(make_pair(dist[i], i));
            }
        }
    }

    if (dist[end] == INT_MAX)
    {
        cout << "No rute found from " << cities[start] << " to " << cities[end] << "\n";
    }
    else
    {
        cout << cities[start] << " to " << cities[end] << ": ";
        int curr = end;
        vector<int> path;
        while (curr != -1)
        {
            path.push_back(curr);
            curr = prev[curr];
        }
        for (int i = path.size() - 1; i >= 0; --i)
        {
            cout << cities[path[i]];
            if (i > 0)
            {
                cout << " -> ";
            }
        }
        cout << endl;
        return dist[end];
    }
}

int main()
{

    cout << endl
         << endl;
    cout << "  _____                                     _                ___     _                                            " << endl;
    cout << " |_   _|    _ _   __ _    __ __    ___     | |      o O O   | _ \\   | |    __ _    _ _     _ _      ___      _ _  " << endl;
    cout << "   | |     | '_| / _` |   \\ V /   / -_)    | |     o        |  _/   | |   / _` |  | ' \\   | ' \\    / -_)    | '_| " << endl;
    cout << "  _|_|_   _|_|_  \\__,_|   _\\_/_   \\___|   _|_|_   ____[O]  _|_|_   _|_|_  \\__,_|  |_||_|  |_||_|   \\___|   _|_|_  " << endl;
    cout << "_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| {======|_| \"\"\" |_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| " << endl;
    cout << "\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'./o--000'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-' " << endl
         << endl;

    cout << "Welcome to Travel Planner!" << endl;
    cout << "1. Bali" << endl;
    cout << "2. Bandung" << endl;
    cout << "3. Jakarta" << endl;
    cout << "4. Surabaya" << endl;
    cout << "Which city do you want to travel in? (1-4) : ";

    int city;
    string path;
    cin >> city;
    switch (city)
    {
    case 1:
        path = "C:\\Users\\USER\\OneDrive - apps.ipb.ac.id\\KULIAH\\Smt 4\\Strukdat\\proyek_akhir\\bali.csv";
        cout << endl << "Tourist attractions in Bali:" << endl;
        cout << "1.  Tanah Lot" << endl;
        cout << "2.  Taman Ayun" << endl;
        cout << "3.  Bali Zoo Park" << endl;
        cout << "4.  Uluwatu" << endl;
        cout << "5.  Ulun Danu Beratan" << endl;
        cout << "6.  Kebun Raya Eka Karya" << endl;
        cout << "7.  Penelokan Batur" << endl;
        cout << "8.  Tirta Empul" << endl;
        cout << "9.  Goa Gajah" << endl;
        cout << "10. Bali Safari Park" << endl << endl;
        break;
    case 2:
        path = "C:\\Users\\USER\\OneDrive - apps.ipb.ac.id\\KULIAH\\Smt 4\\Strukdat\\proyek_akhir\\bandung.csv";
        cout << endl << "Tourist attractions in Bandung:" << endl;
        cout << "1.  Farm House Bandung" << endl;
        cout << "2.  Curug Tilu Leuwi Opat" << endl;
        cout << "3.  Situ Patenggang" << endl;
        cout << "4.  Curug Cimahi" << endl;
        cout << "5.  Taman Hutan Rata" << endl;
        cout << "6.  Kebun Teh Sukawana" << endl;
        cout << "7.  Curug Cisanti" << endl;
        cout << "8.  Kawah Putih" << endl;
        cout << "9.  Tangkuban Perahu" << endl << endl;
        break;
    case 3:
        path = "C:\\Users\\USER\\OneDrive - apps.ipb.ac.id\\KULIAH\\Smt 4\\Strukdat\\proyek_akhir\\jakarta.csv";
        cout << endl << "Tourist attractions in Jakarta : " << endl;
        cout << "1.  Ragunan" << endl;
        cout << "2.  Taman Mini Indonesia Indah" << endl;
        cout << "3.  Monas" << endl;
        cout << "4.  Kota" << endl;
        cout << "5.  Ancol" << endl;
        cout << "6.  Sarinah" << endl;
        cout << "7.  Museum Fatahillah" << endl << endl;
        break;
    case 4:
        path = "C:\\Users\\USER\\OneDrive - apps.ipb.ac.id\\KULIAH\\Smt 4\\Strukdat\\proyek_akhir\\surabaya.csv";
        cout << endl << "Tourist attractions in Surabaya:" << endl;
        cout << "1.  Stasiun Gubeng" << endl;
        cout << "2.  Siola Surabaya Museum" << endl;
        cout << "3.  Museum WR. Soepratman" << endl;
        cout << "4.  Museum Hos Tjokroaminoto" << endl;
        cout << "5.  Museum Dr. Soetomo" << endl;
        cout << "6.  Museum Sepuluh Nopember" << endl << endl;
        break;
    default:
        cout << "Please enter a number between 1-4!" << endl;
        break;
    }

    unordered_map<int, string> cities;
    pair<vector<vector<double>> *, vector<vector<double>> *> adjacency_vector = readcsv(cities, path);
    vector<vector<double>> adjacency_vector_dist = *adjacency_vector.first;
    vector<vector<double>> adjacency_vector_price = *adjacency_vector.second;
    int m, n;

    cout << "Select Starting Point : ";
    cin >> m;
    cout << "Select Destination : ";
    cin >> n;
    cout << "Route with shortest distance from ";
    double shortest_distance = dijkstra(adjacency_vector_dist, m - 1, n - 1, cities);
    cout << " >> Shortest distance: " << shortest_distance << "km" << endl;
    cout << "Route with lowest price from ";
    double lowest_price = dijkstra(adjacency_vector_price, m - 1, n - 1, cities);
    cout << " >> Lowest price: " << lowest_price << "k" << endl << endl;
    // for (int i = 0; i < 10; ++i) {
    //     cout << cities[i] << endl;
    // }
}