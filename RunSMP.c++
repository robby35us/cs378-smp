// -----------------------------
// RunSMP.c++
// Robert Reed and Jordan Graves
// -----------------------------

#include <iostream>
#include "SMP.h"

/** Solve the single marriage problem. */
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    SMP_solve(cin, cout);
    return 0; }
