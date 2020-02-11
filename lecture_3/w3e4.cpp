#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int id, p;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	srand(time(NULL) + id * 1000);

	double time_step = (double)rand() / RAND_MAX;

	cout << "Time step of process " << id << " is " << time_step << endl;

	double min_time_step;
	MPI_Request request;

	// non-blocking allreduce
	MPI_Iallreduce(&time_step, &min_time_step, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD, &request);

	// wait "MPI_Iallreduce" finish through detecting returned "request"
	MPI_Wait(&request, MPI_STATUS_IGNORE);

	cout << "Process " << id << " has a minimum time step of " << min_time_step << endl;

	MPI_Finalize();
}