# psr_srch_useful
Useful progs relating to searching for (binary) pulsars ...




                                  generate_header.c

Convert an ascii sigproc filterbank header into binary format. This can then be combined
with headerless filterbank format data. 

Compile: gcc -lm generate_header.c -o generate_header

Usage: ./generate_header ascii_header_filename

Note. the ascii header format should match the example ascii header (PM0024_02141_example.asciiheader) format precisely.

                                  generate_aclist.c

Create sigproc trial acceleration and jerk lists using methods described in ...
