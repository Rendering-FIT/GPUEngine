/*!
 * geGL library contains 10 OpenGLObject.
 * All are derived from OpenGLObject.
 * OpenGLObject class is derived from FunctionProvider that provides OpenGL.
 *
 *                        ┌────────────────────────┐
 *                        │FunctionProvider│
 *                        └────────────△───────────┘
 *                              ┌──────┴─────┐
 *                              │OpenGLObject│
 *                              └──────△─────┘
 *          ┌───────────────┬──────────┴──┬─────────────┬──────────┬─────┐
 * ┌────────┴────────┐   ┌──┴───┐   ┌─────┴─────┐   ┌───┴──┐   ┌───┴───┐ │
 * │AsynchronousQuery│   │Buffer│   │Framebuffer│   │Shader│   │Program│ │
 * └─────────────────┘   └──────┘   └───────────┘   └──────┘   └───────┘ │
 *         ┌────────────┬────────┬──────────┬─────────────┬──────────────┘
 * ┌───────┴───────┐┌───┴───┐┌───┴───┐┌─────┴──────┐┌─────┴─────┐
 * │ProgramPipeline││Texture││Sampler││Renderbuffer││VertexArray│
 * └───────────────┘└───────┘└───────┘└────────────┘└───────────┘
 *
 * geGL library also contains OpenGL debug message handling,
 * FunctionTable and FunctionProvider classes and FunctionTable decorators.
 */

#pragma once

#include<geGL/AsynchronousQuery.h>
#include<geGL/Buffer.h>
#include<geGL/Framebuffer.h>
#include<geGL/Shader.h>
#include<geGL/Program.h>
#include<geGL/VertexArray.h>
#include<geGL/ProgramPipeline.h>
#include<geGL/Texture.h>
#include<geGL/Sampler.h>
#include<geGL/Renderbuffer.h>
#include<geGL/DebugMessage.h>
#include<geGL/FunctionLoaderInterface.h>
#include<geGL/DefaultLoader.h>

namespace ge{
  namespace gl{
    /**
     * @brief This function initialises geGL library.
     * It requeires FunctionLoader object that can load OpenGL functions
     *
     * @param loader function loader (see DefaultLoader.h)
     */
    GEGL_EXPORT void init(
        std::shared_ptr<FunctionLoaderInterface>const&loader = nullptr);
    /**
     * @brief This function initialises geGL library
     * It requires getProcAddress such as SDL_GL_GetProcAddress or wglGetProcAddress
     *
     * @param getProcAddress
     */
    GEGL_EXPORT void init(GET_PROC_ADDRESS getProcAddress);
  }
}


