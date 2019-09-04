"""
Automated test code for ceq

@author: Nick Gibbons
"""
from numpy import array, zeros
import pyeq

def molef_from_massf(Y,Ms):
    Mmix = sum(Y/Ms)**-1
    return Y*Mmix/Ms

def test_pt():
    spnames = 'N2,O2,C2H4,H2,CO,CO2,H2O'.split(',')
    ceq = pyeq.EqCalculator(spnames)
    Ms = ceq.M
    ceaYs0 = array([0.75,  0.2, 0.05, 0.0, 0.0, 0.0, 0.0])
    ceaXst = {
        'CO': 1.2624e-2,
        'CO2': 8.9029e-2,
        'H2': 2.2749e-3,
        'H2O': 9.9379e-2,
        'N2': 7.6349e-1,
        'O2': 3.3208e-2
    }
    Xst = zeros(len(spnames))
    for k,v in ceaXst.items(): Xst[spnames.index(k)] = v

    Xs0 = molef_from_massf(ceaYs0, Ms)

    T = 2500.0
    p = 2.0*101.325e3

    print("Computing")
    Xs1 = ceq.pt(p, T, Xs0, 2)
    print("Done")
    print("Name  Init      Target    Computed")
    for s,k in enumerate(spnames):
        print('{:>4}: {:1.6f}  {:1.6f}  {:1.6f}'.format(k, Xs0[s], Xst[s], Xs1[s]))
    return

if __name__=='__main__':
    test_pt()
    print(' ')
