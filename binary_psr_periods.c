/*
 * Program prints out the apparent spin period, velocity, acceleration and jerk
 * as a function of time for a hypothetical binary pulsar. Based on updated
 * binary function in Duncan Lorimer's sigproc fake.c (M. Keith, R.P. Eatough 2006).
 *
 * R. P. Eatough 10/05/2023
 *
 */   

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265
#define SPEED_OF_LIGHT 2.99792458e8
#define T_SUN 4.92544947
#define M_SUN 2.0e30
#define G 6.672e-11

struct BinaryParams{
        double orbitalPeriod;   /* Seconds */
        double eccentricity;    /* 0.0 - 1.0 */
        double massPulsar;      /* Solar masses */
        double massCompanion;   /* Solar masses */
        double startPhase;      /* 0.0 - 1.0 to determine way though orbit at start */
        double inclination;     /* Degrees, 60 deg for average inc. */
        double omega;           /* Longitude of periastron */
};

void doppler_params(struct BinaryParams params,double pRest, double time, double *vel, double *accn, double *jer, double *pApp);

int main()
{

  struct BinaryParams binaryParams;
  double period,faketime,obstime,nexttime,timestep;
  double vel_result = 0.0;
  double accn_result = 0.0;
  double jer_result = 0.0;
  double per_result = 0.0;
  
  /* Pulsar and observation parameters in units of seconds. */
  /* *** PSR J0737-3039A */
  period=0.022699;          
  faketime=0.0;
  nexttime=timestep=60.0;   /* 1 minute steps  */
  obstime=8835;             /* In this case obs of one full orbit, or 2.45 hrs */
  
  /* Loop to iterate time step until end of observation time and binary params */
  do
          {

	    /* *** PSR J0737-3039A */
	    binaryParams.orbitalPeriod = 8834.5;     
	    binaryParams.eccentricity = 0.08777;          
	    binaryParams.massPulsar = 1.34;
	    binaryParams.massCompanion = 1.25;
	    binaryParams.startPhase = 0.0;
	    binaryParams.inclination = 88.69;          
	    binaryParams.omega = 87.03;               
	    

	    if(faketime<nexttime)
              {
	       	doppler_params(binaryParams,period,nexttime,&vel_result,&accn_result,&jer_result,&per_result);
		printf("faketime: %.1f period: %.12f velocity: %.12f acceleration: %.12f jerk: %.12f\n",nexttime,per_result,vel_result,accn_result,jer_result);
                nexttime+=timestep;
	      }

	  }  while (nexttime < obstime);

  return 0;

}  


/* *
 *  *    A function for tuning the apparent period of the pulsar as if it were in a binary system.
 *   *   Updated to also output the line of sight velocity, acceleration and jerk. 
 *    * 
 *     */

void doppler_params(struct BinaryParams params,double pRest, double time, double *vel, double *accn, double *jer, double *pApp)
{

        double meanAnomaly;
        double eccentricAnomaly;
        double trueAnomaly;
        double massFunction;
        double asini;
        double omegaB;
	double omega;
	double t0;
        double eNext;
        double incl;
	double du;
        int i;

        incl = params.inclination * (PI/180);

        /* omega appears to have been left out of fake? 26/05/2023  */
	omega = params.omega * (PI/180);
	
        omegaB = 2.0 * PI / params.orbitalPeriod;
        t0 = params.startPhase * params.orbitalPeriod;

        massFunction = pow((params.massCompanion * sin(incl)),3)/pow((params.massCompanion+params.massPulsar),2);

        asini=pow(( M_SUN * massFunction * G * params.orbitalPeriod * params.orbitalPeriod / (4.0*PI*PI)),0.333333333333);


       /* Solve for the Excentric Anomaly.
        *
        * meanAnomaly, M = E - e*sin(E) = omageB * (t-t0)
        *
        */
	
        meanAnomaly = omegaB * (time-t0);

        /* Solver based on tempo where we have replaced "phase" with
           meanAnomaly. R.P. Eatough./N. Wex 20/01/14 */

        /* Compute eccentric anomaly u by iterating Kepler's equation. */

        eccentricAnomaly = meanAnomaly + params.eccentricity
          * sin(meanAnomaly) * (1.0 + params.eccentricity*cos(meanAnomaly));

        /* must initialize to "large" value */
        du = 1.0;
        //du = 0.0;

        while(abs(du) > 1.0e-13) {
          du = (meanAnomaly - (eccentricAnomaly - params.eccentricity * sin(eccentricAnomaly))) /
            (1.0 - params.eccentricity * cos(eccentricAnomaly));

          eccentricAnomaly += du;
        }


        trueAnomaly = 2.0 * atan(
                        sqrt(
                                (1.0 + params.eccentricity)
                                /
                                (1.0 - params.eccentricity)
                        ) * tan(eccentricAnomaly/2.0)
                );


	/* Velocity m/s */
	*vel = omegaB
                * (asini / (sqrt(1.0 - pow(params.eccentricity,2))))
                * (cos(params.omega + trueAnomaly) + params.eccentricity * cos(params.omega));

	/* Acceleration m/s/s */
	*accn = (-1*(omegaB*omegaB)) * (asini / pow(1 - pow(params.eccentricity,2),2)) * pow((1 + (params.eccentricity*cos(trueAnomaly))),2) * sin(params.omega + trueAnomaly);

	/* Jerk m/s/s/s, see Bagchi et al. 2013 */	
        *jer = (-1*(omegaB*omegaB*omegaB)) * (asini / pow(1 - pow(params.eccentricity,2),7/2)) * pow((1 + (params.eccentricity*cos(trueAnomaly))),3) * ( cos(trueAnomaly + params.omega) + params.eccentricity*cos(params.omega) - 3*params.eccentricity*sin(trueAnomaly + params.omega)*sin(trueAnomaly)   ); 
	
	/* Apparent spin period */
        *pApp = pRest / (1.0 - (*vel / SPEED_OF_LIGHT));


}





















