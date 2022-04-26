import matplotlib.pyplot as plt
import matplotlib.ticker as mtick

data_points = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900]

results = {
    'plurality': [
        [0.256575, 0.269207, 0.279611, 0.288931, 0.297930, 0.306232, 0.314182, 0.322177, 0.329440, 0.336354, 0.397827,
         0.452445, 0.503197, 0.554909, 0.606599, 0.663145, 0.727315, 0.808059],
        [0.072649, 0.078051, 0.082639, 0.087263, 0.091562, 0.095732, 0.099529, 0.104036, 0.108214, 0.111679, 0.149960,
         0.187874, 0.228835, 0.275130, 0.328421, 0.393504, 0.478699, 0.604918],
        [0.025666, 0.028170, 0.030224, 0.032400, 0.034676, 0.036451, 0.038002, 0.040224, 0.042270, 0.044368, 0.064002,
         0.086089, 0.111872, 0.144427, 0.185553, 0.240513, 0.320241, 0.455381],
        [0.013198, 0.014569, 0.015812, 0.017113, 0.018271, 0.019527, 0.020429, 0.021779, 0.022952, 0.024181, 0.036370,
         0.051087, 0.069043, 0.092747, 0.124656, 0.170488, 0.241693, 0.372557],
        [0.013198, 0.014569, 0.015812, 0.017113, 0.018271, 0.019527, 0.020429, 0.021779, 0.022952, 0.024181, 0.036370,
         0.051087, 0.069043, 0.092747, 0.124656, 0.170488, 0.241693, 0.372557]],
    'borda': [
        [0.268310, 0.288064, 0.304027, 0.317690, 0.330477, 0.341803, 0.353126, 0.363749, 0.373282, 0.382833, 0.461755,
         0.526818, 0.585059, 0.640445, 0.692179, 0.743953, 0.798692, 0.862073],
        [0.074230, 0.082807, 0.089754, 0.096521, 0.102691, 0.108398, 0.114341, 0.119901, 0.125106, 0.130610, 0.180012,
         0.229051, 0.280908, 0.336783, 0.397497, 0.467212, 0.554198, 0.671027],
        [0.026166, 0.029881, 0.032837, 0.035674, 0.038959, 0.041497, 0.044126, 0.046982, 0.049551, 0.052064, 0.078312,
         0.107490, 0.141335, 0.181588, 0.230901, 0.293471, 0.380643, 0.515700],
        [0.013472, 0.015567, 0.017119, 0.018834, 0.020813, 0.022210, 0.023607, 0.025340, 0.026926, 0.028388, 0.044707,
         0.064335, 0.087977, 0.118200, 0.157434, 0.210966, 0.290621, 0.425928],
        [0.013472, 0.015567, 0.017119, 0.018834, 0.020813, 0.022210, 0.023607, 0.025340, 0.026926, 0.028388, 0.044707,
         0.064335, 0.087977, 0.118200, 0.157434, 0.210966, 0.290621, 0.425928]],
}

for name, result in results.items():
    plt.cla()
    plt.figure(constrained_layout=True)
    plt.xlabel(f'Number of samples ({name})')
    plt.ylabel('Average-case Predictability')
    plt.xscale('log')
    plt.ylim(0, 1)
    plt.xlim(10, 900)
    plt.xticks(ticks=[10, 30, 100, 300, 900], labels=[10, 30, 100, 300, 900])
    plt.gca().yaxis.set_major_formatter(mtick.PercentFormatter(1.0, decimals=0))

    for i in range(4):
        plt.plot(data_points, result[i], 'o-', label=f'top-{i + 1}' if i < 3 else 'top-4=top-5')

    plt.legend()
    fig = plt.gcf()
    fig.set_size_inches(5, 4)
    fig.savefig(f'{name}_topk.pdf', dpi=800)
    fig.savefig(f'{name}_topk.png', dpi=800)
    plt.close()