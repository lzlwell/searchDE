# by Jin-Wu Jiang, jwjiang5918@hotmail.com, 28/05/13/Tue

# The Stillinger-Weber parameters in metal units, for MoS2, from fitting phonon dispersion using GULP.
# these entries are in LAMMPS "metal" units:
#   epsilon = eV; sigma = Angstroms
#   other quantities are unitless

# format of a single entry (one or more lines):
#   element 1, element 2, element 3, 
#   epsilon, sigma, a, lambda, gamma, costheta0, A, B, p, q, tol

Mo  S  S  6.0672  0.7590  4.1634  1.0801  0.8568  0.1525  1.0  45.4357  4  0  0.0
Mo  S Mo  0.0000  0.6097  7.0034  0.0000  0.8568  0.1525  1.0 181.8799  4  0  0.0
Mo Mo  S  0.0000  0.6097  7.0034  0.0000  0.8568  0.1525  1.0 181.8799  4  0  0.0
Mo Mo Mo  3.5040  0.6097  7.0034  0.0000  0.0     0.0     1.0 181.8799  4  0  0.0
S   S  S  0.4651  0.6501  5.7837  0.0000  0.0     0.0     1.0 125.0923  4  0  0.0
S   S Mo  0.0000  0.6097  7.0034  0.0000  0.8568  0.1525  1.0 181.8799  4  0  0.0
S  Mo  S  0.0000  0.6097  7.0034  0.0000  0.8568  0.1525  1.0 181.8799  4  0  0.0
S  Mo Mo  6.0672  0.7590  4.1634  1.0801  0.8568  0.1525  1.0  45.4357  4  0  0.0
