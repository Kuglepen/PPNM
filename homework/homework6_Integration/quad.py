import scipy.integrate as integrate
import numpy as np

f2 = lambda x: 1/np.sqrt(x)
f4 = lambda x: np.log(x)/np.sqrt(x)

res2, err2, info2 = integrate.quad(f2, 0, 1, full_output=1)
res4, err4, info4 = integrate.quad(f4, 0, 1, full_output=1)

print("1/sqrt(x):")
print(" value =", res2)
print(" calls =", info2['neval'])

print("\nlog(x)/sqrt(x):")
print(" value =", res4)
print(" calls =", info4['neval'])

f_exp = lambda x: np.exp(-x)
f_gauss = lambda x: np.exp(-x*x)

res_exp, err_exp, info_exp = integrate.quad(f_exp, 0, np.inf, full_output=1)
res_gauss, err_gauss, info_gauss = integrate.quad(f_gauss, -np.inf, np.inf, full_output=1)

print("exp(-x) from 0 to ∞:")
print(" value =", res_exp)
print(" calls =", info_exp['neval'])

print("\nexp(-x^2) from -∞ to ∞:")
print(" value =", res_gauss)
print(" calls =", info_gauss['neval'])