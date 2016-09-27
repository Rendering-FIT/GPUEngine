#pragma once

#include<geAd/Export.h>
#include<iostream>

namespace ge{
  namespace ad{

    /**
     * @brief This class represents loader of dynamic libraries
     * It can be used for loading libraries at runtime
     */
    class GEAD_EXPORT LibraryLoader{
      public:
        /**
         * @brief Constructor
         */
        LibraryLoader(){}
        /**
         * @brief Destructor - it closes every open library
         */
        virtual ~LibraryLoader(){}
        /**
         * @brief it loads library by its name
         *
         * @param name name of library with path
         *
         * @return index of loaded library
         */
        virtual std::size_t load(std::string name)=0;
        /**
         * @brief it loads function from library
         *
         * @param i index of loaded library that is returned by load(name)
         * @param name name of function inside loaded library
         *
         * @return funtion pointer
         */
        virtual void* get(std::size_t i,std::string name)=0;
    };

    /**
     * @brief This function is factory of LibraryLoader
     * it hides implementation details and os dependency as well
     *
     * @return LibraryLoader
     */
    GEAD_EXPORT LibraryLoader*getLoader();
  }
}
