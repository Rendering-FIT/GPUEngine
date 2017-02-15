#pragma once

#include<cstddef>
#include<vector>
#include<cassert>

class Adjacency{
  public:
    /**
     * @brief constructor of adjacency information
     *
     * @param points vertices, three consecutive vertices form triangle
     * @param numTriangles number of triangles
     * @param maxMultiplicity edges with larger nof opposite vertices will be split
     */
    Adjacency(
        float  const*vertices       ,
        size_t const&nofTriangles   ,
        size_t const&maxMultiplicity);
    /**
     * @brief gets number of edges
     *
     * @return 
     */
    size_t getNofEdges()const;
    /**
     * @brief gets indices of edge vertices
     *
     * @param e edge number
     * @param i 0 - vertex a, 1 - vertex b of edge e
     *
     * @return index of vertex a or b of edge e
     */
    size_t getEdge(size_t e,size_t i)const;
    /**
     * @brief gets index of edge vertex A
     *
     * @param e edge index
     *
     * @return index of vertex A of an edge e
     */
    size_t getEdgeVertexA(size_t e)const{assert(this!=nullptr);return this->getEdge(e,0);}
    /**
     * @brief gets index of vertex B of edge
     *
     * @param e
     *
     * @return 
     */
    size_t getEdgeVertexB(size_t e)const{assert(this!=nullptr);return this->getEdge(e,1);}
    /**
     * @brief gets number of opposite vertices of edge e
     *
     * @param e edge number
     *
     * @return number of opposite vertice of edge e
     */
    size_t getNofOpposite(size_t e)const;
    /**
     * @brief gets index of opposite vertex
     *
     * @param e edge e
     * @param i ith opposite vertex
     *
     * @return index of ith opposite vertex of edge e
     */
    size_t getOpposite   (size_t e,size_t i)const;
    /**
     * @brief gets maximal multiplicity
     *
     * @return maximal multiplicity
     */
    size_t getMaxMultiplicity()const;
    /**
     * @brief gets array of vertices
     *
     * @return array of vertices
     */
    float const*getVertices()const;
    /**
     * @brief gets nof triangles
     *
     * @return number of triangles
     */
    size_t getNofTriangles()const;
  protected:
    class EdgeAdjacency{
      public:
        size_t ab[2] ;
        size_t offset;
        size_t count ;
        EdgeAdjacency(size_t const&a,size_t const&b,size_t const&offset,size_t const&count){
          this->ab[0] = a;
          this->ab[1] = b;
          this->offset = offset;
          this->count  = count;
        }
    };
    std::vector<EdgeAdjacency>_edges                    ;
    std::vector<size_t>       _opposite                 ;///< list of all indices to opposite vertices
    size_t                    _maxMultiplicity = 0      ;///<max allowed multiplicity
    float const*              _vertices        = nullptr;///<all vertices, with redundancies
    size_t                    _nofTriangles    = 0      ;///<number of triangles
};
