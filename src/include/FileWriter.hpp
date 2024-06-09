#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_

#include "Node.hpp"
#include "ElementTri.hpp"
#include "ElementQuad.hpp"
#include "DataException.hpp"
#include "IoException.hpp"

#include <fstream>
#include <sstream>
#include <string>

class FileWriter {

private:

    std::string file_name_;

    std::fstream in_;

    std::fstream out_;

    std::stringstream cur_line_;

    int line_no_;

    int pointDataHeader;

    int cellDataHeader;

public:

    FileWriter();

    ~FileWriter();

    void open(const char *file_name);

    void open(const std::string &file_name);

    void close();

    /**
     * @fn
     * @brief
     * @param val
     * @param label
     */
    void writeInt(const int &val, const char *label);

    void writeVtkCfdProcData(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elemes);

    void writeVtkCfdProcData(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elemes);

    void writeVtkCfdProcDataOnlyMesh(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elemes);

    void writeVtkCfdProcDataOnlyMesh(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<Element *> &my_elemes);

    void writeVtkDataFileVersion();

    void writeVtkHeader();

    void writeVtkAsciiKeyword();

    void writeVtkDatasetUnstructuredGrid();

    void writeVtkPointsHeader(const std::vector<Node *> &my_nodes);

    void writeVtkPoints(const std::vector<Node> &nodes);

    void writeVtkPoints(const std::vector<Node *> &my_nodes);

    void writeVtkCellsHeader(const int &num_cells);

    void writeVtkCellsHeader(const std::vector<Element *> &my_elems);

    void writeVtkCells(const std::vector<Element *> &my_elems);

    void writeVtkCellTypesHeader(const std::vector<Element *> &my_elems);

    void writeVtkCellsTypes(const std::vector<Element *> &my_elems);

    void writeVtkPointsVelocityHeader(const std::vector<Node*> &my_nodes);

    void writeVtkPointsVelocity(const std::vector<Node*> &my_nodes);

    void writeVtkPointsMassHeader(const std::vector<Node*> &my_nodes);

    void writeVtkPointsMass(const std::vector<Node*> &my_nodes);

    void WriteBinaryCfdProcData(const std::string &file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems, const int &step) {
        WriteBinaryCfdProcData(file_name.c_str(), my_nodes, my_elems, step);
    }

    void WriteBinaryCfdProcData(const char *file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems, const int &step) {
        file_name_ = file_name;
        out_.open(file_name, std::ios::out | std::ios::binary);

        std::size_t n_my_nodes = my_nodes.size();
        std::size_t n_my_elems = my_elems.size();
        out_.write((char*)&step, sizeof(std::size_t));
        out_.write((char*)&n_my_nodes, sizeof(std::size_t));
        out_.write((char*)&n_my_elems, sizeof(std::size_t));

        for (std::size_t i = 0; i < n_my_nodes; i++) {
            out_.write((char*)&my_nodes[i]->local_index_, sizeof(std::size_t));
            out_.write((char*)&my_nodes[i]->vel_.x_, sizeof(double));
            out_.write((char*)&my_nodes[i]->vel_.y_, sizeof(double));
            out_.write((char*)&my_nodes[i]->vel_.z_, sizeof(double));
        }

        for (std::size_t i = 0; i < n_my_elems; i++) {
            out_.write((char*)&my_elems[i]->global_index_, sizeof(int));
            out_.write((char*)&my_elems[i]->p_, sizeof(double));
        }
    }
};

#endif // _FILEWRITER_H_
