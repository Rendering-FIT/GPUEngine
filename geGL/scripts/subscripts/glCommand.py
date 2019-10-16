#!/usr/bin/python

import sys
import re
import fileinput

data0=""
for line in fileinput.input():
    data0+=line

data1 = data0.split("\n")
if data1[-1]=="":
  data1 = data1[:-1]

def capitalizeFirst(name):
    return name[0].upper()+name[1:]

indent="    "
attribPostfix=""
attribNamespace="at::"

useAttribs=False
generateGetAddress=True

def writeClass(data):
    #data1=map(lambda x:x+"value" if len(x)==1 else x,data.split(","))
    data1 = data.split(",")
    typeName=[]
    hasReturnValue = False
    if data1[0]!="void":
        typeName+=[(data1[0],"ret")]
        hasReturnValue=True

    hasParams = False
    if len(data1)>2:
        hasParams = True

    hasInterface = hasParams or hasReturnValue

    #typeName+=zip(data1[2::2],data1[3::2])
    typeName+=zip(data1[2::2],map(lambda x:x+"_" if x=="near" or x=="far" else x,data1[3::2]))

    #print typeName
    maxTypeLength = 0
    maxNameLength = 0
    typeSpaces=dict()
    nameSpaces=dict()

    if hasInterface:
        maxTypeLength = max(map(lambda x:len(x[0]),typeName))
        maxNameLength = max(map(lambda x:len(x[1]),typeName))
        for i in typeName:
            typeSpaces[i[0]]=" "*(maxTypeLength-len(i[0]))
            nameSpaces[i[1]]=" "*(maxNameLength-len(i[1]))

    #print data1
    #print data
    #print typeName

    result=""


    if hasInterface:
        result+=indent+"template<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"  typename "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+" = "+i[0]+typeSpaces[i[0]]
    if hasInterface:
        result+=">\n"

    className=data1[1][2:]
    result+=indent+"class "+className+":\n"
    result+=indent+"    public ge::core::Command"
    
    if useAttribs:
        for i in typeName:
            result+=",\n"+indent+"    public "+attribNamespace+capitalizeFirst(i[1])+attribPostfix+nameSpaces[i[1]]+"<"+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+">"

    result+="{\n"
    if generateGetAddress:
        if hasInterface:
            result+=indent+"  protected:\n"
            result+=indent+"    void*_getAttribAddress(std::string name){\n"
            for i in typeName:
                result+=indent+"      if(name == \""+i[1]+"\""+nameSpaces[i[1]]+")return(void*)&this->"+i[1]+nameSpaces[i[1]]+";\n"
            result+=indent+"      return NULL;\n"
            result+=indent+"    }\n"

    result+=indent+"  public:\n"
    if not useAttribs:
        for i in typeName:
            result+=indent+"    "+i[1].upper()+"_TYPE "+nameSpaces[i[1]]+""+i[1]+nameSpaces[i[1]]+";\n"

    result+=indent+"    "+className+"(\n"+indent+"        ";
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"+indent+"        "
        result+=i[1].upper()+"_TYPE"+nameSpaces[i[1]]+" const&"+i[1]+nameSpaces[i[1]]
    result+=")"
    if hasInterface:
        if useAttribs:
            result+=":"
            result+="\n"+indent+"      "
#        if not useAttribs:
#            result+="\n"+indent+"    "

    if useAttribs:
        first=True
        for i in typeName:
            if first: first = False
            else: result+=",\n"+indent+"      "
            result+=attribNamespace+capitalizeFirst(i[1])+attribPostfix+nameSpaces[i[1]]+"<"+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+">("+i[1]+nameSpaces[i[1]]+")"
        result+="{}\n"

    if not useAttribs:
        result+="{\n"
        for i in typeName:
            result+=indent+"      this->"+i[1]+nameSpaces[i[1]]+" = "+i[1]+nameSpaces[i[1]]+";\n"
        result+=indent+"    "+"}\n"

    result+=indent+"    virtual~"+className+"(){}\n"
    result+=indent+"    virtual void operator()(){\n"
    if hasReturnValue:
        result+=indent+"      ge::core::convertFrom<"+typeName[0][0]+">(this->"
        if useAttribs:
            result+=attribNamespace+capitalizeFirst(typeName[0][1])+attribPostfix+"<"+typeName[0][1].upper()+"_TYPE>::_value,"
        if not useAttribs:
            result+=typeName[0][1]+attribPostfix+","

        result+=data1[1]+"("
        if hasParams:
            result+="\n"
        first = True
        for i in typeName[1::]: 
            if first: first = False
            else: result+=",\n"
            result+=indent+"          ge::core::convertTo<"+i[0]+typeSpaces[i[0]]+">(this->"
            if useAttribs:
                result+=attribNamespace+capitalizeFirst(i[1])+attribPostfix+nameSpaces[i[1]]+"<"+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+">::_value)"
            if not useAttribs:
                result+=i[1]+attribPostfix+nameSpaces[i[1]]+")"
        result+=")"
    else:
        result+=indent+"      "+data1[1]+"(\n"
        first = True
        for i in typeName:
            if first: first = False
            else: result+=",\n"
            result+=indent+"        ge::core::convertTo<"+i[0]+typeSpaces[i[0]]+">(this->"
            if useAttribs:
                result+=attribNamespace+capitalizeFirst(i[1])+attribPostfix+nameSpaces[i[1]]+"<"+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+">::_value)"
            if not useAttribs:
                result+=i[1]+attribPostfix+nameSpaces[i[1]]+")"
    result+="\n"+indent+"      );\n"
    result+=indent+"    }\n"
    result+=indent+"};\n"
        
    return result

attribs=["ret"]
for i in data1:
    attribs+=i.split(",")[3::2]

attribs=list(set(attribs))

maxAttribLen=max(map(lambda x:len(x),attribs))

if useAttribs:
    print "namespace ge{"
    print "  namespace gl{"
    print "    namespace at{"
    for i in attribs:
        print "      DEF_NAMED_TEMPLATE_ATTRIBUTE("+capitalizeFirst(i)+attribPostfix+" "*(maxAttribLen-len(i))+");"
    print "    }"
    print "  }"
    print "}"


def factory(data):
    data1 = data.split(",")
    typeName=[]
    hasReturnValue = False
    if data1[0]!="void":
        typeName+=[(data1[0],"ret")]
        hasReturnValue=True

    hasParams = False
    if len(data1)>2:
        hasParams = True

    hasInterface = hasParams or hasReturnValue

    if not hasInterface:
        return ""

    #typeName+=zip(data1[2::2],data1[3::2])
    typeName+=zip(data1[2::2],map(lambda x:x+"_" if x=="near" or x=="far" else x,data1[3::2]))

    #print typeName
    maxTypeLength = 0
    maxNameLength = 0
    typeSpaces=dict()
    nameSpaces=dict()

    if hasInterface:
        maxTypeLength = max(map(lambda x:len(x[0]),typeName))
        maxNameLength = max(map(lambda x:len(x[1]),typeName))
        for i in typeName:
            typeSpaces[i[0]]=" "*(maxTypeLength-len(i[0]))
            nameSpaces[i[1]]=" "*(maxNameLength-len(i[1]))

    result=""

    className=data1[1][2:]

    result+=indent+"template<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"  typename "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+" = "+i[0]+typeSpaces[i[0]]
    result+=">\n"


    result+=indent+"inline "+className
    result+="<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"  "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]
    result+=">*"
    result+=" new"+className+"(\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"    "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+" const&"+i[1]+nameSpaces[i[1]]
    result+="){\n"
    result+=indent+"    return new "+className+"<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"      "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]
    result+=">(\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"          "+i[1]+nameSpaces[i[1]]
    result+=");\n"
    result+=indent+"}\n"





    result+=indent+"template<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"  typename "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+" = "+i[0]+typeSpaces[i[0]]
    result+=">\n"

    result+=indent+"inline std::shared_ptr<"+className
    result+="<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"  "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]
    result+=">>"
    result+=" shared"+className+"(\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"    "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]+" const&"+i[1]+nameSpaces[i[1]]
    result+="){\n"
    result+=indent+"    return std::make_shared<"+className+"<\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"      "+i[1].upper()+"_TYPE"+nameSpaces[i[1]]
    result+=">>(\n"
    first=True
    for i in typeName:
        if first: first = False
        else: result+=",\n"
        result+=indent+"          "+i[1]+nameSpaces[i[1]]
    result+=");\n"
    result+=indent+"}\n"



    return result;


print "#pragma once"
print ""
print "#include<geCore/Command.h>"
print "#include<geGL/Export.h>"
print "#include<GL/glew.h>"
print "#include<geGL/AllAttribs.h>"
print ""
print "namespace ge{"
print "  namespace gl{"
for i in data1:
    print writeClass(i)

for i in data1:
    print factory(i)

print "  }"
print "}"


