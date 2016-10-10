#pragma once

#include <glm/glm.hpp>
#include  <vector>

namespace ge
{
   namespace util
   {
      class MatrixStack
      {
      public:
         MatrixStack();

         glm::mat4 push(glm::mat4& mat);
         glm::mat4 back();
         void pop();

         std::vector<glm::mat4> stack;
      };



      inline MatrixStack::MatrixStack()
      {
         stack.push_back(glm::mat4());
      }

      inline glm::mat4 MatrixStack::push(glm::mat4& mat)
      {
         stack.push_back(stack.back() * mat);
         return stack.back();
      }

      inline glm::mat4 MatrixStack::back()
      {
         return stack.back();
      }

      inline void MatrixStack::pop()
      {
         stack.pop_back();
      }
   } // util
}// ge