#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <thread>

int main(int argc, char *argv[]) {
    std::ifstream fin(argv[1]);

    if (!fin.is_open()) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    int flagnumber(0);
    int regionnumber;
    int nodesnumber;
    int elementsnumber;
    int boundnumber;
    int length;
    int itemp;
    int i;
    std::vector<int> node1;
    std::vector<int> node2;
    std::vector<int> node3;
    std::vector<int> node4;
    std::vector<int> nrn;
    std::vector<int> vec_i;
    std::vector<int> bound1;
    std::vector<std::string> nnn;
    std::vector<std::string> nen;
    std::vector<double> vec_a;
    std::vector<double> positionx;
    std::vector<double> positiony;
    std::vector<double> positionz;
    std::vector<std::vector<int> > bnn( 99, std::vector<int>() );
    std::vector<std::vector<int> > bwr;
    double temp;
    double a[] = {1, 0, 0, 0, 0, 0};
    double b[] = {0, 0, 0, 0, 0, 0};
    double c[] = {0, 0, 0, 0, 0, 0};

    bnn.push_back(std::vector<int>());

    std::string line;
    while (std::getline(fin, line))
    {
        if (line[0] == '#')
            continue;

        std::stringstream ss(line);
        std::string name;

        ss >> name;

        if (name == "$MeshFormat") {
            std::cout << "$MeshFormat" << std::endl;
            flagnumber++;
            continue;
        }
        else if (name == "$Nodes") {
            std::cout << "$Nodes" << std::endl;
            flagnumber++;
            continue;
        }
        else if (name == "$EndNodes") {
            std::cout << "$EndNodes" << std::endl;
            flagnumber++;
            continue;
        }
        else if (name == "$Elements") {
            std::cout << "$Elements" << std::endl;
            flagnumber++;
            continue;
        }
        else if (name == "$EndElements") {
            std::cout << "$EndElements" << std::endl;
            flagnumber++;
            continue;
        }
 

        if (flagnumber == 1) {
            std::cout << name << " ";
            while (ss >> temp) {
                vec_a.push_back(temp);
                std::cout << temp << " ";
            }
            std::cout << std::endl;
            if (name != "2.2") break;
            flagnumber++;
        }

        if (flagnumber == 3) {
            std::cout << "Nodes number = " << name << std::endl;
            flagnumber++;
            continue;
        }

        if (flagnumber == 4) {
            std::cout << name << " ";
            while (ss >> temp) {
                vec_a.push_back(temp);
                std::cout << temp << " ";
            }
            std::cout << std::endl;
            nnn.push_back(name);
            length = vec_a.size();
            positionx.push_back(vec_a[length - 3]);
            positiony.push_back(vec_a[length - 2]);
            positionz.push_back(vec_a[length - 1]);
        }

        if (flagnumber == 6) {
            std::cout << "Elements number = " << name << std::endl;
            flagnumber++;
            continue;
        }

        if (flagnumber == 7) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            ss >> itemp;
            if (itemp == 3) {
                std::cout << name << " ";
                vec_i.push_back(itemp);
                std::cout << itemp << " ";
                while (ss >> itemp) {
                    vec_i.push_back(itemp);
                    std::cout << itemp << " ";
                }
                std::cout << std::endl;
                nen.push_back(name);
                length = vec_i.size();
                nrn.push_back(  vec_i[length - 5]);
                node1.push_back(vec_i[length - 4]);
                node2.push_back(vec_i[length - 3]);
                node3.push_back(vec_i[length - 2]);
                node4.push_back(vec_i[length - 1]);
            } else if (itemp == 1) {
                // std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "name = " << name << "\n";
                vec_i.push_back(itemp);
                std::cout << "itemp = " << itemp << "\n";
                while (ss >> itemp) {
                    vec_i.push_back(itemp);
                    std::cout << itemp << " ";
                }
                std::cout << std::endl;
                length = vec_i.size();
                bound1.push_back(vec_i[length - 6]);
                bound1.push_back(vec_i[length - 2]);
                bound1.push_back(vec_i[length - 1]);
                bwr.push_back(bound1);
                std::vector<int>().swap(bound1);

            }

        }


    }

    fin.close();



    std::ofstream fout1(argv[2]);

    if (!fout1)
        return 1;



    regionnumber = *std::max_element(nrn.begin(), nrn.end());
    nodesnumber = nnn.size();
    elementsnumber = nen.size();

    fout1 << regionnumber << " ";
    fout1 << nodesnumber << " ";
    fout1 << elementsnumber << std::endl;

    for (i = 0; i < nodesnumber; i++) {
        fout1 << stoi(nnn[i]) - 1 << " ";
        fout1 << std::setprecision(15) << positionx[i] << " "; 
        fout1 << std::setprecision(15) << positiony[i] << " ";
        fout1 << std::setprecision(15) << 0.0 << std::endl;
    }

    for (i = 0; i < elementsnumber; i++) {
        fout1 << i << " " << node1[i] - 1 << " ";
        fout1 << node2[i] - 1 << " " << node3[i] - 1 << " ";
        fout1 << node4[i] - 1 << " " << 0 << std::endl;
    }

    fout1.close();
     
      
      
    for (unsigned i = 0; i < bwr.size(); i++) {
        itemp = bwr[i][0];
        if (itemp >= 201) {  
            bnn[itemp-201].push_back(bwr[i][1]);
            bnn[itemp-201].push_back(bwr[i][2]);
        }
    }

    for (unsigned i = 0; i < bnn.size(); i++) {
        std::sort(bnn[i].begin(), bnn[i].end());
        bnn[i].erase(std::unique(bnn[i].begin(), bnn[i].end()), bnn[i].end());
    }

    bnn.erase(std::unique(bnn.begin(), bnn.end()), bnn.end());

    std::ofstream fout2(argv[3]);

    if (!fout2)
        return 1;



    boundnumber = bnn.size() - 1;

    fout2 << boundnumber << std::endl;

    for (unsigned i = 0; i < boundnumber; i++) {
        fout2 << i << " " << bnn[i].size() << std::endl;
        fout2 << 1 << " " << 1 << " " << 0 << std::endl;
        for (unsigned j = 0; j < bnn[i].size(); j++)
            if (j != bnn[i].size() - 1)
                fout2 << bnn[i][j] - 1 << " ";
            else
                fout2 << bnn[i][j] - 1 << std::endl;
        for (unsigned j = 0; j < 6; j++)
            if (j != 5)
                fout2 << a[j] << " ";
            else
                fout2 << a[j] << std::endl;
        for (unsigned j = 0; j < 6; j++)
            if (j != 5)
                fout2 << b[j] << " ";
            else
                fout2 << b[j] << std::endl;
        for (unsigned j = 0; j < 6; j++)
            if (j != 5)
                fout2 << c[j] << " ";
            else
                fout2 << c[j] << std::endl;
    }
    fout2 << std::endl;

    fout2.close();

    return 0;

}
