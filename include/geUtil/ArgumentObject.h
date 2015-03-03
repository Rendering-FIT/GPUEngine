#ifndef _ARGUMENTOBJECT_H_
#define _ARGUMENTOBJECT_H_

#include<iostream>
#include<vector>
#include<map>

#include <geUtil/Export.h>

namespace ge{
  namespace util{
    /**
     * @brief converts string to float with -+ inf ...
     *
     * @param s string
     *
     * @return floating point number
     */
    float atof(const char*s);
    /**
     * @brief Represents manager of program arguments
     */
    class GEUTIL_EXPORT ArgumentObject
    {
      private:
        std::vector<std::string>_argList;///<list of program arguments
      public:
        /**
         * @brief Constructor
         *
         * @param Argc   number of arguments
         * @param Argv[] arguments
         */
        ArgumentObject(int Argc,char*Argv[]);
        /**
         * @brief Gets following argument
         *
         * @param ArgName argument name
         * @param Default default returning value if the arg. is not found
         *
         * @return return next argument (1024 for -w; -w 1024)
         */
        std::string getArg(std::string ArgName,std::string Default="");
        /**
         * @brief Gets following argument in context
         *
         * @param Start starting argument of context
         * @param End ending argument of context
         * @param ArgName argument name
         * @param Default default returning value if the arg. is not found
         *
         * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
         */
        std::string getArg(std::string Start,std::string End,
            std::string ArgName,std::string Default="");
        /**
         * @brief Gets following argument and converts it to integer
         *
         * @param ArgName argument name
         * @param Default default returning value if the arg. is not found
         *
         * @return return next argument (1024 for -w; -w 1024)
         */
        int getArgi(std::string ArgName,std::string Default="");
        /**
         * @brief Gets following argument in context and converts it to integer
         *
         * @param Start starting argument of context
         * @param End ending argument of context
         * @param ArgName argument name
         * @param Default default returning value if the arg. is not found
         *
         * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
         */
        int getArgi(std::string Start,std::string End,
            std::string ArgName,std::string Default="");
        /**
         * @brief Gets following argument and converts it to float
         *
         * @param ArgName argument name
         * @param Default default returning value if the arg. is not found
         *
         * @return return next argument (1024 for -w; -w 1024)
         */
        float getArgf(std::string ArgName,std::string Default="");
        /**
         * @brief Gets following argument in context and converts it to float
         *
         * @param Start starting argument of context
         * @param End ending argument of context
         * @param ArgName argument name
         * @param Default default returning value if the arg. is not found
         *
         * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
         */
        float getArgf(std::string Start,std::string End,
            std::string ArgName,std::string Default="");

        /**
         * @brief Is argument present
         *
         * @param ArgName argument name
         *
         * @return return true if the argument is used
         */
        bool isPresent(std::string ArgName);
        /**
         * @brief Is arguemnt present in context
         *
         * @param Start starting argument of context
         * @param End ending argument of context
         * @param ArgName argment name
         *
         * @return true for -h in: -foo -gostart -bla -h -jojo -goend
         */
        bool isPresent(std::string Start,std::string End,std::string ArgName);
        /**
         * @brief Gets number of arguments in context
         *
         * @param Start starting argument of context
         * @param End ending arguement of context
         *
         * @return 3 in: -foo -blastart -a -b -c -blaend
         */
        unsigned getContextLength(std::string Start,std::string End);
        /**
         * @brief Gets argument in context by index
         *
         * @param Start starting argument of context
         * @param End endif argument of context
         * @param Index index of argument in context
         * @param Default default value of argument
         *
         * @return g for 2 in: -foo -hahastart a b g d -hahaend
         */
        std::string getArg(std::string Start,std::string End,
            unsigned Index,std::string Default="");
        int getArgi(std::string Start,std::string End,
            unsigned Index,std::string Default="");
        float getArgf(std::string Start,std::string End,
            unsigned Index,std::string Default="");
    };
  }//util
}//ge

#endif//_ARGUMENTOBJECT_H_
