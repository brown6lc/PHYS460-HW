import matplotlib.pyplot as plt
import numpy as np

# problem 1 comparison between observed and ideal frequencies
def plotFrequencies():

    def rolling_average(data, window=3):
        return np.convolve(data, np.ones(window)/window, mode='same') # compute rolling averages

    sums = np.arange(2, 13)
    observed = [0.0333, 0.0667, 0.0333, 0.0667, 0.2667, 0.2000,
                0.1333, 0.0667, 0.0333, 0.0333, 0.0667]
    ideal = [0.0278, 0.0556, 0.0833, 0.1111, 0.1389, 0.1667,
             0.1389, 0.1111, 0.0833, 0.0556, 0.0278]

    obs_avg = rolling_average(observed, window=3)
    ideal_avg = rolling_average(ideal, window=3)

    x = np.arange(len(sums))
    width = 0.35

    fig, ax = plt.subplots(figsize=(10, 6))
    ax.bar(x - width/2, observed, width, label='Observed Probability', alpha=0.8)
    ax.bar(x + width/2, ideal, width, label='Ideal Probability', alpha=0.8)

    ax.plot(x, obs_avg, marker='o', linewidth=2, label='Observed Rolling Avg')
    ax.plot(x, ideal_avg, marker='o', linewidth=2, linestyle='--', label='Ideal Rolling Avg')

    ax.set_xlabel('Sum of Two Dice')
    ax.set_ylabel('Probability')
    ax.set_xticks(x)
    ax.set_xticklabels(sums)
    ax.legend()
    ax.grid(axis='y', alpha=0.3)

    plt.tight_layout()
    plt.show()


# problem 2 part b
def waveFunction(x, a, b):
    """
    Defines a wave function.
    
    :param x: x value
    :param a: a value
    :param b: b value

    :return: evaulated piecewise function object
    """
    # define conditions
    conditions = [
        (x >= 0) & (x <= a),
        (x > a) & (x <= b),
    ]
    # define functions
    functions = [
        lambda x: np.sqrt(3/b) * (x/a),
        lambda x: np.sqrt(3/b) * ((b-x)/(b-a)),
    ]
    return np.piecewise(x, conditions, functions)

def plotWaveFunction(waveFunction, a, b):
    """
    Plots given wave function.

    :param waveFunction: wave function to plot
    :param a: a value
    :param b: b value
    """
    x = np.linspace(-50, 50, 1000)  # x values
    y = waveFunction(x, a, b)  # y values
    
    fig, ax = plt.subplots()
    ax.plot(x, y)
    
    xmax = x[np.argmax(y)]
    ymax = y.max()
    text = "x={:.3f}, y={:.3f}".format(xmax, ymax)
    
    bbox_props = dict(boxstyle="square,pad=0.3", fc="w", ec="k", lw=0.72)
    arrowprops = dict(arrowstyle="->", connectionstyle="angle,angleA=0,angleB=60")
    kw = dict(xycoords='data', textcoords="axes fraction", 
              arrowprops=arrowprops, bbox=bbox_props, ha="right", va="top")
    ax.annotate(text, xy=(xmax, ymax), xytext=(0.94, 0.96), **kw)
    
    # Add annotation for parameter 'a'
    a_text = "a = {:.3f}".format(a)
    ax.text(0.02, 0.98, a_text, transform=ax.transAxes,
            fontsize=10, verticalalignment='top',
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
    
    plt.xlabel('x')
    plt.ylabel('ψ(x)')
    plt.grid(True)
    plt.show()

# problem 3 part c
"""
Sketch or plot the graph of |Ψ|2, as a function of x, and mark the
points (〈𝑥〉 + 𝜎) and(〈𝑥〉 − 𝜎)
"""
def probDistribution(x, kappa=1):
    return kappa*np.exp(-2*kappa*np.abs(x))

def plotProbDistribution(kappa=1):
    #x expectation val
    expectX = 0
    #x^2 expectation val
    expectXSqrd = (1/(np.sqrt(2)*kappa))
    sigma = np.sqrt(expectXSqrd - np.power(expectX, 2))
    print(f"Standard deviation: {sigma}")

    x = np.linspace(-5, 5, 1000)  # x values
    y = probDistribution(x)  # y values - probability distribution
    # hard coded the expectation values to save some time
    # expectation value +/- sigma
    plusSigma = 0 + sigma
    minusSigma = 0 - sigma

    fig, ax = plt.subplots()
    ax.plot(x, y)
    xmax = x[np.argmax(y)]
    ymax = y.max()
    text = "x={:.3f}, y={:.3f}".format(xmax, ymax)
    
    bbox_props = dict(boxstyle="square,pad=0.3", fc="w", ec="k", lw=0.72)
    arrowprops = dict(arrowstyle="->", connectionstyle="angle,angleA=0,angleB=60")
    kw = dict(xycoords='data', textcoords="axes fraction", 
              arrowprops=arrowprops, bbox=bbox_props, ha="right", va="top")
    ax.annotate(text, xy=(xmax, ymax), xytext=(0.94, 0.96), **kw)
    
    # Plot vertical lines at +/- sigma
    ax.axvline(plusSigma, color='r', linestyle='--')
    ax.axvline(minusSigma, color='r', linestyle='--')
    
    plt.xlabel('x')
    plt.ylabel('ψ(x)')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    plotFrequencies()
    plotWaveFunction(waveFunction, 3, 5)
    plotProbDistribution()
    