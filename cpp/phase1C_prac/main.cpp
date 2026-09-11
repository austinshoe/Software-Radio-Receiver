#include <cmath>
#include <iostream>
#include <vector>
#include <complex>
#include <numbers>
#include <fstream>

double SingleSine(double amplitude, double freq, int i, double f_s, double phase) {
    return amplitude * std::sin(2 * M_PI * freq * (i / f_s) + phase);
}

double MultiFreqSine(std::vector<double> &freqs, std::vector<double> &amplitudes,
    std::vector<double> &phases, int num_signals, int i, double f_s) {
        double sum = 0.0;
        for (int j = 0; j < num_signals; j++) {
            sum += SingleSine(amplitudes[j], freqs[j], i, f_s, phases[j]);
        }
        return sum;
    }

int main() {
    std::ofstream outFile("test_results.txt", std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    outFile << "New Test\n";
    outFile << "--------\n";
    const double f_s = 10000; //sample frequency
    const double duration = 0.1; // signal duration
    const int N = (int) (f_s * duration); // number of samples total we'll take over the signal duration
    //const double amplitude = 1;
    // const double freq = 1000;
    outFile << "Sample Frequency: " << f_s << " Hz\n";
    outFile << "Signal Duration: " << duration << " s\n";

    std::cout << "Enter how many frequencies you want in the signal: ";
    int num_signals;
    std::cin >> num_signals;

    outFile << "Number of Signal Components: " << num_signals << "\n";
    // const double phase = 0;
    std::vector<double> freqs(num_signals);
    std::vector<double> amplitudes(num_signals);
    std::vector<double> phases(num_signals);

    for (int i = 0; i < num_signals; i++) {
        std::cout << "Enter signal frequency, amplitude, and phase"
        << "(phase angle): ";
        std::cin >> freqs[i] >> amplitudes[i] >> phases[i];

        outFile << "Signal " << i << ": " << freqs[i] << " (Frequency), " << amplitudes[i] << " (Amplitude), "
        << phases[i] << " (Phase Angle)\n";
    }

    std::cout << "Enter the relative-magnitude threshold (between 0 and 1): ";

    double thresh;
    std::cin >> thresh;
    
    outFile << "Relative-magnitude threshold: " << thresh << "\n";

    std::vector<double> samples(N);

    for (int i = 0; i < N; i++) {
        // samples[i] = SingleSine(amplitude,freq, i, f_s, phase);
        samples[i] = MultiFreqSine(freqs, amplitudes,phases, num_signals, i, f_s);
    }

    const double delta_f = f_s / N;

    std::vector<std::complex<double>> X(N); // Transform for each frequency bin k, where the index is k

    std::vector<double> mag(N);

    double mag_l = 0.0; // Largest magnitude
    int index_l = 0; // Largest index

    for (int i = 0; i < N; i++) {
        X[i] = std::complex<double>(0, 0);
        for (int j = 0; j < N; j++) {
            X[i] += std::complex<double>(samples[j]* std::cos(-2 * M_PI * i * j / N),
                samples[j]* std::sin(-2 * M_PI * i * j / N));
        }
        mag[i] = sqrt(std::pow(X[i].real(), 2) + std::pow(X[i].imag(), 2));
        if (mag[i] > mag_l) {
            mag_l = mag[i];
            index_l = i;
        }
    }
    std::vector<int> sig_index(0);
    std::vector<int> sig_freq(0);
    double dft_freq;
    if (mag[0] > mag[1] && mag[0] > mag[N-1] && mag[0] > mag_l * thresh) {
        sig_index.push_back(0);
        dft_freq = 0 * f_s / N;
        sig_freq.push_back(dft_freq);
    }
    else if (mag[N - 1] > mag [N - 2] && mag[N-1] > mag[0] && mag[0] > mag_l * thresh) {
        sig_index.push_back(N - 1);
        dft_freq = -1 * f_s / N;
        sig_freq.push_back(dft_freq);
    }
    
    for (int i = 1; i < N - 1; i++) {
        if (mag[i] > mag[i - 1] && mag[i] > mag[i + 1] && mag[i] > mag_l * thresh) {
            int temp_index = i;
            sig_index.push_back(temp_index);
            double dft_freq;
            if (temp_index > N / 2) {
                temp_index -= N;
            } 
            dft_freq = temp_index * f_s / N;
            sig_freq.push_back(dft_freq);
            std::cout << "Bin " << i << ", Freq: " << dft_freq << std::endl;
            outFile << "Bin " << i << ", Freq: " << dft_freq << "\n";
        }
    }
    outFile << "\n";
    outFile.close();
    

    /* std::cout << "Largest bin: " << index_l << std::endl;
    std::cout << mag[index_l] << " " << mag[N - index_l] << std::endl;
    double dft_freq;
    if (index_l > N / 2) {
        index_l -= N;
    } 
    dft_freq = index_l * f_s / N;
    std::cout << dft_freq << " Hz" << std::endl; */
}