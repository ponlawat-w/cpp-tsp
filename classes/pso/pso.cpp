#include "pso.hpp"

namespace TSP::PSO {

    ParticleSwarm::ParticleSwarm(Graph* graph, int startVertex) {
        this->init(graph, startVertex, 200, 500);
        this->calculate();
    }

    ParticleSwarm::ParticleSwarm(Graph* graph, int startVertex, int particles) {
        this->init(graph, startVertex, particles, 500);
        this->calculate();
    }

    ParticleSwarm::ParticleSwarm(Graph* graph, int startVertex, int particles, int iteration) {
        this->init(graph, startVertex, particles, iteration);
        this->calculate();
    }

    ParticleSwarm::ParticleSwarm(Graph *, int startVertex, int particles, int iteration, bool startCalculation) {
        this->init(graph, startVertex, particles, iteration);
        if (startCalculation) {
            this->calculate();
        }
    }

    ParticleSwarm::~ParticleSwarm() {
        for (int p = 0; p < this->particleSize; p++) {
            delete this->particles[p];
        }
        delete[] this->particles;

        this->graph->deallocateAdjacencyMatrix(this->adjacency);
        delete this->graph;
    }

    void ParticleSwarm::init(Graph* graph, int startVertex, int particles, int iteration) {
        this->graph = graph->clone()->makeCompleteGraph();
        this->adjacency = this->graph->getAdjacencyMatrix();
        this->startVertex = startVertex;
        this->particleSize = particles;
        this->particles = new Particle*[this->particleSize];
        this->iteration = iteration;

        this->bestWeight = -1;
        this->particleThatContainsBestWeight = nullptr;

        this->generator = mt19937((random_device())());
        this->distribution = uniform_real_distribution<double>(0.0, 1.0);

        for (int p = 0; p < this->particleSize; p++) {
            this->particles[p] = new Particle(graph, startVertex, this->distribution(this->generator));
        }
    }

    void ParticleSwarm::moveParticles() {
        for (int p = 0; p < this->particleSize; p++) {
            Particle* particle = this->particles[p];

            double* positions = particle->vertexPositions();

            for (int v = 0; v < this->graph->getVertices(); v++) {
                if (v == this->startVertex) {
                    particle->velocities[v] = 0;
                    continue;
                }

                double velocity = 1 * particle->velocities[v];
                velocity += this->personalConstant * this->randomDouble() * particle->vertexBestPosition(v) * positions[v];
                if (this->particleThatContainsBestWeight != nullptr) {
                    velocity += this->globalConstant * this->randomDouble() * this->particleThatContainsBestWeight->vertexBestPosition(v) * positions[v];
                }

                particle->velocities[v] = velocity;
            }
            particle->move(this->startVertex);

            delete[] positions;
            this->applyBest(particle);
        }
    }

    void ParticleSwarm::applyBest(Particle* particle) {
        vector<int> newVertexOrder = particle->updateBest(this->bestWeight, this->adjacency);
        if (!newVertexOrder.empty()) {
            int particleBestWeight = particle->getBestValue();
            if (this->bestWeight < 0 || particleBestWeight < this->bestWeight) {
                this->bestWeight = particleBestWeight;
                this->bestVertexOrder = newVertexOrder;
                this->particleThatContainsBestWeight = particle;
            }
        }
    }

    void ParticleSwarm::calculate() {
        if (this->printStatus) {
            cout << "\n";
        }

        for (int i = 0; i < this->iteration; i++) {
            this->moveParticles();

            if (this->printStatus && (i % 100 == 0 || i == this->iteration - 1)) {
                cout << "\rIteration " << i << " of " << (this->iteration - 1) << " (best = " << this->bestWeight << ")";
            }
        }

        if (this->printStatus) {
            cout << "\n";
        }
    }

    int ParticleSwarm::getTotalWeight() {
        return this->getTotalWeight(this->bestVertexOrder);
    }

    int ParticleSwarm::getTotalWeight(vector<int> vertexOrder) {
        if (vertexOrder.empty()) {
            return -1;
        }

        int sum = 0;

        int previousVertex = -1;
        for (int vertex: vertexOrder) {
            if (previousVertex < 0) {
                previousVertex = vertex;
                continue;
            }

            sum += this->adjacency[previousVertex][vertex];

            previousVertex = vertex;
        }

        sum += this->adjacency[previousVertex][*vertexOrder.begin()];

        return sum;
    }

    vector<int> ParticleSwarm::getVertexOrder() {
        if (this->particleThatContainsBestWeight == nullptr) {
            return vector<int> {};
        }

        return this->particleThatContainsBestWeight->getBestVertexOrder();
    }

    double ParticleSwarm::randomDouble() {
        return this->distribution(this->generator);
    }
}