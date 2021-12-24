#include <stdio.h>
#include <stdlib.h>
#define MAXCHARS 80

/* Little program to read an ascii sigproc header file and convert to
   binary format. The binary header can then be combined with
   headerless filterbank data. Format of ascii header has to match
   example exactly :/ R.P.Eatough 18/12/2021. */

int main (int argc, char *argv[]) {

  FILE *read_ascii_ptr, *read_ptr, *write_ptr;
  int len, machid, telid, dtyp, nch, nbm, bmid, bit, nifs;
  double a,ra, dec, azst, zast, fch1, foff, tsmp;   
  double tstar;

  /* _mainly_ fixed header parameter strings */
  char hdst_fx[]= "HEADER_START";  
  char rwdat_fx[]= "rawdatafile";
  char rwdat[MAXCHARS];
  char srcnm_fx[] = "source_name";
  char srcnm[MAXCHARS];
  char machid_fx[] = "machine_id";
  char telid_fx[] = "telescope_id";
  char src_ra_fx[] = "src_raj";
  char src_dec_fx[] = "src_dej";
  char azst_fx[] = "az_start";
  char zenast_fx[] = "za_start";
  char dat_typ_fx[] = "data_type";
  char fch1_fx[] = "fch1";
  char foff_fx[] = "foff";
  char nchan_fx[] = "nchans";
  char nbms_fx[] = "nbeams";
  char ibeam_fx[] = "ibeam";
  char nbit_fx[] = "nbits";
  char tstrt_fx[] = "tstart";
  char tsamp_fx[] = "tsamp";
  char nifs_fx[] = "nifs";
  char hdend_fx[] = "HEADER_END";

  /* parse the ascii header file and fill in the variables. */
  if (argc < 2)
    {
      printf("Missing ascii header filename!\nUsage: ./generate_header ascii_header_filename \n");
      return(1);
    }
   else
    {
      read_ascii_ptr = fopen(argv[1], "r");
    }


  printf("Read: %s\n\n", argv[1]);
  
  /* read in the ascii header file */
  fscanf(read_ascii_ptr, "%s", &hdst_fx);
  fscanf(read_ascii_ptr, "%s %s", &rwdat_fx, &rwdat);
  fscanf(read_ascii_ptr, "%s %s", &srcnm_fx, &srcnm);  
  fscanf(read_ascii_ptr, "%s %d", &machid_fx, &machid);  
  fscanf(read_ascii_ptr, "%s %d", &telid_fx, &telid);  
  fscanf(read_ascii_ptr, "%s %lf", &src_ra_fx, &ra);  
  fscanf(read_ascii_ptr, "%s %lf", &src_dec_fx, &dec);  
  fscanf(read_ascii_ptr, "%s %lf", &azst_fx, &azst);  
  fscanf(read_ascii_ptr, "%s %lf", &zenast_fx, &zast);  
  fscanf(read_ascii_ptr, "%s %d", &dat_typ_fx, &dtyp);  
  fscanf(read_ascii_ptr, "%s %lf", &fch1_fx, &fch1);  
  fscanf(read_ascii_ptr, "%s %lf", &foff_fx, &foff);  
  fscanf(read_ascii_ptr, "%s %d", &nchan_fx, &nch);  
  fscanf(read_ascii_ptr, "%s %d", &nbms_fx, &nbm);  
  fscanf(read_ascii_ptr, "%s %d", &ibeam_fx, &bmid);  
  fscanf(read_ascii_ptr, "%s %d", &nbit_fx, &bit);  
  fscanf(read_ascii_ptr, "%s %lf", &tstrt_fx, &tstar);  
  fscanf(read_ascii_ptr, "%s %lf", &tsamp_fx, &tsmp);  
  fscanf(read_ascii_ptr, "%s %d", &nifs_fx, &nifs);  
  fscanf(read_ascii_ptr, "%s", &hdend_fx);  

  /* test print values that were read in */
  printf("%s\n",hdst_fx);
  printf("%s %s\n", rwdat_fx, rwdat);
  printf("%s %s\n", srcnm_fx, srcnm);
  printf("%s %d\n", machid_fx, machid);
  printf("%s %d\n", telid_fx, telid);
  printf("%s %f\n", src_ra_fx, ra);
  printf("%s %f\n", src_dec_fx, dec);
  printf("%s %f\n", azst_fx, azst);
  printf("%s %f\n", zenast_fx, zast);
  printf("%s %d\n", dat_typ_fx, dtyp);
  printf("%s %f\n", fch1_fx, fch1);
  printf("%s %f\n", foff_fx, foff);
  printf("%s %d\n", nchan_fx, nch);
  printf("%s %d\n", nbms_fx, nbm);
  printf("%s %d\n", ibeam_fx, bmid);
  printf("%s %d\n", nbit_fx, bit);
  printf("%s %lf\n", tstrt_fx, tstar);
  printf("%s %f\n", tsamp_fx, tsmp);
  printf("%s %d\n", nifs_fx, nifs);
  printf("%s\n", hdend_fx);

  /* write the header data to a binary format file 
     that can be attached to filterbank format data */
  write_ptr = fopen("output.head","wb");  

  /* write beginning of header */
  len=strlen(hdst_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(hdst_fx,sizeof(char),len,write_ptr); 

  /* rawdata file */  
  len=strlen(rwdat_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(rwdat_fx,sizeof(char),len,write_ptr);
  len=strlen(rwdat);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(rwdat,sizeof(char),len,write_ptr);
  
  /* source name */
  len=strlen(srcnm_fx);
  fwrite(&len,sizeof(int),1,write_ptr); 
  fwrite(srcnm_fx,sizeof(char),len,write_ptr);
  len=strlen(srcnm);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(srcnm,sizeof(char),len,write_ptr);

  /* machine id */
  len=strlen(machid_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(machid_fx,sizeof(char),len,write_ptr);
  fwrite(&machid,sizeof(int),1,write_ptr);

  /* telescope id */
  len=strlen(telid_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(telid_fx,sizeof(char),len,write_ptr);
  fwrite(&telid,sizeof(int),1,write_ptr);

  /* right ascension */
  len=strlen(src_ra_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(src_ra_fx,sizeof(char),len,write_ptr);
  fwrite(&ra,sizeof(double),1,write_ptr);

  /* declination */
  len=strlen(src_dec_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(src_dec_fx,sizeof(char),len,write_ptr);
  fwrite(&dec,sizeof(double),1,write_ptr);

  /* start azimuth angle */
  len=strlen(azst_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(azst_fx,sizeof(char),len,write_ptr);
  fwrite(&azst,sizeof(double),1,write_ptr);

  /* start zenith angle */
  len=strlen(zenast_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(zenast_fx,sizeof(char),len,write_ptr);
  fwrite(&zast,sizeof(double),1,write_ptr);

  /* data type */
  len=strlen(dat_typ_fx);
  fwrite(&len,sizeof(int),1, write_ptr);
  fwrite(dat_typ_fx,sizeof(char),len,write_ptr);
  fwrite(&dtyp,sizeof(int),1,write_ptr);

  /* frequency channel 1 */
  len=strlen(fch1_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(fch1_fx,sizeof(char),len,write_ptr);
  fwrite(&fch1,sizeof(double),1,write_ptr);

  /* channel bandwidth */
  len=strlen(foff_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(foff_fx,sizeof(char),len,write_ptr);
  fwrite(&foff,sizeof(double),1,write_ptr);
  
  /* number of frequency channels */
  len=strlen(nchan_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(nchan_fx,sizeof(char),len,write_ptr);
  fwrite(&nch,sizeof(int),1,write_ptr);

  /* number of beams */
  len=strlen(nbms_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(nbms_fx,sizeof(char),len,write_ptr);
  fwrite(&nbm,sizeof(int),1,write_ptr);

  /* beam ID */
  len=strlen(ibeam_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(ibeam_fx,sizeof(char),len,write_ptr);
  fwrite(&bmid,sizeof(int),1,write_ptr);

  /* number of bits */
  len=strlen(nbit_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(nbit_fx,sizeof(char),len,write_ptr);
  fwrite(&bit,sizeof(int),1,write_ptr);

  /* start time */
  len=strlen(tstrt_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(tstrt_fx,sizeof(char),len,write_ptr);
  fwrite(&tstar,sizeof(double),1,write_ptr);

  /* sampling time */
  len=strlen(tsamp_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(tsamp_fx,sizeof(char),len,write_ptr);
  fwrite(&tsmp,sizeof(double),1,write_ptr);

  /* number of IFs */
  len=strlen(nifs_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(nifs_fx,sizeof(char),len,write_ptr);
  fwrite(&nifs,sizeof(int),1,write_ptr);

  /* end of header marker */
  len=strlen(hdend_fx);
  fwrite(&len,sizeof(int),1,write_ptr);
  fwrite(hdend_fx,sizeof(char),len,write_ptr);

  fclose(write_ptr);

   
  return(0);


}
