#pragma once

#include <glm/glm.hpp>
#include  <vector>

namespace ge
{
   namespace util
   {
      /**
       * \brief Class for traversing a transform graph holding an actual matrix on top (back).
       * Utility class for scene graph traversal. It is used for holding the actual matrix in the node.
       * Push the matrix when entering the node, pop the matrix when leaving. The matrix on the back is automatically
       * multiplied with previous matrix when pushed.
       */
      class MatrixStack
      {
      public:
         MatrixStack();

         glm::mat4 push(glm::mat4& mat);
         glm::mat4 back() const;
         void pop();

      protected:
         std::vector<glm::mat4> stack;
      };



      inline MatrixStack::MatrixStack()
      {
         stack.push_back(glm::mat4(1.f));
      }

      /**
       * \brief Push the relative matrix on the stack.
       * The matrix should be relative to the transform's parent.
       * \param mat Matrix in the current node.
       * \return Absolute (object space to world space) matrix for this node.
       */
      inline glm::mat4 MatrixStack::push(glm::mat4& mat)
      {
         stack.push_back(stack.back() * mat);
         return stack.back();
      }

      /**
       * \brief Returns cumulative (object space to world space matrix).
       */
      inline glm::mat4 MatrixStack::back() const
      {
         return stack.back();
      }

      /**
       * \brief Pops (removes) the top matrix from stack.
       */
      inline void MatrixStack::pop()
      {
         stack.pop_back();
      }
   } // util
}// ge