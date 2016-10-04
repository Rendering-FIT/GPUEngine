#pragma once

#include<vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

/**
 * @brief This function finds out the best distribution of tileDivisibilities among tiles
 *
 * @param tileDivisibility output tile divisibilities
 * @param windowSize windows size
 * @param wgs absolute work-group size = tileDivisibility[i].x*tileDivisibility[i].y
 */
void chooseTileSizes(std::vector<glm::uvec2>&tileDivisibility,glm::uvec2 const&windowSize,size_t wgs);


