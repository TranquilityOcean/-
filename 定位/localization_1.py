# -*- coding: utf-8 -*-
"""
Created on Fri Jul  5 10:12:02 2019

@author: 12928
"""
p = [0.2,0.2,0.2,0.2,0.2]
pHit = 0.6
pMiss = 0.2
pExact = 0.8
pOvershoot = 0.1
pUndershoot = 0.1

world = ['green','red','red','green','green']
measurements = ['red','green']
motions = [1,1]
def sense(p,Z):
    q = []
    for i in range(len(world)):
        hit = (Z == world[i])
        q.append(p[i]*(hit * pHit + (1-hit) * pMiss))
    s = sum(q)
    for i in range(len(q)):
        q[i] = q[i] / s
    return q

def move(p,U):
    q = []
    for i in range(len(p)):
        s = p[(i - U) % len(p)] * pExact
        s += p[(i - U -1) % len(p)] * pOvershoot
        s += p[(i - U +1) % len(p)] * pUndershoot
        q.append(s)
    return q

for k in range(len(measurements)):
    p = sense(p,measurements[k])
    p = move(p,motions[k])
print(p)


        
            
            
        
