#ifndef TSP_EDGE_HPP
#define TSP_EDGE_HPP

namespace TSP::Model {
    class Edge {
        int vertices[2];
        int weight;
        void setVertices(int, int);

    public:
        Edge(int v1, int v2);
        Edge(int v1, int v2, int weight);
        bool connects(int);
        bool equallyConnects(Edge);
        bool sameVertices(int, int);
        void orderVertices(int v1, int v2);
        int getVertex(int);
        int* getVertices();
        int getWeight();
        int getAnotherVertex(int);
    };
}

#endif //TSP_EDGE_HPP
