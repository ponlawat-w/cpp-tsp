#ifndef TSP_PARTICLE_HPP
#define TSP_PARTICLE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "../model/graph.hpp"
#include "vertexP.hpp"

namespace TSP::PSO {

    using namespace TSP::Model;

    class Particle {
        int size;

        int weight;
        VertexP** vertices;

        int bestWeight;
        double* bestPositions;

    public:
        double* velocities;

        Particle(Graph*, int startVertex, double);
        ~Particle();
        void move(int);
        void updateBest(int** adjacency);

        int getTotalWeight(VertexP** positions, int** adjacency);
        void copyVertexPsToPositions(VertexP** from, double* to);
        void copyPositionsToVertexPs(double* from, VertexP** to);

        int getBestValue();
        double* getBestPositions();

        double vertexPosition(int);
        double vertexBestPosition(int);
        double* vertexPositions();

        vector<int> getBestVertexOrder();
    };

}

#endif //TSP_PARTICLE_HPP