#include<geGL/RasterizationState.h>

using namespace ge::gl;

RasterizationState::RasterizationState(){
  this->_ignoreDiscard                = true;
  this->_ignorePointSize              = true;
  this->_ignorePointFadeThresholdSize = true;
  this->_ignorePointSpriteCoordOrigin = true;
  this->_ignoreLineWidth              = true;
  this->_ignoreLineSmooth             = true;
  this->_ignoreCullFace               = true;
  this->_ignoreCullFaceMode           = true;
  this->_ignoreFrontFace              = true;
  this->_ignorePolygonSmooth          = true;
  this->_ignorePolygonModeFront       = true;
  this->_ignorePolygonModeBack        = true;
  this->_ignorePolygonOffset          = true;
  this->_ignorePolygonOffsetPoint     = true;
  this->_ignorePolygonOffsetLine      = true;
  this->_ignorePolygonOffsetFill      = true;
}

void RasterizationState::apply(){
  if(!this->_ignoreDiscard){
    if(this->_discard)glEnable(GL_RASTERIZER_DISCARD);
    else glDisable(GL_RASTERIZER_DISCARD);
  }

  if(!this->_ignorePointSize)
    glPointSize(this->_pointSize);
  if(!this->_ignorePointSpriteCoordOrigin)
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN,this->_pointSpriteCoordOrigin);
  if(!this->_pointFadeThresholdSize)
    glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE,this->_pointFadeThresholdSize);

  if(!this->_ignoreLineWidth)
    glLineWidth(this->_lineWidth);

  if(!this->_ignoreLineSmooth){
    if(this->_lineSmooth)glEnable(GL_LINE_SMOOTH);
    else glDisable(GL_LINE_SMOOTH);
  }

  if(!this->_ignoreCullFace){
    if(this->_cullFace)glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
  }

  if(!this->_ignoreCullFaceMode)
    glCullFace(this->_cullFaceMode);

  if(!this->_ignoreFrontFace)
    glFrontFace(this->_frontFace);

  if(!this->_ignorePolygonSmooth){
    if(this->_polygonSmooth)glEnable(GL_POLYGON_SMOOTH);
    else glDisable(GL_POLYGON_SMOOTH);
  }

  if(!this->_ignorePolygonModeFront)
    glPolygonMode(GL_FRONT,this->_polygonModeFront);

  if(!this->_ignorePolygonModeBack)
    glPolygonMode(GL_BACK,this->_polygonModeBack);

  if(!this->_ignorePolygonOffset)
    glPolygonOffset(this->_polygonOffsetFactor,this->_polygonOffsetUnits);

  if(!this->_ignorePolygonOffsetPoint){
    if(this->_polygonOffsetPoint)glEnable(GL_POLYGON_OFFSET_POINT);
    else glDisable(GL_POLYGON_OFFSET_POINT);
  }

  if(!this->_ignorePolygonOffsetLine){
    if(this->_polygonOffsetLine)glEnable(GL_POLYGON_OFFSET_LINE);
    else glDisable(GL_POLYGON_OFFSET_LINE);
  }

  if(!this->_ignorePolygonOffsetFill){
    if(this->_polygonOffsetPoint)glEnable(GL_POLYGON_OFFSET_FILL);
    else glDisable(GL_POLYGON_OFFSET_FILL);
  }
}


GLboolean RasterizationState::getDiscard(){
  return this->_discard;
}
void RasterizationState::setDiscard(GLboolean value){
  this->_ignoreDiscard = false;
  this->_discard       = value;
}
void RasterizationState::ignoreDiscard(){
  this->_ignoreDiscard = true;
}
bool RasterizationState::hasDiscard(){
  return !this->_ignoreDiscard;
}

GLfloat RasterizationState::getPointSize(){
  return this->_pointSize;
}
void RasterizationState::setPointSize(GLfloat value){
  this->_ignorePointSize = false;
  this->_pointSize       = value;
}
void RasterizationState::ignorePointSize(){
  this->_ignorePointSize = true;
}
bool RasterizationState::hasPointSize(){
  return !this->_ignorePointSize;
}

GLfloat RasterizationState::getPointFadeThresholdSIze(){
  return this->_pointFadeThresholdSize;
}
void RasterizationState::setPointFadeThresholdSize(GLfloat value){
  this->_ignorePointFadeThresholdSize = false;
  this->_pointFadeThresholdSize       = value;
}
void RasterizationState::ignorePointFadeThresholdSize(){
  this->_ignorePointFadeThresholdSize = true;
}
bool RasterizationState::hasPointFadeThresholdSize(){
  return !this->_ignorePointFadeThresholdSize;
}

GLenum RasterizationState::getPointSpriteCoordOrigin(){
  return this->_pointSpriteCoordOrigin;
}
void RasterizationState::setPointSpriteCoordOrig(GLenum value){
  this->_ignorePointSpriteCoordOrigin = false;
  this->_pointSpriteCoordOrigin       = value;
}
void RasterizationState::ignorePointSpriteCoordOrig(){
  this->_ignorePointSpriteCoordOrigin = true;
}
bool RasterizationState::hasPointSpriteCoordOrig(){
  return !this->_ignorePointSpriteCoordOrigin;
}

GLfloat RasterizationState::getLineWidth(){
  return this->_lineWidth;
}
void RasterizationState::setLineWidth(GLfloat value){
  this->_ignoreLineWidth = false;
  this->_lineWidth       = value;
}
void RasterizationState::ignoreLineWidth(){
  this->_ignoreLineWidth = true;
}
bool RasterizationState::hasLineWidth(){
  return !this->_ignoreLineWidth;
}

GLboolean RasterizationState::getCullFace(){
  return this->_cullFace;
}
void RasterizationState::setCullFace(GLboolean value){
  this->_ignoreCullFace = false;
  this->_cullFace       = value;
}
void RasterizationState::ignoreCullFace(){
  this->_ignoreCullFace = true;
}
bool RasterizationState::hasCullFace(){
  return !this->_ignoreCullFace;
}

GLenum    RasterizationState::getCullFaceMode(){
  return this->_cullFaceMode;
}
void      RasterizationState::setCullFaceMode(GLenum value){
  this->_ignoreCullFaceMode = false;
  this->_cullFaceMode       = value;
}
void      RasterizationState::ignoreCullFaceMode(){
  this->_ignoreCullFaceMode = true;
}
bool      RasterizationState::hasCullFaceMode(){
  return !this->_ignoreCullFaceMode;
}

GLenum    RasterizationState::getFrontFace(){
  return this->_frontFace;
}
void      RasterizationState::setFrontFace(GLenum value){
  this->_ignoreFrontFace = false;
  this->_frontFace       = value;
}
void      RasterizationState::ignoreFrontFace(){
  this->_ignoreFrontFace = true;
}
bool      RasterizationState::hasFrontFace(){
  return !this->_ignoreFrontFace;
}

GLboolean RasterizationState::getPolygonSmooth(){
  return this->_polygonSmooth;
}
void      RasterizationState::setPolygonSmooth(GLboolean value){
  this->_ignorePolygonSmooth = false;
  this->_polygonSmooth       = value;
}
void      RasterizationState::ignorePolygonSmooth(){
  this->_ignorePolygonSmooth = true;
}
bool      RasterizationState::hasPolygonSmooth(){
  return !this->_ignorePolygonSmooth;
}

GLenum    RasterizationState::getPolygonModeFront(){
  return this->_polygonModeFront;
}
void      RasterizationState::setPolygonModeFront(GLenum value){
  this->_ignorePolygonModeFront = false;
  this->_polygonModeFront       = value;
}
void      RasterizationState::ignorePolygonModeFront(){
  this->_ignorePolygonModeFront = true;
}
bool      RasterizationState::hasPolygonModeFront(){
  return !this->_ignorePolygonModeFront;
}

GLenum    RasterizationState::getPolygonModeBack(){
  return this->_polygonModeBack;
}
void      RasterizationState::setPolygonModeBack(GLenum value){
  this->_ignorePolygonModeBack = false;
  this->_polygonModeBack       = value;
}
void      RasterizationState::ignorePolygonModeBack(){
  this->_ignorePolygonModeBack = true;
}
bool      RasterizationState::hasPolygonModeBack(){
  return !this->_ignorePolygonModeBack;
}

GLfloat   RasterizationState::getPolygonOffsetFactor(){
  return this->_polygonOffsetFactor;
}
GLfloat   RasterizationState::getPolygonOffsetUnits(){
  return this->_polygonOffsetUnits;
}
void      RasterizationState::getSetPolygonOffset(GLfloat factor,GLfloat units){
  this->_ignorePolygonOffset = false;
  this->_polygonOffsetFactor = factor;
  this->_polygonOffsetUnits  = units;
}
void      RasterizationState::ignorePolygonOffset(){
  this->_ignorePolygonOffset = true;
}
bool      RasterizationState::hasPolygonOffset(){
  return !this->_ignorePolygonSmooth;
}

GLboolean RasterizationState::getPolygonOffsetPoint(){
  return this->_polygonOffsetPoint;
}
void      RasterizationState::setPolygonOffsetPoint(GLboolean value){
  this->_ignorePolygonOffsetPoint = false;
  this->_polygonOffsetPoint       = value;
}
void      RasterizationState::ignorePolygonOffsetPoint(){
  this->_ignorePolygonOffsetPoint = true;
}
bool      RasterizationState::hasPolygonOffsetPoint(){
  return !this->_ignorePolygonOffsetPoint;
}

GLboolean RasterizationState::getPolygonOffsetLine(){
  return this->_polygonOffsetLine;
}
void      RasterizationState::setPolygonOffsetLine(GLboolean value){
  this->_ignorePolygonOffsetLine = false;
  this->_polygonOffsetLine       = value;
}
void      RasterizationState::ignorePolygonOffsetLine(){
  this->_ignorePolygonOffsetLine = true;
}
bool      RasterizationState::hasPolygonOffsetLine(){
  return !this->_ignorePolygonOffsetLine;
}

GLboolean RasterizationState::getPolygonOffsetFill(){
  return this->_polygonOffsetFill;
}
void      RasterizationState::setPolygonOffsetFill(GLboolean value){
  this->_ignorePolygonOffsetFill = false;
  this->_polygonOffsetFill       = value;
}
void      RasterizationState::ignorePolygonOffsetFill(){
  this->_ignorePolygonOffsetFill = true;
}
bool      RasterizationState::hasPolygonOffsetFill(){
  return !this->_ignorePolygonOffsetFill;
}

