#include <geGL/Blend.h>

namespace ge
{
  namespace gl
  {
    /*
    void Blend::_init(){
      this->_enable .free();
      this->_disable.free();
      this->_enablei  = NULL;
      this->_disablei = NULL;

      //this->_enableCommand            = NULL;
      //this->_enableiCommand           = NULL;
      this->_equationCommand          = NULL;
      this->_equationSeparateCommand  = NULL;
      this->_equationiCommand         = NULL;
      this->_equationSeparateiCommand = NULL;
      this->_funcCommand              = NULL;
      this->_funcSeparateCommand      = NULL;
      this->_funciCommand             = NULL;
      this->_funcSeparateiCommand     = NULL;
      this->_colorCommand             = NULL;
    }
    void Blend::_mergeEnableDisableSeparate(){


    }

    Blend::Blend(){
      this->_init();
      glGetIntegerv(GL_MAX_DRAW_BUFFERS,(GLint*)&this->_maxBuffers);
    }
    Blend::Blend(unsigned maxBuffers){
      this->_init();
      this->_maxBuffers=maxBuffers;
    }
    void Blend::enable(){
      //TODO disable sep
      this->_disable.free();
      this->_enable .free();
      this->_enable .command = new Enable(GL_BLEND);
      this->_enable .ref     = false;
    }
    void Blend::enable(Enable*enableCommand){
      //TODO disable sep
      this->_disable.free();
      this->_enable .free();
      this->_enable .command = enableCommand;
      this->_enable .ref     = true;
    }
    void Blend::disable(){
      //TODO disable sep
      this->_enable .free();
      this->_disable.free();
      this->_disable.command = new Disable(GL_BLEND);
      this->_disable.ref     = false;
    }
    void Blend::disable(Disable*disableCommand){
      //TODO disable sep
      this->_enable .free();
      this->_disable.free();
      this->_disable.command = disableCommand;
      this->_disable.ref     = true;
    }
    void Blend::ignore(){
      this->_enable .free();
      this->_disable.free();
    }
    void Blend::enable(GLuint buffer){
      //TODO NULL?
      if(!this->_enablei){
        this->_enablei=new CommandContainer[this->_maxBuffers];
        for(unsigned b=0;b<this->_maxBuffers;++b)this->_enablei[b].free();
      }else this->_enablei[buffer].free();

      if(this->_disablei)this->_disablei[buffer].free();

      this->_enablei [buffer].command = new Enablei(buffer,GL_BLEND);
      this->_enablei [buffer].ref     = false;
      //TODO merge
    }
    void Blend::enable(Enablei*enableCommand){
      //TODO NULL
      GLuint buffer=enableCommand->buffer;
      this->_disablei[buffer].free();
      this->_enablei [buffer].free();
      this->_enablei [buffer].command = enableCommand;
      this->_enablei [buffer].ref     = true;
    }
    void Blend::disable(GLuint buffer){
      //TODO NULL
      this->_enablei [buffer].free();
      this->_disablei[buffer].free();
      this->_disablei[buffer].command = new Enablei(buffer,GL_BLEND);
      this->_disablei[buffer].ref     = false;
      //TODO merge
    }
    void Blend::disable(Disablei*disableCommand){
      //TODO NULL
      GLuint buffer=disableCommand->buffer;
      this->_enablei [buffer].free();
      this->_disablei[buffer].free();
      this->_disablei[buffer].command = disableCommand;
      this->_disablei[buffer].ref     = true;
    }
    */
    /*void Blend::_deleteEnablei(){
      if(this->_enableiCommand){
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->_enableiCommand[i]&&!this->_refEnableiCommand[i])
            delete this->_enableiCommand[i];
        delete[]this->_enableiCommand;
        delete[]this->_refEnableiCommand;
      }
    }
    void Blend::_deleteEquationi(){
      if(this->_equationiCommand){
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->_equationiCommand[i])
            delete this->_equationiCommand[i];
        delete[]this->_equationiCommand;
      }
    }
    void Blend::_deleteEquationSeparatei(){
      if(this->_equationSeparateiCommand){
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->_equationSeparateiCommand[i])
            delete this->_equationSeparateiCommand[i];
        delete[]this->_equationSeparateiCommand;
      }
    }
    void Blend::_deleteFunci(){
      if(this->_funciCommand){
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->_funciCommand[i])
            delete this->_funciCommand[i];
        delete[]this->_funciCommand;
      }
    }
    void Blend::_deleteFuncSeparatei(){
      if(this->_funcSeparateiCommand){
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->_funcSeparateiCommand[i])
            delete this->_funcSeparateiCommand[i];
        delete[]this->_funcSeparateiCommand;
      }
    }
    Blend::~Blend(){
      this->ignore();
      this->_deleteEnablei();
      this->ignoreBlendEquation();
      this->ignoreBlendEquationSeparate();
      this->_deleteEquationi();
      this->_deleteEquationSeparatei();
      if(this->_funcCommand)
        delete this->_funcCommand;
      if(this->_funcSeparateCommand)
        delete this->_funcSeparateCommand;
      this->_deleteFunci();
      this->_deleteFuncSeparatei();
      if(this->_colorCommand)
        delete this->_colorCommand;
    }
    void Blend::enable(){
      //ignore previous glEnable command
      this->ignore();
      //delete gl{En,Dis}ablei commands
      this->_deleteEnablei();
      //create glEnable command
      this->_enableCommand=new Enable(GL_BLEND);
      //set reference flag to false
      this->_refEnableCommand=false;
    }
    void Blend::enable(Enable*enableCommand){
      //ignore previous glEnable command
      this->ignore();
      //delete gl{En,Dis}ablei commands
      this->_deleteEnablei();
      //insert glEnable command
      this->_enableCommand=enableCommand;
      //set reference flag to true
      this->_refEnableCommand=true;
    }
    void Blend::disable(){
      //ignore previous glDisable command
      this->ignore();
      //delete gl{En,Dis}ablei commands
      this->_deleteEnablei();
      //create glDisable command
      this->_enableCommand=new Disable(GL_BLEND);
      //set reference flag to false
      this->_refEnableCommand=false;
    }
    void Blend::disable(Disable*disableCommand){
      //ignore previous glDisable command
      this->ignore();
      //delete gl{En,Dis}ablei commands
      this->_deleteEnablei();
      //insert glDisable command
      this->_enableCommand=disableCommand;
      //set reference flag to true
      this->_refEnableCommand=true;
    }
    void Blend::ignore(){
      //is there a non referenced gl{En,Dis}able command?
      if(this->_enableCommand&&!this->_refEnableCommand)
        //delete gl{En,Dis}anble command
        delete this->_enableCommand;
      //set gl{En,Dis}able command to NULL
      this->_enableCommand=NULL;
      //set reference flag to false
      this->_refEnableCommand=false;
    }
    void Blend::enable(GLuint buffer){
      if(!this->_enableiCommand){
        this->_enableiCommand    = new Command*[this->_maxBuffers];
        this->_refEnableiCommand = new bool          [this->_maxBuffers];
        for(unsigned i=0;i<this->_maxBuffers;++i){
          this->_enableiCommand   [i] = NULL;
          this->_refEnableiCommand[i] = false;
        }

      }
    }*/
    /*
    void Blend::SetEnable(GLuint Buffer,bool Enable){
      if(!this->EnableiCommand){
        this->EnableiCommand=new Command*[this->_maxBuffers];
        for(unsigned i=0;i<this->_maxBuffers;++i)
          this->EnableiCommand[i]=NULL;
      }

      if(this->EnableiCommand[Buffer]){
        ((CBlendEnablei*)this->EnableiCommand[Buffer])->Buffer = Buffer;
        ((CBlendEnablei*)this->EnableiCommand[Buffer])->Enable = Enable;
      }else this->EnableiCommand[Buffer]=new CBlendEnablei(Buffer,Enable);

      bool Merge=true;
      for(unsigned i=0;i<this->_maxBuffers;++i)
        if(((CBlendEnablei*)this->EnableiCommand)->Enable!=Enable){
          Merge=false;
          break;
        }

      if(Merge){
        this->DeleteEnablei();
        if(Enable)this->Enable();
        else this->Disable();
      }
    }*/
    /*void Blend::Enable(GLuint Buffer){
      this->SetEnable(Buffer,true);
    }
    void Blend::Disable(GLuint Buffer){
      this->SetEnable(Buffer,false);
    }
    void Blend::Ignore(GLuint Buffer){
      if(this->EnableiCommand){
        if(this->EnableiCommand[Buffer])
          delete this->EnableiCommand[Buffer];
        this->EnableiCommand[Buffer]=NULL;

        bool Clear=true;
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->EnableiCommand[i]){
            Clear=false;
            break;
          }
        if(Clear)
          delete[]this->EnableiCommand;
        this->EnableiCommand=NULL;
      }
    }
    void Blend::BlendEquation(GLenum Mode){
      if(this->EquationCommand)
        ((CBlendEquation*)this->EquationCommand)->Mode=Mode;
      else this->EquationCommand=new CBlendEquation(Mode);
      this->IgnoreBlendEquationSeparate();
    }
    void Blend::IgnoreBlendEquation(){
      if(this->EquationCommand)
        delete this->EquationiCommand;
      this->EquationCommand=NULL;
    }
    void Blend::BlendEquationSeparate(GLenum ModeRGB,GLenum ModeAlpha){
      if(this->EquationSeparateCommand){
        ((CBlendEquationSeparate*)this->EquationSeparateCommand)->ModeRGB   = ModeRGB;
        ((CBlendEquationSeparate*)this->EquationSeparateCommand)->ModeAlpha = ModeAlpha;
      }else this->EquationSeparateCommand=new CBlendEquationSeparate(ModeRGB,ModeAlpha);
      this->IgnoreBlendEquation();
    }
    void Blend::IgnoreBlendEquationSeparate(){
      if(this->EquationSeparateCommand)
        delete this->EquationSeparateiCommand;
      this->EquationSeparateiCommand=NULL;
    }
    void Blend::BlendEquation(GLuint Buffer,GLenum Mode){
      if(!this->EquationiCommand){
        this->EquationiCommand=new Command*[this->_maxBuffers];
        for(unsigned i=0;i<this->_maxBuffers;++i)
          this->EquationiCommand[i]=NULL;
      }

      if(this->EquationiCommand[Buffer]){
        ((CBlendEquationi*)this->EquationiCommand[Buffer])->Buffer = Buffer;
        ((CBlendEquationi*)this->EquationiCommand[Buffer])->Mode   = Mode;
      }else this->EquationiCommand[Buffer]=new CBlendEquationi(Buffer,Mode);
      this->IgnoreBlendEquationSeparate(Buffer);
    }
    void Blend::IgnoreBlendEquation(GLuint Buffer){
      if(this->EquationiCommand){
        if(this->EquationiCommand[Buffer])
          delete this->EquationiCommand;
        this->EquationiCommand=NULL;

        bool Clear=true;
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->EquationiCommand[i]){
            Clear=false;
            break;
          }
        if(Clear)
          delete[]this->EquationiCommand;
        this->EquationiCommand=NULL;
      }
    }
    void Blend::BlendEquationSeparate(GLuint Buffer,GLenum ModeRGB,GLenum ModeAlpha){
      if(!this->EquationSeparateiCommand){
        this->EquationSeparateiCommand=new Command*[this->_maxBuffers];
        for(unsigned i=0;i<this->_maxBuffers;++i)
          this->EquationSeparateiCommand[i]=NULL;
      }

      if(this->EquationSeparateiCommand[Buffer]){
        ((CBlendEquationSeparatei*)this->EquationSeparateiCommand)->ModeRGB = ModeRGB;
        ((CBlendEquationSeparatei*)this->EquationSeparateiCommand)->ModeRGB = ModeAlpha;
      }else this->EquationSeparateiCommand[Buffer]=new CBlendEquationSeparatei(Buffer,ModeRGB,ModeAlpha);

      bool Merge=true;
      for(unsigned i=0;i<this->_maxBuffers;++i){
        CBlendEquationSeparatei*A=(CBlendEquationSeparatei*)this->EquationSeparateiCommand[i];
        if(A->ModeRGB!=ModeRGB||A->ModeAlpha!=ModeAlpha){
          Merge=false;
          break;
        }
      }

      if(Merge){
        this->DeleteEquationi();
        this->EquationSeparate(ModeRGB,ModeAlpha);
      }
    }
    void Blend::IgnoreBlendEquationSeparate(GLuint Buffer){
      if(this->EquationSeparateiCommand){
        if(this->EquationSeparateiCommand[Buffer])
          delete this->EquationSeparateiCommand[Buffer];
        this->EquationSeparateiCommand[Buffer]=NULL;

        bool Clear=true;
        for(unsigned i=0;i<this->_maxBuffers;++i)
          if(this->EquationSeparateiCommand[Buffer]){
            Clear=false;
            break;
          }
        if(Clear)
          delete[]this->EquationSeparateiCommand;
        this->EquationSeparateiCommand=NULL;
      }
    }
    void Blend::BlendFunc(GLenum Src,GLenum Dst){
      if(this->FuncCommand){
        ((CBlendFunc*)this->FuncCommand)->Src = Src;
        ((CBlendFunc*)this->FuncCommand)->Src = Dst;
      }else this->FuncCommand=new CBlendFunc(Src,Dst);
      this->IgnoreBlendFuncSeparate();
    }
    void Blend::IgnoreBlendFunc(){
      if(this->FuncCommand)
        delete this->FuncCommand;
      this->FuncCommand=NULL;
    }
    void Blend::BlendFuncSeparate(GLenum SrcRGB,GLenum DstRGB,GLenum SrcAlpha,GLenum DstAlpha){
      if(this->FuncSeparateCommand){
        ((CBlendFuncSeparate*)this->FuncSeparateCommand)->SrcRGB   = SrcRGB;
        ((CBlendFuncSeparate*)this->FuncSeparateCommand)->DstRGB   = DstRGB;
        ((CBlendFuncSeparate*)this->FuncSeparateCommand)->SrcAlpha = SrcAlpha;
        ((CBlendFuncSeparate*)this->FuncSeparateCommand)->DstAlpha = DstAlpha;
      }else this->FuncSeparateCommand=new CBlendFuncSeparate(SrcRGB,DstRGB,SrcAlpha,DstAlpha);
      this->IgnoreBlendFunc();
    }
    void Blend::IgnoreBlendFuncSeparate(){
      if(this->FuncSeparateCommand)
        delete this->FuncSeparateCommand;
      this->FuncSeparateCommand=NULL;
    }*/
    /*
       void BlendFunc(GLuint Buffer,GLenum Src,GLenum Dst);
       void IgnoreBlendFunc(GLuint Buffer);

       void BlendFuncSeparate(GLuint Buffer,GLenum SrcRGB,GLenum DstRGB,GLenum SrcAlpha,GLenum DstAlpha);
       void IgnoreBlendFuncSeparate(GLuint Buffer);

       void BlendColor(GLfloat Red,GLfloat Green,GLfloat Blue,GLfloat Alpha);
       void IgnoreBlendColor();

       void apply();*/
  }//ogl
}//ge
