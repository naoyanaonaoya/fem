#include "FileWriter.hpp"
#include "Logger.hpp"

#include <cstdlib>
#include <string>

#ifdef DEBUG_FILEWRITER
#else
#endif

FileWriter::FileWriter() {
    std::cout << "FileWriter constructor.\n";
}


FileWriter::~FileWriter() {
    if (in_.is_open()) {
        in_.close();
    }
    if (out_.is_open()) {
        out_.close();
    }
}

void FileWriter::open(const char *file_name) {
    this->pointDataHeader = 0;
    this->cellDataHeader = 0;
    file_name_ = file_name;

    out_.open(file_name, std::ios::out);
    if (!out_.is_open()) {
        throw IoException(__FILE__, __LINE__, file_name);
    }
    line_no_ = 0;

    Logger::out << "FileWriter::open : " << file_name_ << std::endl;
#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter::open : " << file_name_ << std::endl;
#endif
}

void FileWriter::open(const std::string &file_name) {
    this->open(file_name.c_str());
}

void FileWriter::close() {
    this->pointDataHeader = 0;
    this->cellDataHeader = 0;
    out_.close();
}

void FileWriter::writeInt(const int &val, const char *label) {
    out_ << val << std::endl;
}

void FileWriter::writeVtkCfdProcData(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elems) {
    std::cout << "writeVtkCfdProcData\n";
    this->open(file_name);
    this->writeVtkDataFileVersion();
    this->writeVtkHeader();
    this->writeVtkAsciiKeyword();
    this->writeVtkDatasetUnstructuredGrid();
    this->writeVtkPointsHeader(my_nodes);
    this->writeVtkPoints(my_nodes);
    this->writeVtkCellsHeader(my_elems);
    this->writeVtkCells(my_elems);
    this->writeVtkCellTypesHeader(my_elems);
    this->writeVtkCellsTypes(my_elems);
    this->writeVtkPointsVelocityHeader(my_nodes);
    this->writeVtkPointsVelocity(my_nodes);
    this->writeVtkPointsMassHeader(my_nodes);
    this->writeVtkPointsMass(my_nodes);
    this->close();
}

void FileWriter::writeVtkCfdProcData(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elems) {
    this->writeVtkCfdProcData(file_name.c_str(), my_nodes, my_elems);
}

void FileWriter::writeVtkCfdProcDataOnlyMesh(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elems) {
    std::cout << "writeVtkCfdProcData\n";
    this->open(file_name);
    this->writeVtkDataFileVersion();
    this->writeVtkHeader();
    this->writeVtkAsciiKeyword();
    this->writeVtkDatasetUnstructuredGrid();
    this->writeVtkPointsHeader(my_nodes);
    this->writeVtkPoints(my_nodes);
    this->writeVtkCellsHeader(my_elems);
    this->writeVtkCells(my_elems);
    this->writeVtkCellTypesHeader(my_elems);
    this->writeVtkCellsTypes(my_elems);
    this->close();
}

void FileWriter::writeVtkCfdProcDataOnlyMesh(const std::string &file_name, const std::vector<Node*> &my_nodes, const std::vector<Element*> &my_elems) {
    this->writeVtkCfdProcDataOnlyMesh(file_name.c_str(), my_nodes, my_elems);
}

void FileWriter::writeVtkDataFileVersion() {
    Logger::out << "FileWriter::writeVtkDataFileVersion" << file_name_ << std::endl;
    out_ << "# vtk DataFile Version 2.0\n";
}

void FileWriter::writeVtkHeader() {
    Logger::out << "FileWriter::writeVtkHeader" << file_name_ << std::endl;
    out_ << "HEADER\n";
}

void FileWriter::writeVtkAsciiKeyword() {
    Logger::out << "FileWriter::writeVtkAsciiKeyword" << file_name_ << std::endl;
    out_ << "ASCII\n";
}

void FileWriter::writeVtkDatasetUnstructuredGrid() {
    Logger::out << "FileWriter::writeVtkDatasetUnstructuredGrid" << file_name_ << std::endl;
    out_ << "DATASET UNSTRUCTURED_GRID\n";
}

void FileWriter::writeVtkPointsHeader(const std::vector<Node*> &my_nodes) {
    Logger::out << "FileWriter::writeVtkPointsHeader" << file_name_ << std::endl;
    size_t number_of_nodes = my_nodes.size();
    out_ << "POINTS" << " " << number_of_nodes << " " << "double" << "\n";
}

void FileWriter::writeVtkPoints(const std::vector<Node*> &my_nodes) {
    Logger::out << "FileWriter::writeVtkPoints" << file_name_ << std::endl;
    size_t number_of_nodes = my_nodes.size();
    for (size_t i = 0; i < number_of_nodes; i++)
        out_ << my_nodes[i]->pos_.x_ << " " << my_nodes[i]->pos_.y_ << " " << 0 << "\n";
}

void FileWriter::writeVtkCellsHeader(const std::vector<Element*> &my_elems) {
    Logger::out << "FileWriter::writeVtkCellsHeader" << file_name_ << std::endl;
    size_t number_f_elems = my_elems.size();
    out_ << "CELLS" << " " << number_f_elems << " " << number_f_elems * 5 << "\n";
}

void FileWriter::writeVtkCells(const std::vector<Element*> &my_elems) {
    Logger::out << "FileWriter::writeVtkCells" << file_name_ << std::endl;
    size_t number_of_elems = my_elems.size();
    for (size_t i = 0; i < number_of_elems; i++) {
        // std::cout << "i = " << i << std::endl;
        size_t number_of_nodes = my_elems[i]->GetNumberOfNodes();
        // std::cout << "number_of_nodes = " << number_of_nodes << std::endl;
        out_ << number_of_nodes << " ";
        for (size_t j = 0; j < number_of_nodes; j++) {
            // std::cout << "j = " << j << std::endl;
            if (j != number_of_nodes - 1) {
                // out_ << my_elems[i]->nodes_[j]->global_index_ - 1 << " ";
                out_ << my_elems[i]->nodes_[j]->global_index_<< " ";
            }
            else {
                // out_ << my_elems[i]->nodes_[j]->global_index_ - 1 << "\n";
                out_ << my_elems[i]->nodes_[j]->global_index_ << "\n";
            }
        }
    }
}

void FileWriter::writeVtkCellTypesHeader(const std::vector<Element *> &my_elems) {
    Logger::out << "FileWriter::writeVtkCellTypesHeader" << file_name_ << std::endl;
    size_t number_of_elems = my_elems.size();
    out_ << "CELL_TYPES" << " " << number_of_elems << "\n";
}

void FileWriter::writeVtkCellsTypes(const std::vector<Element *> &my_elems) {
    Logger::out << "FileWriter::writeVtkCellsTypes" << file_name_ << std::endl;
    size_t number_of_elems = my_elems.size();
    for (size_t i = 0; i < number_of_elems; i++) {
        size_t number_of_nodes = my_elems[i]->GetNumberOfNodes();
        // std::cout << "number_of_nodes = " << number_of_nodes << std::endl;
        if (number_of_nodes == 3)
            out_ << 5 << "\n";
        else if (number_of_nodes == 4)
            out_ << 9 << "\n";
    }
}

void FileWriter::writeVtkPointsVelocityHeader(const std::vector<Node*> &my_nodes) {
    int number_of_nodes = my_nodes.size();
    if (this->pointDataHeader == 0) {
        out_ << "POINT_DATA" << " " << number_of_nodes << "\n";
        this->pointDataHeader = 1;
    }
    out_ << "VECTORS" << " " << "velocity" << " " << "double" << "\n";
}

void FileWriter::writeVtkPointsVelocity(const std::vector<Node*> &my_nodes) {
    int number_of_nodes = my_nodes.size();
    for (int i = 0; i < number_of_nodes; i++)
        out_ << my_nodes[i]->vel_.x_ << " " << my_nodes[i]->vel_.y_ << " " << 0 << "\n";
}

void FileWriter::writeVtkPointsMassHeader(const std::vector<Node*> &my_nodes) {
    int number_of_nodes = my_nodes.size();
    if (this->pointDataHeader == 0) {
        out_ << "POINT_DATA" << " " << number_of_nodes << "\n";
        this->pointDataHeader = 1;
    }
    out_ << "SCALARS" << " " << "mass" << " " << "double" << "\n";
    out_ << "LOOKUP_TABLE" << " " << "default" << "\n";
}


void FileWriter::writeVtkPointsMass(const std::vector<Node*> &my_nodes) {
    size_t number_of_nodes = my_nodes.size();
    for (int i = 0; i < number_of_nodes; i++)
        out_ << my_nodes[i]->m_ << "\n";
}
