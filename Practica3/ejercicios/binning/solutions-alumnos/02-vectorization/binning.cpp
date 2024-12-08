#include <cmath>
#include <omp.h>
#include <cstdlib> 
#include <vector>
#include "util.h"
#include "binning.h"

using namespace std;

void BinParticles(const InputDataType& inputData, BinsType& outputBins) {
  // Reservar espacio para las matrices iX e iY con alineación a 32 bytes
  int *iX = (int*) aligned_alloc(32, inputData.numDataPoints * sizeof(int));
  int *iY = (int*) aligned_alloc(32, inputData.numDataPoints * sizeof(int));

  // Calcular coordenadas y bin numbers
  #pragma omp parallel for
  for (int i = 0; i < inputData.numDataPoints; i++) { 
    const FTYPE x = inputData.particles.r[i] * COS(inputData.particles.phi[i]);
    const FTYPE y = inputData.particles.r[i] * SIN(inputData.particles.phi[i]);
    iX[i] = int((x - xMin) * binsPerUnitX);
    iY[i] = int((y - yMin) * binsPerUnitY);
  }

  // Incrementar los bins correspondientes
  for (int i = 0; i < inputData.numDataPoints; i++) { 
    ++outputBins[iX[i]][iY[i]];
  }

  // Liberar la memoria al finalizar su uso
  free(iX);
  free(iY);
}

// #include <cmath>
// #include <omp.h>
// #include "util.h"
// #include "binning.h"

// using namespace std;

// void BinParticles(const InputDataType& inputData, BinsType& outputBins) {
//   // Loop through all particle coordinates
//   #pragma omp parallel for reduction(+:outputBins)
//   for (int i = 0; i < inputData.numDataPoints; i++) { 
//     // Transforming from cylindrical to Cartesian coordinates:
//     const FTYPE x = inputData.particles.r[i]*COS(inputData.particles.phi[i]);   //cambio
//     const FTYPE y = inputData.particles.r[i]*SIN(inputData.particles.phi[i]);   //cambio

//     // Calculating the bin numbers for these coordinates:
//     const int iX = int((x - xMin)*binsPerUnitX);
//     const int iY = int((y - yMin)*binsPerUnitY);

//     // Incrementing the appropriate bin in the counter
//     ++outputBins[iX][iY];
//   }
// }