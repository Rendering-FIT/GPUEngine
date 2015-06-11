namespace ge
{
   namespace core
   {

      template<typename T>
      class InitAndFinalize {
      protected:

         static int niftyCounter;

      public:

         inline InitAndFinalize()
         {
            if(++niftyCounter==1)
               T::init();
         }

         ~InitAndFinalize()
         {
            if(--niftyCounter==0)
               T::finalize();
         }

      };


      template<typename T> int InitAndFinalize<T>::niftyCounter; // according to standard,
                     // this is initialized to zero before any global object constructor is called:
                     // Citing ($3.6.2/1): "Objects with static storage duration (3.7.1) shall
                     // be zero-initialized (8.5) before any other initialization takes place."
                     // Do not try to improve the code and make it "niftyCounter=0;" as
                     // this may theoretically postpone the initialization to later time.

   }
}
