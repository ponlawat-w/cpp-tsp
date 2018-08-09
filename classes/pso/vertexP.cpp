#include "vertexP.hpp"

namespace TSP::PSO {

    VertexP::VertexP(int vertex, double position) {
        this->vertex = vertex;
        this->position = position;
    }

    bool VertexP::comparePositionAscending(const VertexP A, const VertexP B) {
        return A.position < B.position;
    }

    bool VertexP::pointerComparePositionAscending(const VertexP *A, const VertexP *B) {
        return A->position < B->position;
    }
}