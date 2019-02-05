/*
C library for equilibrium chemistry calculations
    References:
        "Computer Program for Calculation of Complex Equilibrium Compositions and Applications"
        Nasa Reference Publication 1311, October 1995
        Sanford Gordon and Bonnie J. McBride

        "NASA Glenn Coefficients for Calculating Thermodynamic Properties of Individual Species"
        NASA/TP - 2002-211556, September 2002
        Bonnie J. McBride, Michael J. Zehe, and Sanford Gordon

@author: Nick Gibbons
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "pt.h"
#include "rhou.h"
#include "ceq.h"


int pt(double p,double T,double* X0,int nsp,int nel,double* lewis,double* M,double* a,double* X1, int verbose){
    /*
    Compute the equilibrium composition X1 at a fixed temperature and pressure
    Inputs:
        p     : Pressure (Pa)
        T     : Temperature (K)
        X0    : Intial Mole fractions [nsp]
        nsp   : number of species 
        nel   : number of elements 
        lewis : Nasa Lewis Thermodynamic Database Data [nsp*3*9]
        M     : Molar Mass of each species (kg/mol) [nsp]
        a     : elemental composition array [nel,nsp]
        verbose: print debugging information

    Output:
        X1 : Equilibrium Mole Fraction [nsp]  
    */
    return solve_pt(p, T, X0, nsp, nel, lewis, M, a, X1, verbose);
}

int rhou(double rho,double u,double* X0,int nsp,int nel,double* lewis,double* M,double* a,
         double* X1, double* T, int verbose){
    /*
    Compute the equilibrium composition X1 at a fixed volume and internal energy 
    Inputs:
        rho   : target Density (kg/m3)
        u     : target internal energy (J/kg)
        X0    : Intial Mole fractions [nsp]
        nsp   : number of species 
        nel   : number of elements 
        lewis : Nasa Lewis Thermodynamic Database Data [nsp*3*9]
        M     : Molar Mass of each species (kg/mol) [nsp]
        a     : elemental composition array [nel,nsp]
        verbose: print debugging information

    Output:
        X1 : Equilibrium Mole Fraction [nsp]  
        T  : Equilibrium Temperature 
    */
    return solve_rhou(rho, u, X0,nsp,nel, lewis, M, a, X1, T, verbose);
}

int batch_pt(int N, double* p,double* T,double* X0,int nsp,int nel,double* lewis,double* M,double* a,
             double* X1, int verbose){
    /*
    Compute the equilibrium composition X1 at an array of fixed temperatures and pressures
    Inputs:
        N     : Number of T and p's
        p     : Pressure (Pa) [N]
        T     : Temperature (K) [N]
        X0    : Intial Mole fractions [N,nsp]
        nsp   : number of species 
        nel   : number of elements 
        lewis : Nasa Lewis Thermodynamic Database Data [nsp*3*9]
        M     : Molar Mass of each species (kg/mol) [nsp]
        a     : elemental composition array [nel,nsp]
        verbose: print debugging information

    Output:
        X1 : Equilibrium Mole Fraction [N,nsp]  
    */
    double pi, Ti, *X0i, *X1i;
    int i,result;

    for (i=0; i<N; i++){
        Ti = T[i];
        pi = p[i];
        X0i = X0 + i*nsp;
        X1i = X1 + i*nsp;

        result = solve_pt(pi, Ti, X0i, nsp, nel, lewis, M, a, X1i, verbose);
        if (result!=0){
            printf("Error in batch_pt @ position: %d", i);
            return result;
        }
    }
    return 0;
}

int batch_rhou(int N, double* rho,double* u,double* X0,int nsp,int nel,double* lewis,double* M,
               double* a, double* X1, double* T, int verbose){
    /*
    Compute the equilibrium compositions X1 at a number of fixed densities and internal energies 
    Inputs:
        N     : number of rho's and u's
        rho   : target Densities (kg/m3) [N]
        u     : target internal energies (J/kg) [N]
        X0    : Intial Mole fractions [N,nsp]
        nsp   : number of species 
        nel   : number of elements 
        lewis : Nasa Lewis Thermodynamic Database Data [nsp*3*9]
        M     : Molar Mass of each species (kg/mol) [nsp]
        a     : elemental composition array [nel,nsp]
        verbose: print debugging information

    Output:
        X1 : Equilibrium Mole Fractions [N,nsp]  
        T  : Equilibrium Temperatures  [N]
    */
    double rhoi, ui, *X0i, *X1i, *Ti;
    int i,result;

    for (i=0; i<N; i++){
        rhoi = rho[i];
        ui = u[i];
        X0i = X0 + i*nsp;
        X1i = X1 + i*nsp;
        Ti = T + i;

        result = solve_rhou(rhoi, ui, X0i,nsp,nel, lewis, M, a, X1i, Ti, verbose);
        if (result!=0){
            printf("Error in batch_rhou @ position: %d", i);
            return result;
        }
    }
    return 0;
}


int main(){
    printf("Called main in ceq.c!\n");
    return 0;
}
