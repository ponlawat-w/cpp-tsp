#ifndef TSP_PSO_HPP
#define TSP_PSO_HPP

#include <random>
#include <vector>
#include <iostream>
#include "../model/graph.hpp"
#include "particle.hpp"

namespace TSP::PSO {

    class ParticleSwarm {
        Graph* graph;

        int startVertex;
        int** adjacency;

        Particle** particles;
        int particleSize;

        int bestWeight;
        vector<int> bestVertexOrder;
        Particle* particleThatContainsBestWeight;

        mt19937 generator;
        uniform_real_distribution<double> distribution;

        void init(Graph*, int startVertex, int particles, int iteration);
        void moveParticles();
        void applyBest(Particle*);

    public:
        double personalConstant = 1;
        double globalConstant = 1;
        int iteration = 500;
        bool printStatus = true;

        ParticleSwarm(Graph*, int startVertex);
        ParticleSwarm(Graph*, int startVertex, int particles);
        ParticleSwarm(Graph*, int startVertex, int particles, int iteration);
        ParticleSwarm(Graph*, int startVertex, int particles, int iteration, bool startCalculation);
        ~ParticleSwarm();
        void calculate();

        int getTotalWeight();
        int getTotalWeight(vector<int>);
        vector<int> getVertexOrder();

        double randomDouble();
    };

}

#endif //TSP_PSO_HPP
