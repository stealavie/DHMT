#include"Voronoi.h"
#include<math.h>
#include<iostream>

Vertex::Vertex(double x, double y) : x(x), y(y) {}

double Vertex::GetX() const
{
    return x;
}
double Vertex::GetY() const
{
    return y;
}

double Vertex::distanceTo(const Vertex& other)
{
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

QuadEdge ::QuadEdge(Vertex *origin, Vertex *dest) : origin(origin), dest(dest), twin(nullptr), next(nullptr) {}

void QuadEdge::makeTwin()
{
    twin = new QuadEdge(new Vertex(dest->GetX(), dest->GetY()), new Vertex(origin->GetX(), origin->GetY()));
    twin->twin = this;
}

const std::vector<QuadEdge *> &VoronoiDiagram::getEdges() const
{
    return edges;
}

VoronoiDiagram::VoronoiDiagram(const std::vector<Vertex> &sites)
{
    for (int i = 0; i < sites.size(); i++)
    {
        for (int j = i + 1; j < sites.size(); j++)
        {
            Vertex *v1 = new Vertex(sites[i].GetX(), sites[i].GetY());
            Vertex *v2 = new Vertex(sites[j].GetX(), sites[j].GetY());
            QuadEdge *edge = new QuadEdge(v1, v2);
            edge->makeTwin();
            edges.push_back(edge);
        }
    }
}

VoronoiDiagram::~VoronoiDiagram()
{
    for (QuadEdge *edge : edges)
    {
        delete edge->origin;
        delete edge->dest;
        delete edge->twin->origin; // delete the origin of the twin edge
        delete edge->twin;         // delete the twin edge
        delete edge;               // delete the edge itself
    }
    edges.clear(); // clear the vector of edges
}

Vertex VoronoiDiagram::findClosestSite(const Vertex &point)
{
    double minDistance = 10000;
    Vertex closestSite(0, 0);

    for (QuadEdge *edge : edges)
    {
        double dist1 = point.distanceTo(*(edge->origin));
        double dist2 = point.distanceTo(*(edge->dest));

        if (dist1 < minDistance)
        {
            minDistance = dist1;
            closestSite = *(edge->origin);
        }
        if (dist2 < minDistance)
        {
            minDistance = dist2;
            closestSite = *(edge->dest);
        }
    }
    return closestSite;
}
