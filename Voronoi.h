#include<vector>

class Vertex {
    private:
    double x, y;
    public:
    Vertex(double x, double y);
    double GetX() const;
    double GetY() const;
    double Vertex::distanceTo(const Vertex& other);
};

class QuadEdge {
public:
    Vertex* origin;
    Vertex* dest;
    QuadEdge* twin;
    QuadEdge* next;

    QuadEdge (Vertex* origin, Vertex* dest);

    void makeTwin();
};

class VoronoiDiagram {
private:
    std::vector<QuadEdge*> edges;

public:
    const std::vector<QuadEdge*>& getEdges() const;
    VoronoiDiagram(const std::vector<Vertex>& sites);
    ~VoronoiDiagram();

    Vertex findClosestSite(const Vertex& point);
};
