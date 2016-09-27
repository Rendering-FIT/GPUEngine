#pragma once

#include<geAd/Export.h>
#include<geAd/LibraryLoader/LibraryLoader.h>
#include<geDE/TypeRegister.h>
#include<geAd/LibraryLoader/RuntimeClassInterface.h>

namespace ge{
  namespace ad{
    /**
     * @brief This class loads object that is created by factory function getObject inside
     * dynamic library
     * It can be used for easy runtime creation of new object from dynamic library
     */
    class GEAD_EXPORT ObjectLoader: public LibraryLoader{
      public:
        /**
         * @brief This function returns object that is created by factory function getObject inside lib
         * dynamic library
         *
         * @param lib name of library
         *
         * @return created object
         */
        void*getObject(std::string lib);
        /**
         * @brief This function returns runtime class interface that is created by factory function getInterface inside lib
         *
         * @param lib name of library
         * @param typeRegister type register
         *
         * @return created interface
         */
        RuntimeClassInterface*getInterface(
            std::string lib,
            std::shared_ptr<de::TypeRegister>&typeRegister);
    };
  }
}
