#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::ios;

struct Product{
    char name[15];
    unsigned short int width;
    unsigned short int height;
    unsigned short int depth;
    float price;
};

Product ParseLine(const string& line);
void PrintProduct(const Product& product);

int main(int argc, char* argv[]){
    if (argc != 3){
        cerr << "Not enough parameters" << endl;
        return 1;
    }
    string flag = argv[1];
    string file = argv[2];
    if (flag == "-read"){
        ifstream input(file, ios::in | ios::binary);
        if (!input){
            cerr << "unable to open file: " << file << endl;
            return 1;
        }
        Product p;
        int recordCount = 0;
        while (input.read((char*)(&p), sizeof(p))){
            PrintProduct(p);
            recordCount++;
        }
        cout << endl << recordCount << " records read from file" << endl;
        input.close();
    }else if (flag == "-write"){
        ifstream input(file);
        string line;
        Product p;
        if (!input){
            cerr << "unable to open file: " << file << endl;
            return 1;
        }
        string outfile = file;
        outfile.replace(outfile.end() - 3, outfile.end(), "dat");
        ofstream output(outfile, ios::app | ios::out | ios::binary);
        if (!output){
            cerr << "unable to open file: " << outfile << endl;
            return 1;
        }
        int recordCount = 0;
        while (getline(input, line)){
            p = ParseLine(line);
            output.write((char*)(&p), sizeof(p));
            recordCount++;
        }
        cout << recordCount << " Read and Writen to Binary file" << endl;
        input.close();
        output.close();
    }else{
        cerr << "Invalid flag... bye" << endl;
        return 1;
    }

	return 0;
}

Product ParseLine(const string& line){
    Product product;
    stringstream stream(line);
    stream >> product.name >> product.height >> product.width >> product.depth >> product.price;
    return product;
}


void PrintProduct(const Product& product){
    cout << "Product: " << product.name << endl
         << "Height:  " << product.height << endl
         << "Width:   " << product.width << endl
         << "Depth:   " << product.depth << endl
         << "Price:   " << product.price << endl;
}
