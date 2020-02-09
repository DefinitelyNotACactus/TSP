CPXPARAM_TimeLimit                               3600
CPXPARAM_Read_DataCheck                          1
CPXPARAM_Threads                                 1
CPXPARAM_Read_APIEncoding                        "UTF-8"
CPXPARAM_MIP_Strategy_CallbackReducedLP          0
Tried aggregator 1 time.
MIP Presolve eliminated 1 rows and 43 columns.
Reduced MIP has 1724 rows, 1763 columns, and 8364 nonzeros.
Reduced MIP has 1722 binaries, 41 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.00 sec. (4.49 ticks)
Probing time = 0.01 sec. (3.34 ticks)
Tried aggregator 1 time.
Reduced MIP has 1724 rows, 1763 columns, and 8364 nonzeros.
Reduced MIP has 1722 binaries, 41 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.01 sec. (6.02 ticks)
Probing time = 0.01 sec. (3.32 ticks)
Clique table members: 904.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: none, using 1 thread.
Root relaxation solution time = 0.00 sec. (3.01 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

      0     0     1018.1667    85                   1018.1667       87         
      0     0     1208.0000   108                   Cuts: 153      153         
      0     0     1218.0000   102                    Cuts: 70      213         
      0     0     1219.5000   117                    Cuts: 30      250         
      0     0     1219.5000   111                    Cuts: 26      267         
      0     0     1219.5000   105                    Cuts: 10      278         
      0     0     1219.5000   106                    Cuts: 17      285         
      0     0     1219.5000   100                 ZeroHalf: 6      289         
      0     2     1219.5000   100                   1219.5000      289         
Elapsed time = 0.50 sec. (729.43 ticks, tree = 0.01 MB, solutions = 0)
*    48    39      integral     0     1449.0000     1219.5000     1135   15.84%
*   149   123      integral     0     1444.0000     1220.4127     2267   15.48%
    150   124     1220.4603   114     1444.0000     1220.4637     2282   15.48%
*   261   195      integral     0     1395.0000     1220.5533     3431   12.51%
*   266   194      integral     0     1393.0000     1220.5533     3452   12.38%
    310   224     1226.9286   106     1393.0000     1220.8571     4292   12.36%
*   366+  250                         1372.0000     1221.6984            10.95%
    479   332     1248.8362    77     1372.0000     1221.8921     6803   10.94%
*   530   188      integral     0     1284.0000     1221.9762     7521    4.83%
    640   244     1247.0976   101     1284.0000     1224.6237     9398    4.62%
    800   331     1245.0660   115     1284.0000     1226.4947    11973    4.48%
    967   411     1280.5542    53     1284.0000     1228.1463    14438    4.35%
   1143   515     1282.2927    73     1284.0000     1229.4634    16768    4.25%
   1302   583     1270.6079    95     1284.0000     1230.9643    19244    4.13%
*  1388+  413                         1273.0000     1272.0000             0.08%
   1388   412        cutoff           1273.0000     1272.0000    21251    0.08%

Clique cuts applied:  13
Implied bound cuts applied:  3
Mixed integer rounding cuts applied:  8
Zero-half cuts applied:  16
Gomory fractional cuts applied:  23

Root node processing (before b&c):
  Real time             =    0.50 sec. (729.50 ticks)
Sequential b&c:
  Real time             =    2.92 sec. (3338.38 ticks)
                          ------------
Total (root+branch&cut) =    3.42 sec. (4067.88 ticks)
Solution status =  101 : MIP_optimal
Solution value  =  1273.0
Solution (Instance: instances/swiss42.tsp)
[1, 33, 35, 34, 21, 36, 37, 32, 18, 8, 38, 16, 17, 15, 20, 14, 6, 27, 19, 13, 12, 26, 11, 9, 10, 42, 24, 41, 25, 22, 40, 23, 39, 31, 30, 29, 3, 28, 4, 5, 7, 2]
