#!/usr/bin/python
import sys
import cplex
import math
from cplex.exceptions import CplexError

#um leitor de instancias em python inspirado no feito pelo laser no kit g2
def readInstance(filePath):
    f = file(filePath, "r")
    text = str(f.read()).split()
    p = 0
    while True:
        if(text[p] == "DIMENSION:" or text[p] == "DIMENSION"):
            p += 1
            break
        p += 1
        
    if text[p] == ":":
        p += 1
        
    n = int(text[p])
    dist = [0] * n
    for i in range(n):
        dist[i] = [0] * n
        
    while True:
        if(text[p] == "EDGE_WEIGHT_TYPE:" or text[p] == "EDGE_WEIGHT_TYPE"):
            p += 1
            break
        p += 1
    
    if text[p] == ":":
        p += 1
        
    ewt = text[p]
    ewf = ""
    
    if ewt == "EXPLICIT":
        while True:
            if(text[p] == "EDGE_WEIGHT_FORMAT:" or text[p] == "EDGE_WEIGHT_FORMAT"):
                p += 1
                break
            p += 1
        if text[p] == ":":
            p += 1
        ewf = text[p]
        
        if ewf == "FULL_MATRIX":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
                
            for i in range(n):
                for j in range(n):
                    dist[i][j] = int(text[p])
                    p += 1
                    
        elif ewf == "UPPER_ROW":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for i in range(n-1):
                for j in range(i+1, n):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
                    
            for i in range(n):
                dist[i][i] = 0
                
        elif ewf == "LOWER_ROW":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
                
            for i in range(1, n):
                for j in range(0, i):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
                    
            for i in range(n):
                dist[i][i] = 0
                
        elif ewf == "UPPER_DIAG_ROW":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for i in range(0, n):
                for j in range(i, n):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
                    
        elif ewf == "LOWER_DIAG_ROW":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for i in range(0, n):
                for j in range(0, i+1):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
        
        elif ewf == "UPPER_COL":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for j in range(1, n):
                for i in range(0, j):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
        
        elif ewf == "LOWER_COL":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for j in range(0, n-1):
                for i in range(j+1, n):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
        
        elif ewf == "UPPER_DIAG_COL":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for j in range(0, n):
                for i in range(0, j+1):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
        
        elif ewf == "LOWER_DIAG_COL":
            while True:
                if(text[p] == "EDGE_WEIGHT_SECTION"):
                    p += 1
                    break
                p += 1
            
            for j in range(0, n):
                for i in range(j, n):
                    dist[i][j] = int(text[p])
                    dist[j][i] = dist[i][j]
                    p += 1
                    
    elif ewt == "EUC_2D":
        while True:
            if(text[p] == "NODE_COORD_SECTION"):
                p += 1
                break
            p += 1
        
        tempCity, x, y = 0, [0.0] * n, [0.0] * n
            
        for i in range(n):
            tempCity = int(text[p])
            p += 1
            x[i] = float(text[p])
            p += 1
            y[i] = float(text[p])
            p += 1
            
        for i in range(0, n):
            for j in range(0, n):
                dist[i][j] = (math.sqrt((x[i] - x[j])**2 + (y[i] - y[j])**2) + 0.5) // 1
        
    elif ewt == "CEIL_2D":
        while True:
            if(text[p] == "NODE_COORD_SECTION"):
                p += 1
                break
            p += 1
        
        tempCity, x, y = 0, [0.0] * n, [0.0] * n
            
        for i in range(n):
            tempCity = int(text[p])
            p += 1
            x[i] = float(text[p])
            p += 1
            y[i] = float(text[p])
            p+= 1
        
        for i in range(0, n):
            for j in range(0, n):
                dist[i][j] = math.ceil(math.sqrt((x[i] - x[j])**2 + (y[i] - y[j])**2))
    
    else:
        print "TIPO NAO SUPORTADO!"
        
    #TODO: GEO
    #TODO: ATT
    f.close()
    
    return n, dist

def createProblem(n, matrix):
    
    prob = cplex.Cplex()
    prob.objective.set_sense(prob.objective.sense.minimize)
    
    for i in range(n):
        for j in range(n):
            prob.variables.add(obj=[matrix[i][j]], lb=[0], ub=[1], types="I", names=["x_" + str(i+1) + "_" + str(j+1)]) #adicionando as variaveis xij

    for j in range(n):
          prob.variables.add(obj=[0], lb=[1], ub=[n], types="I", names=["u_" + str(j+1)]) #adicionando as variaveis uj

    for j in range(n):
       var_list = []
       coeff_list = []
       for i in range(n):
          if j != i:
            var_list.append("x_" + str(i+1) + "_" + str(j+1))
            coeff_list.append(1)
       prob.linear_constraints.add(lin_expr=[[var_list, coeff_list]], senses="E", rhs=[1], names = ["COV1_" + str(i+1)]) #somatorio de xij = 1 p/ todo i pertencente a v, i != j
       
    for i in range(n):
        var_list = []
        coeff_list = []
        for j in range(n):
           if j != i:
             var_list.append("x_" + str(i+1) + "_" + str(j+1))
             coeff_list.append(1)
        prob.linear_constraints.add(lin_expr=[[var_list, coeff_list]], senses="E", rhs=[1], names = ["COV2_" + str(i+1)]) #somatorio de xji = 1 p/ todo i pertencente a v, i != j
    
    prob.linear_constraints.add(lin_expr=[[["u_1"], [1]]], senses="E", rhs=[1], names = ["COV3_1"]) #u1 = 1
    
    for i in range(1, n):
        var_list = []
        coeff_list = []
        for j in range(1, n):
            if i != j:
                prob.linear_constraints.add(lin_expr=[[["u_" + str(i+1), "u_" + str(j+1), "x_" + str(i+1) + "_" + str(j+1)], [1, -1, n]]], senses="L", rhs=[(n - 1)], names = ["COV4_" + str((i+1)*(j+1))]) #ui - uj + nxij <= (n-1)
    return prob

def main():
    try:
        dim, matrix = readInstance(sys.argv[1])
        prob = createProblem(dim, matrix)
        prob.write("modelo.lp")
        prob.solve()
    except CplexError as exc:
        print(exc)
        return

    # solution.get_status() returns an integer code
    print "Solution status = ", prob.solution.get_status(), ":",
    # the following line prints the corresponding string
    print prob.solution.status[prob.solution.get_status()]
    print "Solution value  = ", prob.solution.get_objective_value()
    print "Solution:", str(sys.argv[1])
    
    #for i in range(dim):
        #print prob.solution.get_values("u_" + str(i+1))

    #for i in range(dim):
        #for j in range(dim):
            #if prob.solution.get_values("x_" + str(i+1) + "_" + str(j+1)) == 1:
                #print "x_" + str(i+1) + "_" + str(j+1)
                
if __name__ == "__main__":
   main()

