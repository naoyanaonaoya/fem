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
};

#endif // _FILEWRITER_H_
