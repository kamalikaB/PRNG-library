# PRNG
A collection of existing PRNG source files with codes for empirical testing with blind tests (Diehard, NIST, battery rabbit of TestU01) and graphical tests (lattice tests and space-time diagram)

These codes are used for our paper "A search for Good Random Number Generators: Survey and Empirical Studies"

The codes of the package "umontreal_pierre_lecuyer" are taken from Prof. Pierre L’Ecuyer's software library. He developed these libarraies in many programming languages. I have used Java and C implementations. Following are the details:
1. Java library "SSJ: Stochastic Simulation in Java", http://simul.iro.umontreal.ca/ssj/indexe.html
   Various RNGs are implemented in the package rng of the SSJ library.   See the documention and the examples from the above URL.  SSJ is available freely on GitHub.
2. C Library: "Random number generators", http://www-labs.iro. umontreal.ca/~simul/rng/ (2017)

For more software libraries, please see:
http://www-labs.iro.umontreal.ca/~simul/clrng/

To run Tauss, first install GSL (GNU Scientific Library) on your machine. For Ubuntu, I followed these steps:
    Download gsl-latest.tar.gz from the GSL ftp site and unzip it anywhere (e.g. /Downloads)
    Open the unzipped gsl folder in Terminal (e.g. cd ~/Downloads/gsl-2.7/) and run the following commands:
    $sudo ./configure 
    $sudo make
    $ sudo make install
    
    
More updates are to be done:

TestU01 sample code
TestU01 sample output and how to compile
Diehard sample code
diehard sample code for 1000 seeds
NIST run procedure
CA codes

