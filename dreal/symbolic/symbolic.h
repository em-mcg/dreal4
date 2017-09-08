/// @file symbolic.h
///
/// This is the header file that we consolidate Drake's symbolic
/// classes and expose them inside of dreal namespace.
///
/// Other files in dreal should include this file and should NOT
/// include files in drake/common directory. Similarly, BUILD files
/// should only have a dependency "//dreal/symbolic:symbolic", not
/// "@drake_symbolic//:symbolic".
///
/// Test cases which need predicates defined in
/// "drake/common/test/symbolic_test_util.h" file should include
/// "dreal/symbolic/symbolic_test_util.h" file and include
/// "//dreal/symbolic:symbolic_test_util" in BUILD file.
///
#pragma once

#include <functional>
#include <set>

#include "symbolic/symbolic_environment.h"
#include "symbolic/symbolic_expression.h"
#include "symbolic/symbolic_expression_visitor.h"
#include "symbolic/symbolic_formula.h"
#include "symbolic/symbolic_formula_visitor.h"
#include "symbolic/symbolic_variable.h"
#include "symbolic/symbolic_variables.h"

namespace dreal {

using drake::hash_value;

using drake::symbolic::Expression;
using drake::symbolic::ExpressionSubstitution;
using drake::symbolic::Formula;
using drake::symbolic::FormulaKind;
using drake::symbolic::Variable;
using drake::symbolic::Variables;
using drake::symbolic::VisitExpression;
using drake::symbolic::VisitFormula;

/// Returns a formula @p f1 ⇒ @p f2.
Formula imply(const Formula& f1, const Formula& f2);

/// Returns a formula @p f1 ⇔ @p f2.
Formula iff(const Formula& f1, const Formula& f2);

// Given @p formulas = {f₁, ..., fₙ} and a @p func : Formula →
// Formula, `map(formulas, func)` returns a set `{func(f₁),
// ... func(fₙ)}`.
std::set<Formula> map(const std::set<Formula>& formulas,
                      const std::function<Formula(const Formula&)>& func);

/// Checks if @p f is atomic.
bool is_atomic(const Formula& f);

/// Checks if @p f is a clause.
bool is_clause(const Formula& f);

/// Checks if @p is in CNF form.
bool is_cnf(const Formula& f);

/// Strengthen the input formula @p f by @p delta.
/// @pre delta > 0
Formula DeltaStrengthen(const Formula& f, double delta);

/// Weaken the input formula @p f by @p delta.
/// @pre delta > 0
Formula DeltaWeaken(const Formula& f, double delta);

}  // namespace dreal