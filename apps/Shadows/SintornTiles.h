#pragma once

#include<vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

/**
 * @brief This function finds out the best distribution of size among tiles
 *
 * @param TileSize output tile sizes 
 * @param WindowSize windows size
 * @param WavefrontSize wavefront size usually 32 or 64
 *
 * @return returns number of levels
 */
unsigned chooseTileSizes(std::vector<glm::uvec2>&tileSize,glm::uvec2 const&windowSize,uint32_t wavefrontSize);


