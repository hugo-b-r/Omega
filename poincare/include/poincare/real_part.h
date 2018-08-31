#ifndef POINCARE_REEL_PART_H
#define POINCARE_REEL_PART_H

#include <poincare/layout_helper.h>
#include <poincare/expression.h>
#include <poincare/serialization_helper.h>
#include <poincare/approximation_helper.h>

namespace Poincare {

class RealPartNode : public ExpressionNode  {
public:
  // Allocation Failure
  static RealPartNode * FailedAllocationStaticNode();
  RealPartNode * failedAllocationStaticNode() override { return FailedAllocationStaticNode(); }

  // TreeNode
  size_t size() const override { return sizeof(RealPartNode); }
  int numberOfChildren() const override { return 1; }
#if POINCARE_TREE_LOG
  virtual void logNodeName(std::ostream & stream) const override {
    stream << "RealPart";
  }
#endif

  // Properties
  Type type() const override { return Type::RealPart; }
private:
  // Layout
  LayoutReference createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override {
    return SerializationHelper::Prefix(this, buffer, bufferSize, floatDisplayMode, numberOfSignificantDigits, name());
  }
  const char * name() const { return "re"; }
  // Simplification
  Expression shallowReduce(Context& context, Preferences::AngleUnit angleUnit, const Expression futureParent) override;
  // Evaluation
  template<typename T> static Complex<T> computeOnComplex(const std::complex<T> c, Preferences::AngleUnit angleUnit);
  Evaluation<float> approximate(SinglePrecision p, Context& context, Preferences::AngleUnit angleUnit) const override {
    return ApproximationHelper::Map<float>(this, context, angleUnit,computeOnComplex<float>);
  }
  Evaluation<double> approximate(DoublePrecision p, Context& context, Preferences::AngleUnit angleUnit) const override {
    return ApproximationHelper::Map<double>(this, context, angleUnit, computeOnComplex<double>);
  }
};

class RealPart : public Expression {
public:
  RealPart() : Expression(TreePool::sharedPool()->createTreeNode<RealPartNode>()) {}
  RealPart(const RealPartNode * n) : Expression(n) {}
  RealPart(Expression operand) : RealPart() {
    replaceChildAtIndexInPlace(0, operand);
  }

  Expression shallowReduce(Context& context, Preferences::AngleUnit angleUnit, const Expression futureParent);
};

}

#endif


