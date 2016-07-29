#pragma once

#define REMOVE_RETURN(name) std::string(name).substr(std::string(name).rfind(" ")+1)
#define REMOVE_ARGS(name) std::string(name).substr(0,std::string(name).find("("))

#define GE_CORE_FCENAME REMOVE_RETURN(REMOVE_ARGS(__PRETTY_FUNCTION__))
