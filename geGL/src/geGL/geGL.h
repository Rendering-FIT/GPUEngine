/*!
 * geGL library contains 10 OpenGLObject.
 * All are derived from OpenGLObject.
 * OpenGLObject class is derived from FunctionProvider that provides OpenGL.
 *
 *                                ┌───────┐
 *                                │Context│
 *                                └────△──┘
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
     * @brief This function returns pointers to opengl functions
     *
     * @param name name of opengl function
     *
     * @return pointer to opengl function
     */
    GEGL_EXPORT void*getProcAddress(char const*name);

    /**
     * @brief This function initialises geGL library.
     * It requires FunctionLoader object that can load OpenGL functions
     *
     * @param loader function loader (see DefaultLoader.h)
     */
    GEGL_EXPORT void init(
        std::shared_ptr<FunctionLoaderInterface>const&loader);
    /**
     * @brief This function initialises geGL library
     * It requires getProcAddress such as SDL_GL_GetProcAddress or wglGetProcAddress or glxGetProcAddress ...
     *
     * @param getProc function that takes name of opengl function and returns its address
     */
    GEGL_EXPORT void init(GET_PROC_ADDRESS getProc = getProcAddress);

  }
}


