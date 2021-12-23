#include "ortools/linear_solver/linear_solver.h"

namespace operations_research
{
	void BasicLinearSolution()
	{
		std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));

		//Creating variable x and y;
		MPVariable* const x = solver->MakeNumVar(0, 1, "x");
		MPVariable* const y = solver->MakeNumVar(0, 2, "y");

		LOG(INFO) << "Number of variables = " << solver->NumVariables();

		//Creates a linear constraint constraint, x + y <= 2.
		MPConstraint* const ct = solver->MakeRowConstraint(0, 2, "ct");
		//Sets the coefficient of x and y in constraint
		ct->SetCoefficient(x, 1);
		ct->SetCoefficient(y, 1);

		LOG(INFO) << "Number of constraints: " << solver->NumConstraints();

		// Creates the main function which needs to be maximized
		MPObjective* const objective = solver->MutableObjective();
		objective->SetCoefficient(x, 3);
		objective->SetCoefficient(y, 1);
		objective->SetMaximization();

		solver->Solve();

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