#include "ortools/linear_solver/linear_solver.h"

namespace operations_research
{
	void BasicLinearSolution()
	{
		// This example uses SCIP, which is not made by GOOGLE and is used to solve for integer values.
		std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));

		// Creating variable x and y;
		MPVariable *const x = solver->MakeNumVar(0, INFINITY, "x");
		MPVariable *const y = solver->MakeNumVar(0, INFINITY, "y");

		LOG(INFO) << "Number of variables = " << solver->NumVariables();

		// Creates a linear constraint constraint, x + 2y <= 14.
		MPConstraint *const ct = solver->MakeRowConstraint(0, 14);
		// Sets the coefficient of x and y in constraint
		ct->SetCoefficient(x, 1);
		ct->SetCoefficient(y, 2);

		// Creates another constraint, 3x-y >= 0
		MPConstraint *const ct2 = solver->MakeRowConstraint(0, INFINITY);
		ct2->SetCoefficient(x, 3);
		ct2->SetCoefficient(y, -1);

		// Creates another constraint, x-y <= 2
		MPConstraint *const ct3 = solver->MakeRowConstraint(-INFINITY, 2);
		ct3->SetCoefficient(x, 1);
		ct3->SetCoefficient(y, -1);

		LOG(INFO) << "Number of constraints: " << solver->NumConstraints();

		// Creates the main function which needs to be maximized
		MPObjective *const objective = solver->MutableObjective();
		objective->SetCoefficient(x, 3);
		objective->SetCoefficient(y, 4);
		objective->SetMaximization();

		const MPSolver::ResultStatus result_status = solver->Solve();
		// Check that the problem has an optimal solution.
		if (result_status != MPSolver::OPTIMAL)
		{
			LOG(FATAL) << "The problem does not have an optimal solution!";
		}

		LOG(INFO) << "Solution:" << std::endl;
		LOG(INFO) << "Value of function = " << objective->Value();
		LOG(INFO) << "x = " << x->solution_value();
		LOG(INFO) << "y = " << y->solution_value();
	}
}

int main()
{
	operations_research::BasicLinearSolution();
	return EXIT_SUCCESS;
}