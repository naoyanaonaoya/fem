#include "FileWriter.hpp"
#include "Logger.hpp"

#include <cstdlib>
#include <string>

int FileWriter::SSSTTTTEEEPPP = 0;

FileWriter::FileWriter() {
#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter constructor.\n";
#endif
}

FileWriter::~FileWriter() {

#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter destructor.\n";
#endif

    if (in_.is_open())
        in_.close();

    if (out_.is_open())
        out_.close();
}

void FileWriter::Open(const char *file_name) {
    point_data_header_ = 0;
    cell_data_header_ = 0;
    file_name_ = file_name;

    out_.open(file_name, std::ios::out);
    std::cout << "file_name = " << file_name << "\n";
    if (!out_.is_open()) {
        exit(0);
        throw IoException(__FILE__, __LINE__, file_name);
    }
    line_no_ = 0;

#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter::open : " << file_name_ << std::endl;
#endif
}

void FileWriter::OpenBin(const char* file_name) {
    point_data_header_ = 0;
    cell_data_header_ = 0;
    file_name_ = file_name;

    out_.open(file_name, std::ios::out);
    std::cout << "file_name = " << file_name << "\n";
    if (!out_.is_open()) {
        exit(0);
        throw IoException(__FILE__, __LINE__, file_name);
    }
    line_no_ = 0;

#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter::open : " << file_name_ << std::endl;
#endif 
}

void FileWriter::Open(const std::string &file_name) {
    Open(file_name.c_str());
}

void FileWriter::Close() {
    point_data_header_ = 0;
    cell_data_header_ = 0;
    out_.close();

    if(out_.is_open())
        std::cout << "still open" << "\n";
    else
        std::cout << "closed" << "\n";

#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter::close : " << file_name_ << std::endl;
#endif
}

void FileWriter::WriteInt(const int &val, const char *label) {
    out_ << val << std::endl;
}

void FileWriter::WriteBinaryCfdProcData(const char *file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems) {
    file_name_ = file_name;
    OpenBin(file_name);
    // out_.open(file_name, std::ios::out | std::ios::binary);
    // std::size_t n_my_nodes = my_nodes.size();
    // std::size_t n_my_elems = my_elems.size();
    // out_.write((char*)&step, sizeof(std::size_t));
    // out_.write((char*)&n_my_nodes, sizeof(std::size_t));
    // out_.write((char*)&n_my_elems, sizeof(std::size_t));

    // for (std::size_t i = 0; i < n_my_nodes; i++) {
    //     out_.write((char*)&my_nodes[i]->local_index_, sizeof(std::size_t));
    //     out_.write((char*)&my_nodes[i]->vel_.x_, sizeof(double));
    //     out_.write((char*)&my_nodes[i]->vel_.y_, sizeof(double));
    //     out_.write((char*)&my_nodes[i]->vel_.z_, sizeof(double));
    // }

    // for (std::size_t i = 0; i < n_my_elems; i++) {
    //     out_.write((char*)&my_elems[i]->global_index_, sizeof(int));
    //     out_.write((char*)&my_elems[i]->p_, sizeof(double));
    // }
    Close();
}

void FileWriter::WriteBinaryCfdProcData(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elems) {
    WriteBinaryCfdProcData(file_name.c_str(), my_nodes, my_elems);
}

void FileWriter::WriteVtkCfdProcData(const char *file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems) {
    std::cout << "WriteVtkCfdProcData" << "\n";
    Open(file_name);
    WriteVtkDataFileVersion();
    WriteVtkHeader();
    WriteVtkAsciiKeyword();
    WriteVtkDatasetUnstructuredGrid();
    WriteVtkPointsHeader(my_nodes);
    WriteVtkPoints(my_nodes);
    WriteVtkCellsHeader(my_elems);
    WriteVtkCells(my_elems);
    WriteVtkCellTypesHeader(my_elems);
    WriteVtkCellsTypes(my_elems);
    WriteVtkPointsVelocityHeader(my_nodes);
    WriteVtkPointsVelocity(my_nodes);
    WriteVtkPointsMassHeader(my_nodes);
    WriteVtkPointsMass(my_nodes);
    Close();
}

void FileWriter::WriteVtkCfdProcData(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elems) {
    WriteVtkCfdProcData(file_name.c_str(), my_nodes, my_elems);
}

void FileWriter::WriteVtkCfdProcDataOnlyMesh(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elems) {
    std::cout << "WriteVtkCfdProcDataOnlyMesh" << "\n";
    Open(file_name);
    WriteVtkDataFileVersion();
    WriteVtkHeader();
    WriteVtkAsciiKeyword();
    WriteVtkDatasetUnstructuredGrid();
    WriteVtkPointsHeader(my_nodes);
    WriteVtkPoints(my_nodes);
    WriteVtkCellsHeader(my_elems);
    WriteVtkCells(my_elems);
    WriteVtkCellTypesHeader(my_elems);
    WriteVtkCellsTypes(my_elems);
    Close();
}

void FileWriter::WriteVtkCfdProcDataOnlyMesh(const std::string &file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems) {
    WriteVtkCfdProcDataOnlyMesh(file_name.c_str(), my_nodes, my_elems);
}

void FileWriter::WriteVtkDataFileVersion() {
    // Logger::out << "FileWriter::WriteVtkDataFileVersion" << file_name_ << std::endl;
    out_ << "# vtk DataFile Version 2.0" << "\n";
}

void FileWriter::WriteVtkHeader() {
    // Logger::out << "FileWriter::WriteVtkHeader" << file_name_ << std::endl;
    out_ << "HEADER" << "\n";
}

void FileWriter::WriteVtkAsciiKeyword() {
    // Logger::out << "FileWriter::WriteVtkAsciiKeyword" << file_name_ << std::endl;
    out_ << "ASCII" << "\n";
}

void FileWriter::WriteVtkDatasetUnstructuredGrid() {
    // Logger::out << "FileWriter::WriteVtkDatasetUnstructuredGrid" << file_name_ << std::endl;
    out_ << "DATASET UNSTRUCTURED_GRID" << "\n";
}

void FileWriter::WriteVtkPointsHeader(const std::vector<Node*> &my_nodes) {
    // Logger::out << "FileWriter::WriteVtkPointsHeader" << file_name_ << std::endl;
    size_t number_of_nodes = my_nodes.size();
    out_ << "POINTS" << " " << number_of_nodes << " " << "double" << "\n";
}

void FileWriter::WriteVtkPoints(const std::vector<Node*> &my_nodes) {
    // Logger::out << "FileWriter::WriteVtkPoints" << file_name_ << std::endl;
    size_t number_of_nodes = my_nodes.size();
    for (size_t i = 0; i < number_of_nodes; i++)
        out_ << my_nodes[i]->pos_.x_ << " " << my_nodes[i]->pos_.y_ << " " << 0 << "\n";
}

void FileWriter::WriteVtkCellsHeader(const std::vector<ElementQuad*> &my_elems) {
    // Logger::out << "FileWriter::WriteVtkCellsHeader" << file_name_ << std::endl;
    size_t number_f_elems = my_elems.size();
    out_ << "CELLS" << " " << number_f_elems << " " << number_f_elems * 5 << "\n";
}

void FileWriter::WriteVtkCells(const std::vector<ElementQuad*> &my_elems) {
    // Logger::out << "FileWriter::WriteVtkCells" << file_name_ << std::endl;
    size_t number_of_elems = my_elems.size();
    for (size_t i = 0; i < number_of_elems; i++) {
        size_t number_of_nodes = my_elems[i]->GetNumberOfNodes();
        out_ << number_of_nodes << " ";
        for (size_t j = 0; j < number_of_nodes; j++)
            if (j != number_of_nodes - 1)
                out_ << my_elems[i]->nodes_[j]->global_index_<< " ";
            else
                out_ << my_elems[i]->nodes_[j]->global_index_ << "\n";
    }
}

void FileWriter::WriteVtkCellTypesHeader(const std::vector<ElementQuad*> &my_elems) {
    // Logger::out << "FileWriter::WriteVtkCellTypesHeader" << file_name_ << std::endl;
    size_t number_of_elems = my_elems.size();
    out_ << "CELL_TYPES" << " " << number_of_elems << "\n";
}

void FileWriter::WriteVtkCellsTypes(const std::vector<ElementQuad*> &my_elems) {
    // Logger::out << "FileWriter::WriteVtkCellsTypes" << file_name_ << std::endl;
    size_t number_of_elems = my_elems.size();
    for (size_t i = 0; i < number_of_elems; i++) {
        size_t number_of_nodes = my_elems[i]->GetNumberOfNodes();
        if (number_of_nodes == 3)
            out_ << 5 << "\n";
        else if (number_of_nodes == 4)
            out_ << 9 << "\n";
    }
}

void FileWriter::WriteVtkPointsVelocityHeader(const std::vector<Node*> &my_nodes) {
    int number_of_nodes = my_nodes.size();
    if (this->point_data_header_ == 0) {
        out_ << "POINT_DATA" << " " << number_of_nodes << "\n";
        this->point_data_header_ = 1;
    }
    out_ << "VECTORS" << " " << "velocity" << " " << "double" << "\n";
}

void FileWriter::WriteVtkPointsVelocity(const std::vector<Node*> &my_nodes) {
    int number_of_nodes = my_nodes.size();
    for (int i = 0; i < number_of_nodes; i++)
        out_ << my_nodes[i]->vel_.x_ << " " << my_nodes[i]->vel_.y_ << " " << 0 << "\n";
}

void FileWriter::WriteVtkPointsMassHeader(const std::vector<Node*> &my_nodes) {
    int number_of_nodes = my_nodes.size();
    if (this->point_data_header_ == 0) {
        out_ << "POINT_DATA" << " " << number_of_nodes << "\n";
        this->point_data_header_ = 1;
    }
    out_ << "SCALARS" << " " << "mass" << " " << "double" << "\n";
    out_ << "LOOKUP_TABLE" << " " << "default" << "\n";
}


void FileWriter::WriteVtkPointsMass(const std::vector<Node*> &my_nodes) {
    size_t number_of_nodes = my_nodes.size();
    for (int i = 0; i < number_of_nodes; i++)
        out_ << my_nodes[i]->m_ << "\n";
}
