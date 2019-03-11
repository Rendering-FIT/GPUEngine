#include "OctreeSidesDrawer.hpp"

#include <geGL/StaticCalls.h>

void OctreeSidesDrawer::drawSides(const glm::mat4& mvp, const glm::vec4& light)
{
	const auto cellIndex = _octreeVisitor->getLowestNodeIndexFromPoint(glm::vec3(light));

	if (cellIndex<0)
	{
		static bool printOnce = false;

		if (!printOnce)
		{
			std::cout << "Light " << light.x << ", " << light.y << ", " << light.z << " is out of range\n";
			//printOnce = true;
		}
	}
	else
	{
		static bool printOnce = false;

		if (!printOnce)
		{
			std::cout << "Light " << light.x << ", " << light.y << ", " << light.z << std::endl;
			std::cout << "Cell index: " << cellIndex << std::endl;
			printOnce = true;
		}
		if (m_compressionLevel == 0)
		{
			_getPotentialSilhouetteEdgesNoCompress(cellIndex);
			//_getPotentialSilhouetteEdgesNoCompress2(cellIndex);
		}
		else if(m_compressionLevel==1)
		{
			_getPotentialSilhouetteEdgesGpu8bit(cellIndex);
		}
		else
		{
			_getPotentialSilhouetteEdgesGpu3(cellIndex);
		}

		if (_silhouetteDrawingMethod == DrawingMethod::CS && _potentialDrawingMethod == DrawingMethod::CS)
			_drawSidesCS(mvp, light);
		else
		{
			switch (_silhouetteDrawingMethod)
			{
			case DrawingMethod::GS:
				_drawSidesFromSilhouetteEdgesGS(mvp, light); break;
			case DrawingMethod::TS:
				_drawSidesFromSilhouetteEdgesTS(mvp, light); break;
			case DrawingMethod::CS:
				_drawSidesFromSilhouetteEdgesCS(mvp, light); break;
			}

			switch (_potentialDrawingMethod)
			{
			case DrawingMethod::GS:
				_drawSidesFromPotentialEdgesGS(mvp, light); break;
			case DrawingMethod::TS:
				_drawSidesFromPotentialEdgesTS(mvp, light); break;
			case DrawingMethod::CS:
				_drawSidesFromPotentialEdgesCS(mvp, light); break;
			}
		}
	}

	_lastFrameCellIndex = cellIndex;
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	//if (_timer) _timer->stamp("");

	assert(GL_NO_ERROR == ge::gl::glGetError());

	_silhouetteSidesTsProgram->use();
	_silhouetteSidesTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);

	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	//if (_timer) _timer->stamp("SilhouetteEdges");

	assert(GL_NO_ERROR == ge::gl::glGetError());
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	//if (_timer) _timer->stamp("");

	_silhouetteSidesGsProgram->use();
	_silhouetteSidesGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_POINTS, 0);
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);

	_dummyVAO->unbind();

	//if (_timer) _timer->stamp("SilhouetteEdges");
}

void OctreeSidesDrawer::_drawSidesFromSilhouetteEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	//if (_timer) _timer->stamp("");
	_generateSidesFromSilhouetteCS();
	//if (_timer) _timer->stamp("SilhouetteEdges");
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_silhouetteSidesCsVAO->bind();
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	_silhouetteSidesCsVAO->unbind();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesTS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	//if (_timer) _timer->stamp("");

	assert(ge::gl::glGetError() == GL_NO_ERROR);

	_potentialTsProgram->use();
	_potentialTsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 1);

	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, 0);
	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();

	//if (_timer) _timer->stamp("PotentialEdges");

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesGS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	assert(ge::gl::glGetError() == GL_NO_ERROR);

	//if (_timer) _timer->stamp("");
	_potentialGsProgram->use();
	_potentialGsProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_dummyVAO->bind();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_POINTS, nullptr);
	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);

	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);

	_dummyVAO->unbind();

	//if (_timer) _timer->stamp("PotentialEdges");

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_drawSidesFromPotentialEdgesCS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	//if (_timer) _timer->stamp("");
	_generateSidesFromPotentialCS(lightPos);
	//if (_timer) _timer->stamp("PotentialEdges");
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_potentialSidesCsVAO->bind();
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_indirectDrawBufferPotentialCS->unbind(GL_DRAW_INDIRECT_BUFFER);
	_potentialSidesCsVAO->unbind();

	assert(ge::gl::glGetError() == GL_NO_ERROR);
}

void OctreeSidesDrawer::_generateSidesFromPotentialCS(const glm::vec4& lightPos)
{
	const uint32_t zero = 0;
	_indirectDrawBufferPotentialCS->setData(&zero, sizeof(uint32_t));

	_testAndGenerateSidesProgram->use();
	_testAndGenerateSidesProgram->set4fv("lightPosition", glm::value_ptr(lightPos));
	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_potentialEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->bindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_nofEdgesPotSil->bindRange(GL_SHADER_STORAGE_BUFFER, 5, 0, sizeof(uint32_t));
	_indirectDispatchCsPotential->bind(GL_DISPATCH_INDIRECT_BUFFER);

	ge::gl::glDispatchComputeIndirect(0);

	_indirectDispatchCsPotential->unbind(GL_DISPATCH_INDIRECT_BUFFER);
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_gpuEdges->_oppositeVertices->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_edgesIdsToTestAndGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_potentialEdgeCsVBO->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_indirectDrawBufferPotentialCS->unbindBase(GL_SHADER_STORAGE_BUFFER, 4);
	_nofEdgesPotSil->unbindRange(GL_SHADER_STORAGE_BUFFER, 5);
}

void OctreeSidesDrawer::_generateSidesFromSilhouetteCS()
{
	const uint32_t zero = 0;
	assert(GL_NO_ERROR == ge::gl::glGetError());
	_indirectDrawBufferSilhouetteCS->setData(&zero, sizeof(uint32_t));

	_generateSidesProgram->use();

	_gpuEdges->_edges->bindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_nofEdgesPotSil->bindRange(GL_SHADER_STORAGE_BUFFER, 4, 8*sizeof(uint32_t), sizeof(uint32_t));
	_indirectDispatchCsSilhouette->bind(GL_DISPATCH_INDIRECT_BUFFER);

	ge::gl::glDispatchComputeIndirect(0);

	_indirectDispatchCsSilhouette->unbind(GL_DISPATCH_INDIRECT_BUFFER);
	_gpuEdges->_edges->unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
	_edgesIdsToGenerate->unbindBase(GL_SHADER_STORAGE_BUFFER, 1);
	_silhouetteEdgeCsVBO->unbindBase(GL_SHADER_STORAGE_BUFFER, 2);
	_indirectDrawBufferSilhouetteCS->unbindBase(GL_SHADER_STORAGE_BUFFER, 3);
	_nofEdgesPotSil->unbindRange(GL_SHADER_STORAGE_BUFFER, 4);

	assert(GL_NO_ERROR == ge::gl::glGetError());
}

void OctreeSidesDrawer::_drawSidesCS(const glm::mat4& mvp, const glm::vec4& lightPos)
{
	assert(GL_NO_ERROR == ge::gl::glGetError());
	//if (_timer) _timer->stamp("");
	_generateSidesFromPotentialCS(lightPos);
	//if (_timer) _timer->stamp("PotentialEdges");
	_generateSidesFromSilhouetteCS();
	//if (_timer) _timer->stamp("SilhouetteEdges");
	ge::gl::glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

	_drawSidesProgram->use();
	_drawSidesProgram->setMatrix4fv("mvp", glm::value_ptr(mvp))->set4fv("lightPosition", glm::value_ptr(lightPos));

	_potentialSidesCsVAO->bind();
	_indirectDrawBufferPotentialCS->bind(GL_DRAW_INDIRECT_BUFFER);

	ge::gl::glPatchParameteri(GL_PATCH_VERTICES, 2);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_silhouetteSidesCsVAO->bind();
	_indirectDrawBufferSilhouetteCS->bind(GL_DRAW_INDIRECT_BUFFER);
	ge::gl::glDrawArraysIndirect(GL_PATCHES, nullptr);

	_silhouetteSidesCsVAO->unbind();
	_indirectDrawBufferSilhouetteCS->unbind(GL_DRAW_INDIRECT_BUFFER);

	assert(GL_NO_ERROR == ge::gl::glGetError());
}