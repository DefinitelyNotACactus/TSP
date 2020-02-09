CPXPARAM_TimeLimit                               3600
CPXPARAM_Read_DataCheck                          1
CPXPARAM_Threads                                 1
CPXPARAM_Read_APIEncoding                        "UTF-8"
CPXPARAM_MIP_Strategy_CallbackReducedLP          0
Tried aggregator 1 time.
MIP Presolve eliminated 1 rows and 97 columns.
Reduced MIP has 9122 rows, 9215 columns, and 45030 nonzeros.
Reduced MIP has 9120 binaries, 95 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.02 sec. (22.22 ticks)
Probing time = 0.02 sec. (6.13 ticks)
Tried aggregator 1 time.
Reduced MIP has 9122 rows, 9215 columns, and 45030 nonzeros.
Reduced MIP has 9120 binaries, 95 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.03 sec. (30.09 ticks)
Probing time = 0.01 sec. (6.13 ticks)
Clique table members: 2503.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: none, using 1 thread.
Root relaxation solution time = 0.01 sec. (20.01 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

      0     0    46025.9896   199                  46025.9896      265         
      0     0    49008.7604   256                   Cuts: 344      567         
      0     0    49706.1493   259                   Cuts: 350      691         
      0     0    49706.1493   275                    Cuts: 61      790         
      0     0    49706.1493   277                    Cuts: 59      822         
*     0+    0                        74805.0000    49706.1493            33.55%
*     0+    0                        74434.0000    49706.1493            33.22%
      0     2    49706.1493   245    74434.0000    49706.1493      822   33.22%
Elapsed time = 1.07 sec. (1168.47 ticks, tree = 0.01 MB, solutions = 2)
     15    15    51963.7326   157    74434.0000    49711.0451     1565   33.21%
     40    34    55796.9896    90    74434.0000    49711.0451     1931   33.21%
     70    57    65618.2396    55    74434.0000    49711.0451     2399   33.21%
    105    86    68761.3438    12    74434.0000    49711.0451     3150   33.21%
    124   105    71732.3906    90    74434.0000    49711.0451     3965   33.21%
    149   130    69400.2333   165    74434.0000    49711.0451     4728   33.21%
    181   160    71122.8856    53    74434.0000    49711.0451     5702   33.21%
    218   181    49749.5139   185    74434.0000    49749.5139     6766   33.16%
    251   212    50313.0156   136    74434.0000    49749.6094     7440   33.16%
    360   320    64921.6464   105    74434.0000    49749.6094    11045   33.16%
Elapsed time = 3.07 sec. (4514.38 ticks, tree = 1.82 MB, solutions = 2)
    460   415    72134.2257   121    74434.0000    49749.6094    15097   33.16%
*   481+  286                        73398.0000    53029.7222            27.75%

Clique cuts applied:  11
Cover cuts applied:  11
Implied bound cuts applied:  12
Mixed integer rounding cuts applied:  52
Zero-half cuts applied:  22
Multi commodity flow cuts applied:  24
Gomory fractional cuts applied:  48

Root node processing (before b&c):
  Real time             =    1.07 sec. (1169.04 ticks)
Sequential b&c:
  Real time             =   11.01 sec. (12510.56 ticks)
                          ------------
Total (root+branch&cut) =   12.08 sec. (13679.60 ticks)

KeyboardInterrupt
Solution status =  113 : MIP_abort_feasible
Solution value  =  73398.0
Solution (Instance: instances/gr96.tsp)
[1, 80, 79, 28, 27, 65, 68, 67, 66, 64, 63, 62, 61, 60, 59, 70, 69, 57, 56, 58, 54, 48, 47, 46, 45, 44, 33, 11, 25, 24, 23, 26, 22, 21, 19, 18, 20, 17, 16, 15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 96, 94, 93, 92, 95, 87, 86, 85, 84, 82, 81, 83, 91, 90, 89, 88, 78, 77, 76, 75, 74, 73, 72, 71, 55, 51, 53, 52, 50, 49, 43, 42, 41, 40, 39, 34, 35, 38, 37, 36, 32, 31, 30, 29]
