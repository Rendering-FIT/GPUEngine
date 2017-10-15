#include<geUtil/CameraPath.h>
#include<math.h>
#include<fstream>
#include<sstream>
#include<cstdlib>

namespace ge{
  namespace util{
    CameraKeyPoint::CameraKeyPoint(
        float*Position,
        float*ViewVector,
        float*UpVector,
        float Fovy){
      for(int k=0;k<3;++k){
        this->position  [k] = Position[k];
        this->viewVector[k] = ViewVector[k];
        this->upVector  [k] = UpVector[k];
      }
      this->fovy=Fovy;
    }
    CameraKeyPoint::CameraKeyPoint(CameraObject*Camera){
      for(int k=0;k<3;++k){
        this->position  [k] = -Camera->getPosition( )[k];
        this->viewVector[k] = -Camera->getVector(2)[k];
        this->upVector  [k] =  Camera->getVector(1)[k];
      }
      this->fovy=Camera->getFovy();
    }

    CameraPath::CameraPath(){
      this->_selected=0;

#ifdef ENABLE_DRAWING
      this->_emptyVAO=new ge::gl::VertexArrayObject();
      std::string LineVertex=
        "#version 430\n"
        "void main(){gl_Position=vec4(0,0,0,1);}\n";
      std::string LineGeometry=
        "#version 430\n"
        "#define POINTS 20\n"
        "layout(points)in;\n"
        "layout(line_strip,max_vertices=POINTS)out;\n"
        "uniform vec3 A;\n"
        "uniform vec3 B;\n"
        "uniform vec3 C;\n"
        "uniform vec3 D;\n"
        "uniform mat4 mvp;\n"
        "float CR(float a,float b,float c,float d,float t1){\n"
        "float t2=t1*t1;\n"
        "float t3=t2*t1;\n"
        "return\n"
        "   ( -.5*t3 +    t2 - .5*t1 + 0 )*a+\n"
        "   ( 1.5*t3 -2.5*t2 + 0     + 1.)*b+\n"
        "   (-1.5*t3 +  2*t2 + .5*t1 + 0.)*c+\n"
        "   (  .5*t3 - .5*t2 + 0     + 0.)*d;\n"
        "}\n"
        "void main(){\n"
        "  for(int i=0;i<POINTS;++i){\n"
        "    float t=float(i)/float(POINTS-1);\n"
        "    float Px=CR(A.x,B.x,C.x,D.x,t);\n"
        "    float Py=CR(A.y,B.y,C.y,D.y,t);\n"
        "    float Pz=CR(A.z,B.z,C.z,D.z,t);\n"
        "    gl_Position=mvp*vec4(Px,Py,Pz,1);\n"
        "    EmitVertex();\n"
        "  }\n"
        "  EndPrimitive();\n"
        "}\n";
      std::string LineFragment=
        "#version 430\n"
        "uniform vec4 Color;\n"
        "out vec4 fColor;\n"
        "void main(){fColor=Color;}";

      std::shared_ptr<ge::gl::ShaderObject>LV=nullptr;
      std::shared_ptr<ge::gl::ShaderObject>LG=nullptr;
      std::shared_ptr<ge::gl::ShaderObject>LF=nullptr;

      try{
        LV=std::make_shared<ge::gl::ShaderObject>(GL_VERTEX_SHADER  ,LineVertex  );
        LG=std::make_shared<ge::gl::ShaderObject>(GL_GEOMETRY_SHADER,LineGeometry);
        LF=std::make_shared<ge::gl::ShaderObject>(GL_FRAGMENT_SHADER,LineFragment);
        this->_lineProgram=new ge::gl::ProgramObject(LV,LG,LF);
      }catch(std::string&e){
        std::cerr<<e<<std::endl;
      }

      std::string PointVertex=
        "#version 430\n"
        "void main(){gl_Position=vec4(0,0,0,1);}\n";
      std::string PointGeometry=
        "#version 430\n"
        "layout(points)in;\n"
        "layout(line_strip,max_vertices=4)out;\n"
        "uniform vec3 A;\n"
        "uniform mat4 mvp;\n"
        "void main(){\n"
        "  vec4 TP=mvp*vec4(A,1);\n"
        "  float Size=0.03*TP.w;\n"
        "  gl_Position=TP+vec4(-Size,0,0,0);\n"
        "  EmitVertex();\n"
        "  gl_Position=TP+vec4(Size,0,0,0);\n"
        "  EmitVertex();\n"
        "  EndPrimitive();\n"
        "  gl_Position=TP+vec4(0,-Size,0,0);\n"
        "  EmitVertex();\n"
        "  gl_Position=TP+vec4(0,Size,0,0);\n"
        "  EmitVertex();\n"
        "  EndPrimitive();\n"
        "}\n";
      std::string PointFragment=
        "#version 430\n"
        "uniform vec4 Color;\n"
        "out vec4 fColor;\n"
        "void main(){fColor=Color;}";

      std::shared_ptr<ge::gl::ShaderObject>PV=NULL;
      std::shared_ptr<ge::gl::ShaderObject>PG=NULL;
      std::shared_ptr<ge::gl::ShaderObject>PF=NULL;
      try{
        PV=std::make_shared<ge::gl::ShaderObject>(GL_VERTEX_SHADER  ,PointVertex  );
        PG=std::make_shared<ge::gl::ShaderObject>(GL_GEOMETRY_SHADER,PointGeometry);
        PF=std::make_shared<ge::gl::ShaderObject>(GL_FRAGMENT_SHADER,PointFragment);
        this->_pointProgram=new ge::gl::ProgramObject(PV,PG,PF);
      }catch(std::string&e){
        std::cerr<<e<<std::endl;
      }
#endif//ENABLE_DRAWING
    }

    float CameraPath::_catmullRom(float A,float B,float C,float D,float t1){
      float t2=t1*t1;
      float t3=t2*t1;
      return
        ( -.5f*t3 +     t2 -  .5f*t1 + 0.f )*A+
        ( 1.5f*t3 -2.5f*t2 + 0.0f    + 1.f )*B+
        (-1.5f*t3 +2.0f*t2 +  .5f*t1 + 0.f )*C+
        (  .5f*t3 - .5f*t2 + 0.0f    + 0.f )*D;
    }
    CameraPath::~CameraPath(){
      for(unsigned i=0;i<this->_keyPoints.size();++i)
        delete this->_keyPoints[i];
#ifdef ENABLE_DRAWING
      delete this->_lineProgram;
      delete this->_pointProgram;
      delete this->_emptyVAO;
#endif//ENABLE_DRAWING
    }

    void CameraPath::getCameraPoint(CameraKeyPoint*Point,float Time){
      if(this->_keyPoints.size()<1)return;
      if(this->_cyclic)
        Time=fmodf(fmodf(Time,this->_duration)+this->_duration,this->_duration);
      else
        if(Time>this->_duration)Time=this->_duration;
      std::vector<ge::util::CameraKeyPoint*>::size_type Divider=this->_keyPoints.size()-(this->_cyclic?0:1);
      float l=Time/this->_duration;
      std::vector<ge::util::CameraKeyPoint*>::size_type Index[4];
      Index[1]=((std::vector<ge::util::CameraKeyPoint*>::size_type)(l*(float)Divider))%this->_keyPoints.size();
      if(this->_cyclic){
        Index[0]=Index[1]?Index[1]-1:this->_keyPoints.size()-1;
        Index[2]=(Index[1]+1==this->_keyPoints.size())?0:Index[1]+1;
        Index[3]=(Index[2]+1==this->_keyPoints.size())?0:Index[2]+1;
      }else{
        Index[0]=Index[1]?Index[1]-1:0;
        Index[2]=(Index[1]+1==this->_keyPoints.size())?Index[1]:Index[1]+1;
        Index[3]=(Index[2]+1==this->_keyPoints.size())?Index[2]:Index[2]+1;
      }
      float t=(float)Divider*Time/this->_duration-(float)Index[1];
      /*std::cerr<<"Divider: "<<Divider<<std::endl;
        std::cerr<<"_duration: "<<this->_duration<<std::endl;
        std::cerr<<"Time: "<<Time<<std::endl;
        std::cerr<<"t: "<<t<<std::endl;
        std::cerr<<"index: "<<Index[0]<<" "<<Index[1]<<" "<<Index[2]<<" "<<Index[3]<<std::endl;*/
      for(int k=0;k<3;++k){
        Point->position[k]=this->_catmullRom(
            this->_keyPoints[Index[0]]->position[k],
            this->_keyPoints[Index[1]]->position[k],
            this->_keyPoints[Index[2]]->position[k],
            this->_keyPoints[Index[3]]->position[k],
            t);
        Point->viewVector[k]=this->_catmullRom(
            this->_keyPoints[Index[0]]->viewVector[k],
            this->_keyPoints[Index[1]]->viewVector[k],
            this->_keyPoints[Index[2]]->viewVector[k],
            this->_keyPoints[Index[3]]->viewVector[k],
            t);
        Point->upVector[k]=this->_catmullRom(
            this->_keyPoints[Index[0]]->upVector[k],
            this->_keyPoints[Index[1]]->upVector[k],
            this->_keyPoints[Index[2]]->upVector[k],
            this->_keyPoints[Index[3]]->upVector[k],
            t);
      }
      Point->fovy=this->_catmullRom(
          this->_keyPoints[Index[0]]->fovy,
          this->_keyPoints[Index[1]]->fovy,
          this->_keyPoints[Index[2]]->fovy,
          this->_keyPoints[Index[3]]->fovy,
          t);
      float lvv=0;
      for(int k=0;k<3;++k)lvv+=Point->viewVector[k]*Point->viewVector[k];
      lvv=sqrtf(lvv);
      if(lvv>0)for(int k=0;k<3;++k)Point->viewVector[k]/=lvv;
      float luv=0;
      for(int k=0;k<3;++k)luv+=Point->upVector[k]*Point->upVector[k];
      luv=sqrtf(luv);
      if(luv>0)for(int k=0;k<3;++k)Point->upVector[k]/=luv;
    }
    void CameraPath::setDuration(float _duration){
      this->_duration=_duration;
    }
    void CameraPath::insertAfter(int Index,CameraKeyPoint*P){
      this->_keyPoints.insert(this->_keyPoints.begin()+Index+1,P);
    }
    void CameraPath::deletePoint(int Index){
      delete this->_keyPoints[Index];
      this->_keyPoints.erase(this->_keyPoints.begin()+Index);
    }
    void CameraPath::loadCSV(std::string FileName){
      std::ifstream f;
      f.open(FileName.c_str());
      while(f){
        std::string Line;
        if(!std::getline(f,Line))break;
        std::istringstream ss(Line);
        float P[3];
        float V[3];
        float U[3];
        float Fovy;
        for(int k=0;k<3;++k){
          std::string s;
          getline( ss, s, ',' );
          P[k]=(float)std::atof(s.c_str());
        }
        for(int k=0;k<3;++k){
          std::string s;
          getline( ss, s, ',' );
          V[k]=(float)std::atof(s.c_str());
        }
        for(int k=0;k<3;++k){
          std::string s;
          getline( ss, s, ',' );
          U[k]=(float)std::atof(s.c_str());
        }
        for(int k=0;k<1;++k){
          std::string s;
          getline( ss, s, ',' );
          Fovy=(float)std::atof(s.c_str());
        }
        this->_keyPoints.push_back(new CameraKeyPoint(P,V,U,Fovy));
      }
      f.close();
    }
    void CameraPath::saveCSV(std::string FileName){
      std::ofstream f;
      f.open(FileName.c_str());
      for(unsigned i=0;i<this->_keyPoints.size();++i){
        for(int k=0;k<3;++k)f<<this->_keyPoints[i]->position[k]<<",";
        for(int k=0;k<3;++k)f<<this->_keyPoints[i]->viewVector[k]<<",";
        for(int k=0;k<3;++k)f<<this->_keyPoints[i]->upVector[k]<<",";
        f<<this->_keyPoints[i]->fovy<<std::endl;
      }
      f.close();
    }
    void CameraPath::select(unsigned Index){
      this->_selected=Index;
    }
    void CameraPath::insertToEnd(CameraKeyPoint*CameraPoint){
      this->_keyPoints.push_back(CameraPoint);
    }
    decltype(CameraPath::_keyPoints)::size_type CameraPath::getLength(){
      return this->_keyPoints.size();
    }

#if defined(ENABLE_DRAWING)
    void CameraPath::draw(float*mvp){
      this->_emptyVAO->bind();
      if(this->_keyPoints.size()>1){
        this->_lineProgram->use();
        this->_lineProgram->set("mvp",1,GL_FALSE,mvp);
        this->_lineProgram->set("Color",0.f,1.f,0.f,1.f);
        for(int k=0;k<((int)this->_keyPoints.size());++k){
          if(!this->_cyclic&&k+1==(int)this->_keyPoints.size())break;
          float SP[3],EP[3];
          if(this->_cyclic){
            if(k==0)
              for(int i=0;i<3;++i)
                SP[i]=this->_keyPoints[this->_keyPoints.size()-1]->position[i];
            else
              for(int i=0;i<3;++i)
                SP[i]=this->_keyPoints[k-1]->position[i];

            for(int i=0;i<3;++i)
              EP[i]=this->_keyPoints[(k+2)%this->_keyPoints.size()]->position[i];
          }else{
            if(k==0)
              for(int i=0;i<3;++i)
                SP[i]=2*this->_keyPoints[0]->position[i]-this->_keyPoints[1]->position[i];
            else
              for(int i=0;i<3;++i)
                SP[i]=this->_keyPoints[k-1]->position[i];

            for(int i=0;i<3;++i)
              EP[i]=2*this->_keyPoints[(k+2)%this->_keyPoints.size()]->position[i]-
                this->_keyPoints[(k+1)%this->_keyPoints.size()]->position[i];
          }
          this->_lineProgram->set("A",1,SP);
          this->_lineProgram->set("B",1,this->_keyPoints[k+0]->position);
          this->_lineProgram->set("C",1,this->_keyPoints[(k+1)%this->_keyPoints.size()]->position);
          this->_lineProgram->set("D",1,EP);
          glDrawArrays(GL_POINTS,0,1);
        }
      }
      this->_pointProgram->use();
      this->_pointProgram->set("mvp",1,GL_FALSE,mvp);
      for(unsigned k=0;k<this->_keyPoints.size();++k){
        this->_pointProgram->set("A",1,this->_keyPoints[k]->position);
        if(this->_selected==k)this->_pointProgram->set("Color",1.f,0.f,0.f,1.f);
        else this->_pointProgram->set("Color",0.f,0.f,1.f,1.f);
        glDrawArrays(GL_POINTS,0,1);
      }
      this->_emptyVAO->unbind();
    }
#endif//ENABLE_DRAWING
  }//util
}//ge
