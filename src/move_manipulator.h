#pragma once

#include <maya/MPxManipulatorNode.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class MannequinMoveManipulator : public MPxManipulatorNode {
public:
  MannequinMoveManipulator();

  void setManipScale(float scale);
  float manipScale() const;

  void recalcMetrics();
  bool intersectManip(MPxManipulatorNode* manip) const;
  void glDrawCone(GLUquadricObj* quadric,
    MPoint pos,
    MVector dir,
    float height,
    float radius) const;

  virtual void postConstructor() override;
  virtual void draw(M3dView &view,
    const MDagPath &path,
    M3dView::DisplayStyle style,
    M3dView::DisplayStatus status) override;
  virtual void preDrawUI(const M3dView &view) override;
  virtual void drawUI(MHWRender::MUIDrawManager &drawManager,
    const MHWRender::MFrameContext &frameContext) const override;
  virtual MStatus connectToDependNode(const MObject &dependNode) override;
  virtual MStatus doPress(M3dView& view) override;
  virtual MStatus doDrag(M3dView& view) override;
  virtual MStatus doRelease(M3dView& view) override;

  static void* creator();
  static MStatus initialize();
  static const MTypeId id;

  // For compatibility with Maya 2015.
  void beginDrawable(MHWRender::MUIDrawManager &drawManager,
    unsigned int name,
    bool pickable) const;
  bool shouldDrawHandleAsSelected(int axis);

private:
  int _translateIndex;
  MPlug _translatePlug;

  MTransformationMatrix _parentXform;
  MTransformationMatrix _childXform;

  short _xColor;
  short _yColor;
  short _zColor;
  short _selColor;
  GLuint _glPickableItem;
  bool _selected[3];

  float _manipScale;
  MVector _x;
  MVector _y;
  MVector _z;
  MPoint _origin;

  MVector _xInParentSpace;
  MVector _yInParentSpace;
  MVector _zInParentSpace;

  bool _opValid;
  short _opAxisIndex;
  MPoint _opOrigin;
  MVector _opAxis;
  MVector _opPlaneNormal;
  MPoint _opHitBegin;
  MPoint _opHitCurrent;
  MVector _opDiffProj;
  MPoint _opValueBegin;
};
