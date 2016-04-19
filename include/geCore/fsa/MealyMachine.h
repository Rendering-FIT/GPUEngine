#pragma once

#include<vector>
#include<tuple>
#include<memory>
#include<limits>
#include<geCore/Export.h>

namespace ge{
  namespace core{
    class TransitionChooser;

    class GECORE_EXPORT MealyMachine{
      public:
        using StateIndex       = size_t;
        using BasicUnit        = uint8_t;
        using TransitionSymbol = BasicUnit const*;
        using CallbackData     = void*;
        using Callback         = void(*)(MealyMachine*,CallbackData const&);
        MealyMachine(size_t largestState);
        virtual ~MealyMachine();

        StateIndex addState(std::shared_ptr<TransitionChooser>const&chooser);
        void addTransition(
            StateIndex       const&from              ,
            TransitionSymbol const&symbol            ,
            StateIndex       const&to                ,
            Callback         const&callback = nullptr,
            CallbackData     const&data     = nullptr);
        void addElseTransitions(
            StateIndex   const&from              ,
            StateIndex   const&to                ,
            Callback     const&callback = nullptr,
            CallbackData const&data     = nullptr);
        void addEOFTransition(
            StateIndex   const&from              ,
            Callback     const&callback = nullptr,
            CallbackData const&data     = nullptr);
        virtual void begin();
        virtual bool parse(BasicUnit const*data,size_t size);
        virtual bool end();
        inline size_t     const&getReadingPosition()const;
        inline BasicUnit  const*getCurrentSymbol()const;
        inline StateIndex const&getCurrentState()const;
        inline void dontMove();
        virtual std::string str()const;
      protected:
        using TransitionSymbolIndex = size_t;
        using CallbackWithData      = std::tuple<Callback,CallbackData>;
        using Transition            = std::tuple<StateIndex,CallbackWithData>;
        using TransitionVector      = std::vector<Transition>;
      public:
        using TransitionIndex       = TransitionVector::size_type;
        static const TransitionIndex nonexistingTransition;
      protected:
        using State = std::tuple<
          TransitionVector,
          std::shared_ptr<TransitionChooser>,
          std::shared_ptr<Transition>,
          std::shared_ptr<Transition>>;
      protected:
        enum CallbackWithDataParts{
          CALLBACK = 0,
          DATA     = 1,
        };
        enum TransitionParts{
          STATE_INDEX        = 0,
          CALLBACK_WITH_DATA = 1,
        };
        enum StateParts{
          TRANSITIONS     = 0,
          CHOOSER         = 1,
          ELSE_TRANSITION = 2,
          EOF_TRANSITION  = 3,
        };
        inline void _call(Transition const&transitions);
        inline bool _nextState(State const&state);
        bool                   _dontMove          = false  ;
        size_t                 _readingPosition   = 0      ;
        BasicUnit const*       _currentSymbol     = nullptr;
        size_t                 _currentSymbolSize = 0      ;
        std::vector<State>     _states                     ;
        StateIndex             _currentState      = 0      ;
        std::vector<BasicUnit> _symbolBuffer               ;
        TransitionSymbolIndex  _symbolBufferIndex = 0      ;
    };

    inline size_t const& MealyMachine::getReadingPosition()const{
      return this->_readingPosition;
    }

    inline MealyMachine::BasicUnit const*MealyMachine::getCurrentSymbol()const{
      return this->_currentSymbol;
    }

    inline MealyMachine::StateIndex const&MealyMachine::getCurrentState()const{
      return this->_currentState;
    }

    inline void MealyMachine::dontMove(){
      this->_dontMove = true;
    }
  }
}
