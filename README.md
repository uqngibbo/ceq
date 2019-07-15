# ceq -- Library for Equilibrium Chemistry Calculations

- Author: Nick Gibbons (n.gibbons@uq.edu.au)

- References:

    "Computer Program for Calculation of Complex Equilibrium Compositions and Applications"\
    Nasa Reference Publication 1311, October 1995\
    Sanford Gordon and Bonnie J. McBride\

    "NASA Glenn Coefficients for Calculating Thermodynamic Properties of Individual Species"\
    NASA/TP - 2002-211556, September 2002\
    Bonnie J. McBride, Michael J. Zehe, and Sanford Gordon

- Build Instructions

    Add your preferred install directory to the INSTALL_DIR variable in the makefile. Then type:\
    $ cd source\
    $ make ceq\
    $ make install\


- Use Instructions

    The code is accessed through a python script that handles reading of data, memory management, and initialisation. All of this data is then passed to a set of c routines that do most of the actual work.\
    See examples in the "tests" directory.