#include<geUtil/NamespaceWithUsers.h>

#include<algorithm>
#include<sstream>
#include<geUtil/Namespace.h>
#include<geUtil/User.h>

using namespace ge::util::sim;

NamespaceWithUsers::NamespaceWithUsers(std::string name):Namespace(name){}

void NamespaceWithUsers::registerUser  (User*user,std::string variable){
  this->_allUsers.insert(user);
  this->_variableUser[variable].insert(user);
  this->_sendUpdate[user]=false;
  this->_user2Variables[user].insert(variable);
}

void NamespaceWithUsers::unregisterUser(User*user,std::string variable){
  if(variable==""){
    this->_allUsers.erase(user);
    for(auto i:this->_user2Variables[user])
      this->_variableUser[i].erase(user);
    this->_sendUpdate.erase(user);
    this->_user2Variables.erase(user);
  }else{
    this->_variableUser[variable].erase(user);
    this->_user2Variables[user].erase(variable);
  }
}

void NamespaceWithUsers::setAsChanged(std::string variable){
  this->_changed[variable]=true;
}

void NamespaceWithUsers::sendUpdate(){
  for(auto i:this->_changed)
    if(i.second)
      for(auto j:this->_variableUser[i.first])
        this->_sendUpdate[j]=true;
  for(auto i:this->_sendUpdate)
    if(i.second)
      i.first->update();
}

