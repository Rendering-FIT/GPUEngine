#ifndef _RASTERIZATIONSTATE_H_
#define _RASTERIZATIONSTATE_H_

#include<geGL/OpenGL.h>
#include<geCore/Object.h>

#include<iostream>

namespace ge{
  namespace gl{
    class GE_EXPORT RasterizationState
    {
      protected:
        bool      _ignoreDiscard;
        GLboolean _discard;

        bool      _ignorePointSize;
        GLfloat   _pointSize;
        bool      _ignorePointFadeThresholdSize;
        GLfloat   _pointFadeThresholdSize;
        bool      _ignorePointSpriteCoordOrigin;
        GLenum    _pointSpriteCoordOrigin;

        bool      _ignoreLineWidth;
        GLfloat   _lineWidth;
        bool      _ignoreLineSmooth;
        GLboolean _lineSmooth;

        bool      _ignoreCullFace;
        GLboolean _cullFace;
        bool      _ignoreCullFaceMode;
        GLenum    _cullFaceMode;

        bool      _ignoreFrontFace;
        GLenum    _frontFace;

        bool      _ignorePolygonSmooth;
        GLboolean _polygonSmooth;
        bool      _ignorePolygonModeFront;
        GLenum    _polygonModeFront;
        bool      _ignorePolygonModeBack;
        GLenum    _polygonModeBack;
        bool      _ignorePolygonOffset;
        GLfloat   _polygonOffsetFactor;
        GLfloat   _polygonOffsetUnits;
        bool      _ignorePolygonOffsetPoint;
        GLboolean _polygonOffsetPoint;
        bool      _ignorePolygonOffsetLine;
        GLboolean _polygonOffsetLine;
        bool      _ignorePolygonOffsetFill;
        GLboolean _polygonOffsetFill;
      public:
        RasterizationState();
        ~RasterizationState();
        void apply();

        GLboolean getDiscard();
        void      setDiscard(GLboolean value);
        void      ignoreDiscard();
        bool      hasDiscard();
        GLfloat   getPointSize();
        void      setPointSize(GLfloat value);
        void      ignorePointSize();
        bool      hasPointSize();
        GLfloat   getPointFadeThresholdSIze();
        void      setPointFadeThresholdSize(GLfloat value);
        void      ignorePointFadeThresholdSize();
        bool      hasPointFadeThresholdSize();
        GLenum    getPointSpriteCoordOrigin();
        void      setPointSpriteCoordOrig(GLenum value);
        void      ignorePointSpriteCoordOrig();
        bool      hasPointSpriteCoordOrig();
        GLfloat   getLineWidth();
        void      setLineWidth(GLfloat value);
        void      ignoreLineWidth();
        bool      hasLineWidth();
        GLboolean getCullFace();
        void      setCullFace(GLboolean value);
        void      ignoreCullFace();
        bool      hasCullFace();

        GLenum    getCullFaceMode();
        void      setCullFaceMode(GLenum value);
        void      ignoreCullFaceMode();
        bool      hasCullFaceMode();
        GLenum    getFrontFace();
        void      setFrontFace(GLenum value);
        void      ignoreFrontFace();
        bool      hasFrontFace();
        GLboolean getPolygonSmooth();
        void      setPolygonSmooth(GLboolean value);
        void      ignorePolygonSmooth();
        bool      hasPolygonSmooth();
        GLenum    getPolygonModeFront();
        void      setPolygonModeFront(GLenum value);
        void      ignorePolygonModeFront();
        bool      hasPolygonModeFront();
        GLenum    getPolygonModeBack();
        void      setPolygonModeBack(GLenum value);
        void      ignorePolygonModeBack();
        bool      hasPolygonModeBack();
        GLfloat   getPolygonOffsetFactor();
        GLfloat   getPolygonOffsetUnits();
        void      getSetPolygonOffset(GLfloat factor,GLfloat units);
        void      ignorePolygonOffset();
        bool      hasPolygonOffset();
        GLboolean getPolygonOffsetPoint();
        void      setPolygonOffsetPoint(GLboolean value);
        void      ignorePolygonOffsetPoint();
        bool      hasPolygonOffsetPoint();
        GLboolean getPolygonOffsetLine();
        void      setPolygonOffsetLine(GLboolean value);
        void      ignorePolygonOffsetLine();
        bool      hasPolygonOffsetLine();
        GLboolean getPolygonOffsetFill();
        void      setPolygonOffsetFill(GLboolean value);
        void      ignorePolygonOffsetFill();
        bool      hasPolygonOffsetFill();
    };
  }//gl
}//ge

#endif//_RASTERIZATIONSTATE_H_
