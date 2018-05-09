#ifndef GE_RG_ATTRIB_CONFIG_H
#define GE_RG_ATTRIB_CONFIG_H

#include <list>
#include <map>
#include <memory>
#include <vector>
#include <geRG/Export.h>
#include <geRG/AttribType.h>


namespace ge
{
   namespace rg
   {
      class AttribStorage;
      class Mesh;
      class RenderingContext;
      typedef uint32_t AttribConfigId;  ///< \brief Integer-based type for the most frequently used attribute configurations.


      /** AttribConfig class represents particular OpenGL attribute configuration.
       *
       *  Each mesh uses particular attribute configuration. For instance,
       *  it uses coordinates on the attribute index 0 using vector of three floats,
       *  color attribute on the index 1 using vector of four unsigned bytes,
       *  and indexing (e.g. element buffer object is used).
       *
       *  Each attribute has its index and AttribType. AttribConfig holds the vector
       *  of these attribute configurations, the flag whether indexing (element buffer
       *  object) are used, and AttribConfigId.
       *  AttribConfigId is an integer value for the most typically used attribute
       *  configurations. It is used for fast comparison, lookups, etc.
       *  See AttribConfig::Configuration for more details.
       *
       *  AttribConfig class by itself is just a proxy object to AttribConfig::Instance
       *  that carries all the data of AttribConfig. AttribConfigs points
       *  to the same AttribConfig::Instance if they share the same attribute
       *  configuration (\sa AttribConfig::Configuration) in the same RenderingContext.
       *  AttribConfig::Instance maintains the reference counter that is incremented
       *  and decremented by AttribConfig objects. If there are no more AttribConfig
       *  objects, AttribConfig::Instance is released.
       */
      class GERG_EXPORT AttribConfig {
      public:

         /** AttribConfig::Configuration represents the complete information about
          *  the configuration of attributes.
          *
          *  It includes number of attributes, their types, whether EBO (Element Buffer Object) is used
          *  and id for quick Configuration comparison and lookup. */
         struct Configuration {

            std::vector<AttribType> attribTypes;  ///< Type of each active attribute. \sa AttribType
            bool ebo;                             ///< Indicates whether element buffer object is used or not.
            AttribConfigId id;                    ///< \brief Id of one of the frequently used attribute configurations.

            inline Configuration() = default;     ///< Default constructor. Does nothing. The user is responsible for the object initialization.
            inline Configuration(const std::vector<AttribType>& attribTypes,bool ebo);  ///< \brief Constructs object from parameters.
            inline Configuration(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id);  ///< \brief Construct object from parameters.
            inline Configuration(const Configuration &c);  ///< Copy constructor.
            inline void updateId();  ///< \brief Updates id member of the object.
            inline bool operator==(const Configuration &rhs) const;  ///< Comparison operator.
            inline bool operator!=(const Configuration &rhs) const;  ///< Comparison operator.
            inline bool operator<=(const Configuration &rhs) const;  ///< Comparison operator.
            inline bool operator>=(const Configuration &rhs) const;  ///< Comparison operator.
            inline bool operator< (const Configuration &rhs) const;  ///< Comparison operator.
            inline bool operator> (const Configuration &rhs) const;  ///< Comparison operator.

         };

         struct Instance;
         typedef std::vector<AttribType> AttribTypeList;  ///< Number of attributes and their types.
         typedef std::map<Configuration,Instance*> InstanceList;  ///< Map of AttribConfig::Instances used inside RenderingContext class.
         typedef std::list<std::shared_ptr<AttribStorage>> AttribStorageList;  ///< List of AttribStorages used inside AttribConfig::Instance class.

         /** AttribConfig::Instance holds all the data of AttribConfig class.
          *  AttribConfig::Instance object is singleton-style object.
          *  If more AttribConfigs share the same configuration
          *  within the same RenderingContext,
          *  they points to the same AttribConfig::Instance object.
          */
         struct GERG_EXPORT Instance {

            int referenceCounter;
            Configuration configuration;
            RenderingContext *renderingContext;
            InstanceList::iterator selfIterator;
            mutable AttribStorageList attribStorageList; // private storages are on the end

            inline void ref();
            inline void unref();
            void destroy();

            inline AttribConfig createAttribConfig();
            void deleteAllAttribStorages();
            inline void detachFromRenderingContext();

            inline Instance();
            inline Instance(int referenceCounter);
            inline Instance(const Configuration& configuration,RenderingContext *rc,InstanceList::iterator it);
            virtual ~Instance();

            static Instance invalid;

         };

      protected:

         Instance* _instance;

      public:

         inline AttribConfig();
         inline AttribConfig(const AttribConfig& ac);
         inline AttribConfig(Instance *instance);
         inline AttribConfig(const Configuration& config,RenderingContext *rc);
         inline AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo);
         inline AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                             AttribConfigId id);
         inline AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                             RenderingContext *rc);
         inline AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,
                             AttribConfigId id,RenderingContext *rc);
         virtual ~AttribConfig();

         inline const std::vector<AttribType>& attribTypes() const;
         inline bool ebo() const;
         inline AttribConfigId id() const;

         inline const Configuration& configuration() const;
         inline RenderingContext* renderingContext() const;
         inline AttribStorageList& getAttribStorageList() const;
         inline const Instance* getConfigurationInstance() const;

         static AttribConfigId getId(const std::vector<AttribType>& attribTypes,bool ebo);

         inline AttribConfig& operator=(const AttribConfig& ac);
         inline bool operator==(const AttribConfig& rhs) const;
         inline bool operator!=(const AttribConfig& rhs) const;
         inline bool operator<=(const AttribConfig& rhs) const;
         inline bool operator>=(const AttribConfig& rhs) const;
         inline bool operator<(const AttribConfig& rhs) const;
         inline bool operator>(const AttribConfig& rhs) const;

         static const AttribConfig invalid;
      };

   }
}



// inline methods
#include <geRG/AttribStorage.h>
#include <geRG/RenderingContext.h>

namespace ge
{
   namespace rg
   {
      inline AttribConfig::Configuration::Configuration(const std::vector<AttribType>& a,bool e)
         : attribTypes(a), ebo(e), id(AttribConfig::getId(attribTypes,ebo))  {}
      inline AttribConfig::Configuration::Configuration(const std::vector<AttribType>& a,bool e,AttribConfigId i)
         : attribTypes(a), ebo(e), id(i)  {}
      inline AttribConfig::Configuration::Configuration(const Configuration& c)
         : attribTypes(c.attribTypes), ebo(c.ebo), id(c.id)  {}
      inline void AttribConfig::Configuration::updateId()  { id=AttribConfig::getId(attribTypes,ebo); }
      inline bool AttribConfig::Configuration::operator==(const Configuration& rhs) const  { return id!=0||rhs.id!=0 ? id==rhs.id : ebo==rhs.ebo&&attribTypes==rhs.attribTypes; }
      inline bool AttribConfig::Configuration::operator!=(const Configuration& rhs) const  { return id!=0||rhs.id!=0 ? id!=rhs.id : ebo!=rhs.ebo||attribTypes!=rhs.attribTypes; }
      inline bool AttribConfig::Configuration::operator<=(const Configuration& rhs) const  { return id!=0||rhs.id!=0 ? id<=rhs.id : ebo!=rhs.ebo?ebo<rhs.ebo:attribTypes<=rhs.attribTypes; }
      inline bool AttribConfig::Configuration::operator>=(const Configuration& rhs) const  { return id!=0||rhs.id!=0 ? id>=rhs.id : ebo!=rhs.ebo?ebo>rhs.ebo:attribTypes>=rhs.attribTypes; }
      inline bool AttribConfig::Configuration::operator<(const Configuration& rhs) const  { return id!=0||rhs.id!=0 ? id<rhs.id : ebo!=rhs.ebo?ebo<rhs.ebo:attribTypes<rhs.attribTypes; }
      inline bool AttribConfig::Configuration::operator>(const Configuration& rhs) const  { return id!=0||rhs.id!=0 ? id>rhs.id : ebo!=rhs.ebo?ebo>rhs.ebo:attribTypes>rhs.attribTypes; }

      inline void AttribConfig::Instance::ref()  { referenceCounter++; }
      inline void AttribConfig::Instance::unref()  { if(--referenceCounter==0) destroy(); }
      inline AttribConfig AttribConfig::Instance::createAttribConfig()  { return AttribConfig(this); }
      inline void AttribConfig::Instance::detachFromRenderingContext()  { if(renderingContext) renderingContext->removeAttribConfigInstance(selfIterator); }
      inline AttribConfig::Instance::Instance() : referenceCounter(0), renderingContext(nullptr) {}
      inline AttribConfig::Instance::Instance(int refCounter) : referenceCounter(refCounter), renderingContext(nullptr) {}
      inline AttribConfig::Instance::Instance(const Configuration& config,RenderingContext *rc,InstanceList::iterator it) : referenceCounter(0), configuration(config), renderingContext(rc), selfIterator(it) {}

      inline AttribConfig::AttribConfig() : _instance(&Instance::invalid) { _instance->ref(); }
      inline AttribConfig::AttribConfig(const AttribConfig& ac)  { _instance=ac._instance; _instance->ref(); }
      inline AttribConfig::AttribConfig(Instance *instance)  { _instance=instance; _instance->ref(); }
      inline AttribConfig::AttribConfig(const AttribConfig::Configuration& config,RenderingContext *rc)
         { _instance=rc->getAttribConfigInstance(config); _instance->ref(); }
      inline AttribConfig::AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo)
         : AttribConfig(AttribConfig::Configuration(attribTypes,ebo),RenderingContext::current().get()) {}
      inline AttribConfig::AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
         : AttribConfig(AttribConfig::Configuration(attribTypes,ebo,id),RenderingContext::current().get()) {}
      inline AttribConfig::AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,RenderingContext *rc)
         : AttribConfig(AttribConfig::Configuration(attribTypes,ebo),rc) {}
      inline AttribConfig::AttribConfig(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id,RenderingContext *rc)
         : AttribConfig(AttribConfig::Configuration(attribTypes,ebo,id),rc) {}

      inline const std::vector<AttribType>& AttribConfig::attribTypes() const  { return _instance->configuration.attribTypes; }
      inline bool AttribConfig::ebo() const  { return _instance->configuration.ebo; }
      inline AttribConfigId AttribConfig::id() const  { return _instance->configuration.id; }

      inline const AttribConfig::Configuration& AttribConfig::configuration() const  { return _instance->configuration; }
      inline RenderingContext* AttribConfig::renderingContext() const  { return _instance->renderingContext; }
      inline AttribConfig::AttribStorageList& AttribConfig::getAttribStorageList() const  { return _instance->attribStorageList; }
      inline const AttribConfig::Instance* AttribConfig::getConfigurationInstance() const  { return _instance; }

      inline AttribConfig& AttribConfig::operator=(const AttribConfig &ac)  { _instance->unref(); _instance=ac._instance; _instance->ref(); return *this; }
      inline bool AttribConfig::operator==(const AttribConfig &rhs) const  { return _instance==rhs._instance; }
      inline bool AttribConfig::operator!=(const AttribConfig &rhs) const  { return _instance!=rhs._instance; }
      inline bool AttribConfig::operator<=(const AttribConfig &rhs) const  { return _instance==rhs._instance || _instance->configuration<rhs._instance->configuration; }
      inline bool AttribConfig::operator>=(const AttribConfig &rhs) const  { return _instance==rhs._instance || _instance->configuration>rhs._instance->configuration; }
      inline bool AttribConfig::operator<(const AttribConfig &rhs) const  { return _instance!=rhs._instance && _instance->configuration<rhs._instance->configuration; }
      inline bool AttribConfig::operator>(const AttribConfig &rhs) const  { return _instance!=rhs._instance && _instance->configuration>rhs._instance->configuration; }

   }
}

#endif // GE_RG_ATTRIB_CONFIG_H
