/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITE = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    //arrays
    int *path = new int[size - 1];
    int *dist = new int[size - 1];
    bool *done = new bool[size - 1];
    int w = 0;
    
    for (int i = 1; i <= size; i++)
    {
        path[i] = 0;
        dist[i] = INFINITE;
        done[i] = false;
    }
    
    dist[1] = 0; //distance to starting vertex is 0
    done[1] = true; //starting vertex done
    int v = 1;
    
    while (true)
    {
        Node *temp = array[v].getFirst(); //set pointer to first node in tree
        
        while (temp != nullptr) //while there are unvisited nodes...
        {
            if (done[temp->vertex] == false && dist[temp->vertex] > temp->weight)
            {
                dist[temp->vertex] = temp->weight;
                path[temp->vertex] = v;
            }
            temp = array[v].getNext();
        }
        int lowDist = INFINITE;
        
        for (int i = 1; i <= size; i++)
        {
            if (dist[i] < lowDist && !done[i])
            {
                lowDist = dist[i];
                v = i;
            }
        }
        
        if (lowDist == INFINITE)
        {
            break;
        }
        
        done[v] = true;
        w += dist[v];
        
        std::cout << "(" << path[v] << ", " << v << ", " << dist[v] << ")" << std::endl;
    }
    
    std::cout << "Total weight: " << w << std::endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    Heap<Edge> H;
    DSets D(size + 1);
    
    int v = 1;
    bool *heapChecked = new bool[size + 1];
    
    for (int i = 1; i < size; i++)
    {
        heapChecked[i] = true;
        Node *tempNode = array[v].getFirst();
        
        while (tempNode != nullptr)
        {
            if (heapChecked[tempNode->vertex] != true)
            {
                H.insert(Edge(i, tempNode->vertex, tempNode->weight));
            }
            tempNode = array[i].getNext();
        }
    }
    
    int counter = 0;
    int w = 0;
    
    while (counter < size - 1)
    {
        Edge e = H.deleteMin();
        
        if (D.find(e.head) != D.find(e.tail))
        {
            cout << e << endl;
            
            D.join(D.find(e.head), D.find(e.tail));
            w += e.weight;
            
            counter++;
        }
    }
    
    cout << endl << "Total weight = " << w << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
