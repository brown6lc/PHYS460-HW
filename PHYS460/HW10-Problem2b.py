import numpy as np
import matplotlib.pyplot as plt

r = np.linspace(0, 8, 500)
P = 4 * r**2 * np.exp(-2 * r)

plt.plot(r, P)
plt.axvline(1.0,      linestyle='--', label=r'$r_{mp} = a_0$')
plt.axvline(1.5,      linestyle='--', label=r'$\langle r \rangle = 1.5\,a_0$')
plt.axvline(3**0.5,   linestyle='--', label=r'$\sqrt{\langle r^2 \rangle} = \sqrt{3}\,a_0$')
plt.xlabel(r'$r/a_0$')
plt.ylabel(r'$P(r)\cdot a_0$')
plt.legend()
plt.tight_layout()
plt.grid(True)
plt.show()

