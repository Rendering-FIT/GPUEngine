#include <unordered_set>

#include <GPUEngine/geCore/InitAndFinalize.h>

using namespace ge::core;


static int niftyCounter; // according to standard,
      // this is initialized to zero before any global object constructor is called:
      // Citing ($3.6.2/1): "Objects with static storage duration (3.7.1) shall
      // be zero-initialized (8.5) before any other initialization takes place."
      // Do not try to improve the code and make it "niftyCounter=0;" as
      // this may theoretically postpone the initialization to later time.


typedef std::unordered_set<void (*)()> FceSet;


static FceSet& getInitSet()
{
   static FceSet s;
   return s;
}


static FceSet& getFinalizeSet()
{
   static FceSet s;
   return s;
}


InitAndFinalize::InitAndFinalize(void (*initFce)(),void (*finalizeFce)())
{
   // increment global counter
   ++niftyCounter;

   // call initFce
   // but do it only on the first such request
   // (InitAndFinalize object is instantiated in header (that is how NiftyCounter idiom works)
   // and number times it is included, it is instantiated with the same values)
   if(initFce) {
      auto r=getInitSet().insert(initFce);
      if(r.second)
         initFce();
   }

   // register finalizeFce
   if(finalizeFce)
      getFinalizeSet().insert(finalizeFce);
}


InitAndFinalize::~InitAndFinalize()
{
   if(--niftyCounter==0)
   {
      auto& s=getFinalizeSet();
      for(void (*f)():s)
         f();
   }
}
