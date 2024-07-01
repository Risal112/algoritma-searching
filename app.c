#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Fungsi binary search parallel
int parallelBinarySearch(long long arr[], int n, long long target) {
    int index = -1;

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        int left = 0;
        int right = n - 1;

        int local_left = left + (right - left) * id / num_threads;
        int local_right = left + (right - left) * (id + 1) / num_threads - 1;

        while (local_left <= local_right && index == -1) {
            int middle = local_left + (local_right - local_left) / 2;

            if (arr[middle] == target) {
                #pragma omp critical
                {
                    if (index == -1) { // Hindari kondisi balapan
                        index = middle;
                    }
                }
                #pragma omp flush(index)
                break;
            } else if (arr[middle] < target) {
                local_left = middle + 1;
            } else {
                local_right = middle - 1;
            }
        }
    }

    return index;
}

int main() {
    int n = 25;  // Jumlah elemen dalam array
    long long arr[] = {
        105841103621,
        105841103721,
        105841103821,
        105841104021,
        105841104121,
        105841104321,
        105841104421,
        105841104521,
        105841104621,
        105841104720,
        105841104821,
        105841104921,
        105841105021,
        105841105121,
        105841105221,
        105841105321,
        105841105421,
        105841105521,
        105841105621,
        105841105721,
        105841105821,
        105841105921,
        105841106021,
        105841106121,
        105841106321,
        105841106421
    };

    const char* names[] = {
        "NUR ALAM",
        "SASTRA CHANDRA KIRANA A",
        "SYAHRIL AKBAR",
        "JEHAN IZATHUL MULIDAH",
        "Faried Kusuma Wardana",
        "Amelia",
        "Reski Anugrah Sari",
        "MAKMUR JAYA NUR",
        "ARGUM LE JAHHTEGIS",
        "MUHAMMAD ASYGAR FAERUDDIN",
        "MUH. RISWAN",
        "Risal",
        "ROMADHAN",
        "MUH. AL IQRAM MARZAH",
        "SARINA",
        "SONY ACHMAD DJAILI",
        "ANUGRAH RESKY SAMUDRA",
        "Rizky Maulia",
        "Rizqih juni setiono",
        "Muhammad Adil Sya'putra",
        "GEMPAR PERKASA TAHIR",
        "ISMI SARIF",
        "NUR ANNISA SYARIFUDDIN",
        "MUH. LUL. AMRI",
        "ULUL AZMI",
        "Rifaul Jamila"
    };

    long long target;
    printf("Masukkan NIM kelas 6B yang ingin dicari: ");
    scanf("%lld", &target);

    int index = parallelBinarySearch(arr, n, target);

    if (index != -1) {
        printf("NIM %lld milik %s ditemukan di indeks %d.\n", target, names[index], index);
    } else {
        printf("NIM %lld tidak ditemukan.\n", target);
    }

    return 0;
}
