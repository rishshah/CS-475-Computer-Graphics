#include "./clipping.hpp"

/**
 * @brief      Determines if v1 is inside the clipping edge.
 *
 * @param[in]  v1               The v 1
 * @param[in]  edge             The edge
 * @param[in]  is_less_in       Indicates if less in
 * @param[in]  edge_xyz  Indicates edge plane direction	
 *
 * @return     1 if inside, 0 otherwise.
 */

int is_inside(Vertex v1, float edge, bool is_less_in, int edge_xyz) {
	bool ans = false;
	if (edge_xyz == 1) {
		if (is_less_in) {
			ans = v1.position.x <= edge;
		}
		else {
			ans = v1.position.x >= edge;
		}
	}
	else if(edge_xyz == 2){
		if (is_less_in) {
			ans = v1.position.y <= edge;
		}
		else {
			ans = v1.position.y >= edge;
		}
	}
	else if(edge_xyz == 3){
		if (is_less_in) {
			ans = v1.position.z <= edge;
		}
		else {
			ans = v1.position.z >= edge;
		}
	}
	if(ans)
		return 1;
	else
		return 0;
}

/**
 * @brief      Calulate the interection vertex between line of 2 vertices and a clipping edge
 *
 * @param[in]  v_in             The v in
 * @param[in]  v_out            The v out
 * @param[in]  edge             The edge
 * @param[in]  edge_xyz  Indicates edge plane direction
 *
 * @return     Intersect vertex with correct interpolated z val and colors
 */
Vertex intersection(Vertex v_in, Vertex v_out, float edge, int edge_xyz){
	if(edge_xyz == 1){
		float pos_y = v_in.position.y  + (v_out.position.y - v_in.position.y) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);
		float pos_z = v_in.position.z  + (v_out.position.z - v_in.position.z) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);
		
		float col_r = v_in.color.x  + (v_out.color.x - v_in.color.x) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x); 
		float col_g = v_in.color.y  + (v_out.color.y - v_in.color.y) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);
		float col_b = v_in.color.z  + (v_out.color.z - v_in.color.z) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);

		return Vertex(glm::vec3(edge, pos_y, pos_z),glm::vec3(col_r, col_g, col_b));
		// return Vertex(glm::vec3(edge, pos_y, pos_z),v_out.color);
	}
	else if(edge_xyz == 2){
		float pos_x = v_in.position.x  + (v_out.position.x - v_in.position.x) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);
		float pos_z = v_in.position.z  + (v_out.position.z - v_in.position.z) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);
		
		float col_r = v_in.color.x  + (v_out.color.x - v_in.color.x) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y); 
		float col_g = v_in.color.y  + (v_out.color.y - v_in.color.y) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);
		float col_b = v_in.color.z  + (v_out.color.z - v_in.color.z) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);

		return Vertex(glm::vec3(pos_x, edge, pos_z),glm::vec3(col_r, col_g, col_b));
		// return Vertex(glm::vec3(pos_x, edge, pos_z),v_out.color);	
	}
	else if(edge_xyz == 3){
		float pos_x = v_in.position.x  + (v_out.position.x - v_in.position.x) * (edge - v_in.position.z)/(v_out.position.z - v_in.position.z);
		float pos_y = v_in.position.y  + (v_out.position.y - v_in.position.y) * (edge - v_in.position.z)/(v_out.position.z - v_in.position.z);
		
		float col_r = v_in.color.x  + (v_out.color.x - v_in.color.x) * (edge - v_in.position.z)/(v_out.position.z - v_in.position.z); 
		float col_g = v_in.color.y  + (v_out.color.y - v_in.color.y) * (edge - v_in.position.z)/(v_out.position.z - v_in.position.z);
		float col_b = v_in.color.z  + (v_out.color.z - v_in.color.z) * (edge - v_in.position.z)/(v_out.position.z - v_in.position.z);

		return Vertex(glm::vec3(pos_x, pos_y, edge),glm::vec3(col_r, col_g, col_b));
		// return Vertex(glm::vec3(pos_x, edge, pos_z),v_out.color);	
	}
}

/**
 * @brief      Clip a triangle given by three vertices
 *
 * @param[in]  v1               The first vertex of triangle
 * @param[in]  v2               The second vertex of triangle
 * @param[in]  v3               The third vertex of triangle
 * @param[in]  edge             The edge to be clipped about
 * @param      output           The output vertex list that will be appended with new clipped vertices
 */
void clip_triangle(Vertex v1, Vertex v2, Vertex v3, float edge, bool is_less_in , int edge_xyz, std::vector<Vertex> &output) {
	int mask = is_inside(v1, edge, is_less_in, edge_xyz);
	mask <<= 1;
	mask |= is_inside(v2, edge, is_less_in, edge_xyz);
	mask <<= 1;
	mask |= is_inside(v3, edge, is_less_in, edge_xyz);
	// mask = v1 | v2 | v3 
	switch(mask){
		case 0 :
			break;
		case 1 :
			output.push_back(intersection(v3, v1, edge, edge_xyz));
			output.push_back(intersection(v3, v2, edge, edge_xyz));
			output.push_back(v3);
			break;	
		case 2 :
			output.push_back(intersection(v2, v1, edge, edge_xyz));
			output.push_back(v2);
			output.push_back(intersection(v2, v3, edge, edge_xyz));
			break;
		case 3 :
			output.push_back(intersection(v2, v1, edge, edge_xyz));
			output.push_back(v2);
			output.push_back(v3);

			output.push_back(intersection(v3, v1, edge, edge_xyz));
			output.push_back(intersection(v2, v1, edge, edge_xyz));
			output.push_back(v3);
			break;
		
		case 4 :
			output.push_back(v1);
			output.push_back(intersection(v1, v2, edge, edge_xyz));
			output.push_back(intersection(v1, v3, edge, edge_xyz));
			break;
		case 5 :
			output.push_back(intersection(v1, v2, edge, edge_xyz));
			output.push_back(v1);
			output.push_back(v3);

			output.push_back(intersection(v3, v2, edge, edge_xyz));
			output.push_back(intersection(v1, v2, edge, edge_xyz));
			output.push_back(v3);
			break;
		
		case 6 :
			output.push_back(intersection(v1, v3, edge, edge_xyz));
			output.push_back(v1);
			output.push_back(v2);

			output.push_back(intersection(v2, v3, edge, edge_xyz));
			output.push_back(intersection(v1, v3, edge, edge_xyz));
			output.push_back(v2);
			break;
		case 7 :
			output.push_back(v1);
			output.push_back(v2);
			output.push_back(v3);
			break;
	}
}

/**
 * @brief      Clip model for a given edge of DCS(assuming DCS is a sqaure -10 -> 10 along principle axes)
 *
 * @param[in]  vList            The transformed vertices list
 * @param[in]  edge             The edge ( either x value or y value) 
 * @param[in]  is_less_in       Indicates if less value than edge considered as inside the view area
 * @param[in]  edge_xyz  		Indicates edge plane direction
 *
 * @return    New vertex_list of cliped verties
 */
std::vector<Vertex>  clip_for_edge(std::vector<Vertex> vList, float edge, bool is_less_in , int edge_xyz) {
	std::vector<Vertex> output(0);
	for (int i = 0; i < vList.size(); i += 3) {
		clip_triangle(vList[i], vList[i + 1], vList[i + 2], edge, is_less_in, edge_xyz, output);
	}
	return output;
}
