# psr_srch_useful
Useful progs relating to searching for (binary) pulsars ...

                                  generate_header.c

Convert an ascii sigproc filterbank header into binary format. This can then be combined
with headerless filterbank format data. 

Compile: gcc -lm generate_header.c -o generate_header

Usage: ./generate_header ascii_header_filename

Note. the ascii header format should match the example ascii header (PM0024_02141_example.asciiheader) format precisely.
                                  
                                  generate_aclist.c

Program to generate a sigproc style acceleration and jerk trial lists using the method outlined in Camilo at al., 2000, ApJ, 535, 975C (spin frequency drifts less than one spectral bin for incorrect trial), or the time domain procedure described in Eatough et al., 2013, MNRAS, 431, 292E (acceptable time domain pulse smearing of 4*t_samp for acceleration that lies exactly in between trials).

Compile:  gcc generate_aclist.c -lm -o generate_aclist

Usage: ./generate_aclist


