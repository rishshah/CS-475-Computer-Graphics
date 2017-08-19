#ifndef _GRID_HPP_
#define _GRID_HPP_

#include "../main.hpp"

namespace modellingMode {
/**
* @brief      { create line points for the grid structure and assign buffers and array object accordingly}
*/
void initgrid();
/**
 * @brief      { render grid by binding corresponding buffers and array objects}
 */
void render_grid();
}

#endif
