#pragma once

#include <vector>

#include <maya/MPxContext.h>
#include <maya/MPxContextCommand.h>
#include <maya/MEvent.h>
#include <maya/MDagPath.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <boost/optional.hpp>

class MannequinManipulator;

class MannequinContext : public MPxContext {
public:
  MannequinContext();
  void forceExit();
  void select(const MDagPath& dagPath);
  void reselect();
  MDagPath selectionDagPath() const;
  void calculateMaxInfluences(MDagPath meshDagPath, MObject skinObject);
  void calculateLongestJoint(MObject skinObject);
  void calculateJointLengthRatio(MDagPath jointDagPath);
  const std::vector<int>& maxInfluences() const;
  MDagPath meshDagPath() const;
  MObject skinObject() const;
  bool addMannequinManipulator(MDagPath newHighlight = MDagPath());
  bool intersectRotateManip(MPoint linePoint,
    MVector lineDirection,
    float* distanceOut);
  double manipScale() const;
  void setManipScale(double scale);
  bool manipAutoAdjust() const;
  void setManipAutoAdjust(bool autoAdjust);
  double manipAdjustedScale() const;

  virtual void toolOnSetup(MEvent& event) override;
  virtual void toolOffCleanup() override;
  virtual void getClassName(MString& name) const override;
  virtual MStatus doPress(MEvent& event,
    MHWRender::MUIDrawManager& drawMgr,
    const MHWRender::MFrameContext& context);
  virtual MStatus doPress(MEvent& event);
  virtual void abortAction() override;
  void doPress();
  void updateText();

private:
  static constexpr double MANIP_DEFAULT_SCALE = 1.5;
  static constexpr double MANIP_ADJUSTMENT = 0.1;

  MDagPath _meshDagPath;
  MObject _skinObject;
  std::vector<int> _maxInfluences;

  MDagPath _selection;
  MannequinManipulator* _mannequinManip;
  MObject _rotateManip;

  mutable boost::optional<double> _scale;
  mutable boost::optional<double> _autoAdjust;
  double _longestJoint;
  double _jointLengthRatio;
};

class MannequinContextCommand : public MPxContextCommand
{
public:
  MannequinContextCommand();
  virtual MPxContext* makeObj() override;
  static void* creator();
  virtual MStatus doEditFlags() override;
  virtual MStatus doQueryFlags() override;
  virtual MStatus appendSyntax() override;

private:
  MannequinContext* _mannequinContext;
};