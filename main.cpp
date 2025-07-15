#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

// Exemple de noyau gaussien avec erreur de mesure 
// Kn(u, sigma_u, h) = N(0, 1 + sigma_u^2 / h^2)
double gaussian_noise_kernel(double u, double sigma_u, double h) {
    double total_variance = 1.0 + (sigma_u * sigma_u) / (h * h);
    double exponent = -0.5 * u * u / total_variance;
    return std::exp(exponent) / std::sqrt(2 * M_PI * total_variance);
}

// Estimateur de Nadaraya-Watson avec noyau bruité
template<typename KernelWithNoise>
double mhat_NW(
    double x,
    const std::vector<double>& W,
    const std::vector<double>& Y,
    KernelWithNoise Kn,
    double bnop,
    double SigU
) {
    double Num = 0.0;
    double Den = 0.0;

    for (size_t i = 0; i < W.size(); ++i) {
        double u = (x - W[i]) / bnop;
        double Kval = Kn(u, SigU, bnop);
        Num += Kval * Y[i];
        Den += Kval;
    }

    if (Den == 0.0) return 0.0;

    double ans = Num / Den;
    return std::isnan(ans) ? 0.0 : ans;
}

// la fonction main pour tester avec des donnees 
int main() {
    std::vector<double> W = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> Y = {2.1, 2.9, 4.2, 5.0};
    double x = 2.5;
    double h = 1.0;
    double sigma_u = 0.2;

    double result = mhat_NW(x, W, Y, gaussian_noise_kernel, h, sigma_u);

    std::cout << "Estimation NW avec bruit : " << result << std::endl;
    return 0;
}
