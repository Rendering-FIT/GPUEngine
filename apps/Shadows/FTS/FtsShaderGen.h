#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

namespace ge 
{
    namespace gl 
    {
        class Program;
    }
}


class FtsShaderGen
{
public:

    std::unique_ptr<ge::gl::Program> GetZbufferFillProgram(glm::uvec3 const& bufferDims);
    std::unique_ptr<ge::gl::Program> GetZbufferTraversalProgram(glm::uvec3 const& bufferDims);

private:

    std::string GetVS_Fill() const;
    std::string GetFS_Fill(glm::uvec3 const& bufferDims) const;

    std::string GetVS_Traversal() const;
    std::string GetFS_Traversal(glm::uvec3 const& bufferDims) const;
};