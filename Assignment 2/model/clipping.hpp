#ifndef _CLIPPING_HPP_
#define _CLIPPING_HPP_

#include "./vertex.hpp"

int is_inside(Vertex v1, float edge, bool is_less_in, int edge_xyz);

Vertex intersection(Vertex v_in, Vertex v_out, float edge, int edge_xyz);

void clip_triangle(Vertex v1, Vertex v2, Vertex v3, float edge, bool is_less_in , int edge_xyz, std::vector<Vertex> &output);

std::vector<Vertex>  clip_for_edge(std::vector<Vertex> vList, float edge, bool is_less_in , int edge_xyz);

#endif