#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

string library = "1234567890~`!@#$%^&*()_-+={}[]:;'< ,>./?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string target;

int random_number(int start, int end) {
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

char mutasi() {
    int i = random_number(0, library.size()- 1);
    return library[i];
}
//untuk random individu, kita harus mengetahui length dari individu tersebut, lalu di random dari library
string create_random_sample() {
    string random_sample = "";
    for (int i = 0; i < target.size(); i++) {
        random_sample += mutasi();
    }
    return random_sample;
}
//individu, terdiri dari kromosom, dan fitness functionnya
class Sample {
public:
    string kromosom;
    int fitness;
    Sample(string kromosom) {
        this->kromosom = kromosom;
        fitness = fitness_counter();
    }
    Sample swap_parent(Sample parent2);
    int fitness_counter();
};


Sample Sample::swap_parent(Sample parent2) {
    string kromosom_baru = "";

    int len = kromosom.size();
    for (int i = 0; i < len; i++) {

        int tes_probabilitas = random_number(0, 100);
        //jika kurang dari 45, child baru diambil dari chromosome parent
        if (tes_probabilitas < 45) {
            kromosom_baru += kromosom[i];
        }
        //jika kurang dari 90, diambil dari chromosome parent 2
        else if (tes_probabilitas < 90) {
            kromosom_baru += parent2.kromosom[i];
        }   
        else {
            kromosom_baru += mutasi();
        }
    }
    return Sample(kromosom_baru);
};

//untuk count, fitness setiap char yang berbeda+1
int Sample::fitness_counter() {

    int length = target.size(), fitness = 0;
    for (int i = 0; i < length; i++) {
        if (kromosom[i] != target[i]) {
            fitness++;
        }
    }
    return fitness;
};
//untuk sort
bool operator<(const Sample& sample1, const Sample& sample2) {
    return sample1.fitness < sample2.fitness;
}

int main() {
    srand(time(NULL));

    int generation = 0, besar_populasi;
    //vector = sekumpulan, dari individu dimasukkan ke dalam vector populasi
    vector <Sample> populasi;   
    string random_sample;

    cout << "Input your string target: ";
    getline(cin, target);

    cout << "Population size for the algorithm: ";
    cin >> besar_populasi;
    //membuat individu baru, sebanyak besar populasi, dan dimasukkan ke populasi 
    for (int i = 0; i < besar_populasi; i++) {
        random_sample = create_random_sample();
        populasi.push_back(Sample(random_sample));
    }
    cout << "\n\nResult : " << endl;
    while (true) {
        //vector populasi (new_sample), terdiri dari individu
        vector <Sample> new_sample;

        //buat_keturunan yang baru, diambil 10% dari individu terbaik(fitness_point point terdekat dengan string)
        int loop = (10 * besar_populasi) / 100;

        sort(populasi.begin(), populasi.end());

        if (populasi[0].fitness <= 0) {
            break;
        }
        //gawe input 10% terbaik, dari populasi sebelumnya
        for (int i = 0; i < loop; i++) {
            new_sample.push_back(populasi[i]);
        }

        loop = (90 * besar_populasi) / 100;

        for (int i = 0; i < loop; i++) {

            int len = populasi.size(), num = random_number(0, besar_populasi/2);
            //menentukan individu parent dengan roulete, 1/2 dari populasi  teratas, karena sudah di sort
            Sample parent1 = populasi[num];
            num = random_number(0, besar_populasi/2);
            //mennentukan individu parent2 dengan roulete lagi
            Sample parent2 = populasi[num];

            //crossover dan mutasi      
            Sample next_gen = parent1.swap_parent(parent2);
            new_sample.push_back(next_gen);
        }
        //show generasi, dan replace populasi ke generasi yang baru dibuat
        //generasi dari populasi terbaik
        populasi = new_sample;
        cout << "Generation: " << generation << "   ";
        cout << "String: " << populasi[0].kromosom << "   ";
        cout << "Fitness: " << populasi[0].fitness << endl;
        generation++;
    }
    cout << "Generation: " << generation << "   ";
    cout << "String: " << populasi[0].kromosom << "   ";
    cout << "Fitness: " << populasi[0].fitness << endl;
}
