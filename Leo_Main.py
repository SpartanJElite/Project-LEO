import math as m
import numpy as np

def CenterofGravity(m,x,y,z):
    mass_x = 0
    mass_y = 0
    mass_z = 0
    massTol = 0
    for i in range(len(m)):
        mass_x = m[i]*x[i] + mass_x
        mass_y = m[i]*y[i] + mass_y
        mass_z = m[i]*z[i] + mass_z
        massTol = massTol + m[i]
    CoG_x = mass_x/massTol
    CoG_y = mass_y/massTol
    CoG_z = mass_z/massTol
    return CoG_x,CoG_y,CoG_z
def oswaldFactorStraight(AR):
    e = 1.78*(1-0.045*(AR**(0.68)))-0.64
    return e

    
density = 1.14
b = 5
A = 45
AR = (b**2)/A
e = oswaldFactorStraight(24)
k = 1/(m.pi*AR*e)
print(e)
#Components
a = [1,1,1,1]
b = [2,1,0,1]
arr = np.array([a,b])

[CoG_x,CoG_y,CoG_z] = CenterofGravity(arr[:,0],arr[:,1],arr[:,2],arr[:,3])
print(CoG_x," ",CoG_y," ",CoG_z)