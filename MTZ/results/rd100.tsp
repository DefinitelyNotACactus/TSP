CPXPARAM_TimeLimit                               3600
CPXPARAM_Read_DataCheck                          1
CPXPARAM_Threads                                 1
CPXPARAM_Read_APIEncoding                        "UTF-8"
CPXPARAM_MIP_Strategy_CallbackReducedLP          0
Tried aggregator 1 time.
MIP Presolve eliminated 1 rows and 101 columns.
Reduced MIP has 9902 rows, 9999 columns, and 48906 nonzeros.
Reduced MIP has 9900 binaries, 99 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.02 sec. (24.10 ticks)
Probing time = 0.02 sec. (6.41 ticks)
Tried aggregator 1 time.
Reduced MIP has 9902 rows, 9999 columns, and 48906 nonzeros.
Reduced MIP has 9900 binaries, 99 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.03 sec. (33.12 ticks)
Probing time = 0.02 sec. (6.40 ticks)
Clique table members: 2600.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: none, using 1 thread.
Root relaxation solution time = 0.01 sec. (18.04 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

      0     0     6573.3000   210                   6573.3000      222         
      0     0     7275.7700   301                   Cuts: 421      503         
      0     0     7349.1200   273                    Cuts: 80      604         
      0     0     7359.2700   274                    Cuts: 56      656         
      0     0     7359.2700   268                    Cuts: 22      676         
      0     0     7359.2700   264                    Cuts: 22      686         
      0     0     7359.2700   246                     Cuts: 9      695         
      0     0     7359.2700   251                    Cuts: 25      706         
      0     2     7359.2700   251                   7361.2700      706         
Elapsed time = 1.72 sec. (2102.29 ticks, tree = 0.01 MB, solutions = 0)
     28    29     7549.2130   207                   7385.4500     1237         
     57    55     7911.9994   161                   7385.4500     1674         
     80    75     8370.0400    95                   7385.4500     2261         
    113   104     9300.1367   111                   7385.4500     2991         
    141   132     9785.6333    71                   7385.4500     3619         
    180   166    10580.4100    31                   7385.4500     3992         
*   228   202      integral     0    12972.0000     7385.4500     4328   43.07%
    230   200        cutoff          12972.0000     7385.4500     4332   43.07%
    265   235     7497.1275   230    12972.0000     7385.4500     4806   43.07%
    298   263     8060.2420   157    12972.0000     7385.4500     5666   43.07%
    427   390     9323.1743    73    12972.0000     7385.4500     8189   43.07%
Elapsed time = 4.02 sec. (5302.06 ticks, tree = 3.04 MB, solutions = 1)
*   480+  432                        12768.0000     7385.4500            42.16%
*   482   433      integral     0    12733.0000     7385.4500     8596   42.00%
    547   498     8265.6833   141    12733.0000     7385.4500     9504   42.00%
*   582+  528                        12404.0000     7385.4500            40.46%
*   692+  424                        10564.0000     7657.2500            27.52%
