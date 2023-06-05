#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program to generate a sigproc style aclist using the method outlined in Camilo at al., 2000,
   ApJ, 535, 975C (spin frequency drifts less than one spectral bin for incorrect trial), or the
   time domain procedure described in Eatough et al., 2013, MNRAS, 431, 292E (acceptable time domain
   smearing of 4*t_samp for acceleration that lies exactly in between trials). Ralph Eatough 28/07/11. */


int main()
{
  FILE *outfile1, *outfile2, *outfile3;
  char aclist;
  int i, j, k, naccnint1, naccnint2, njerkint2;
  float per, tint, c, accnstep1, accnstep2, jerkstep2, accn1, accn2, jerk2, accnrang, jerrang, naccn1, naccn2, njerk2, tsamp;
  
    printf("#############################################\n");
    printf("Program to generate a sigproc style ac/adlist\n");
    printf("using the Camilo and Lyne/Eatough step sizes.\n");
    printf("#############################################\n");

    /* Info for the Camilo step size */    
    printf("Enter minimum pulse period to search for (sec): ");
    scanf("%f", &per);
    printf("Enter integration time (sec): ");
    scanf("%f", &tint);
    printf("Enter acceleration search range (m/s/s) c.f. Double Pulsar ~250 m/s/s: ");
    scanf("%f", &accnrang);
    printf("Enter jerk search range (m/s/s/s) c.f. Double Pulsar ~0.2 m/s/s/s: ");
    scanf("%f",&jerrang);	

    
    /* Extra info for the Eatough/Lyne step size*/
    printf("Enter sampling interval (us): ");
    scanf("%f", &tsamp);
    printf("\n");
    
    c=2.99E8;
    
    outfile1 = fopen("aclist_Cam", "w");
    outfile2 = fopen("aclist_Eat", "w");
    outfile3 = fopen("adlist_Eat", "w");	    

    /* step size */
    accnstep1 = c*per/(tint*tint);
    accnstep2 = 64*c*(tsamp/1E6)/(tint*tint);
    jerkstep2 = 768*c*(tsamp/1E6)/(tint*tint*tint);	    

    /* number of trials */
    naccn1 = accnrang/accnstep1;
    naccn2 = accnrang/accnstep2;
    njerk2 = jerrang/jerkstep2;

    /* integer number of trials */
    naccnint1 = (long) (naccn1+0.5);
    naccnint2 = (long) (naccn2+0.5);
    njerkint2 = (long) (njerk2+0.5);

    printf("\n");
    printf("Using a stepsize of %f generated with the Camilo method, the number of acceleration trials is %d ---> x2 for each direction +1 for 0 m/s/s, in total is %d trials. \n", accnstep1, naccnint1, 2*naccnint1+1);

    printf("\n");
    printf("Using a stepsize of %f generated with the Lyne/Eatough method, the number of acceleration trials is %d ---> x2 for each direction +1 for 0 m/s/s, in total is %d trials. \n", accnstep2, naccnint2, 2*naccnint2+1);

    printf("\n");
    printf("Using a stepsize of %f generated with the Lyne/Eatough method, the number of jerk trials is %d ---> x2 for each direction +1 for 0 m/s/s/s, in total is %d trials. \n", jerkstep2, njerkint2, 2*njerkint2+1);


    i=0;
    j=0;
    k=0;	

    /* write Camilo list out */
    for (i=-naccnint1; i<naccnint1+1; i++){
      accn1 = i*accnstep1;
      fprintf(outfile1,"%f \n", accn1);
    } 

    /* write Eatough/Lyne list out */
    for (j=-naccnint2; j<naccnint2+1; j++){
      accn2 = j*accnstep2;
      fprintf(outfile2,"%f \n", accn2);
    }

    /* write Eatough/Lyne adlist list out */
    for (k=-njerkint2; k<njerkint2+1; k++){
      jerk2 = k*jerkstep2*100.0;   /* Convert to cm/s/s/s units for seek */
      fprintf(outfile3,"%f \n", jerk2);
    }




    printf("\n");
    printf("Acceleration trials written to aclist_Cam and aclist_Eat\n");
    printf("\n");
    printf("Jerk trials written to adlist_Eat --> CONVERTED to cm/s/s/s!\n");	
    
    fclose(outfile1);
    fclose(outfile2);
    fclose(outfile3);

    return 0;
    
}
