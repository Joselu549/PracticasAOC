#include <cmath>
#include <omp.h>
#include <cstdlib> 
#include <vector>
#include "util.h"
#include "binning.h"

using namespace std;

void BinParticles(const InputDataType& inputData, BinsType& outputBins) { 
  const int TILE = 8192 * 4096;
  
  // Reservar espacio para las matrices iX e iY con alineación a 32 bytes
  int *iX = (int*) aligned_alloc(32, inputData.numDataPoints * sizeof(int));
  int *iY = (int*) aligned_alloc(32, inputData.numDataPoints * sizeof(int));

  // Calcular coordenadas y bin numbers
  #pragma omp parallel for reduction(+:outputBins)
  for(int i = 0; i < inputData.numDataPoints; i+=TILE){
    for (int ii = i; ii < i+TILE; ii++) { 
      const FTYPE x = inputData.particles.r[ii-i] * COS(inputData.particles.phi[ii-i]);
      const FTYPE y = inputData.particles.r[ii-i] * SIN(inputData.particles.phi[ii-i]);
      iX[ii] = int((x - xMin) * binsPerUnitX);
      iY[ii] = int((y - yMin) * binsPerUnitY);
    }

    // Incrementar los bins correspondientes
    for (int ii = i; ii < i+TILE; ii++) { 
      ++outputBins[iX[ii-i]][iY[ii-i]];
    }
  }
  // Liberar la memoria al finalizar su uso
  free(iX);
  free(iY);
}

