#ifndef TSP_VERTEXP_HPP
#define TSP_VERTEXP_HPP

namespace TSP::PSO {

    struct VertexP {
        int vertex;
        double position;
        VertexP(int, double);

        static bool comparePositionAscending(const VertexP A, const VertexP B);
        static bool pointerComparePositionAscending(const VertexP* A, const VertexP* B);
    };

}

#endif //TSP_VERTEXP_HPP
