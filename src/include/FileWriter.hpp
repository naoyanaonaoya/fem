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

    int point_data_header_;

    int cell_data_header_;

    static int SSSTTTTEEEPPP;

public:

    FileWriter();

    ~FileWriter();

    void Open(const char *file_name);

    void Open(const std::string &file_name);

    void OpenBin(const char *file_name);

    void OpenBin(const std::string &file_name);

    void Close();

    /**
     * @fn
     * @brief
     * @param val
     * @param label
     */
    void WriteInt(const int &val, const char *label);

    void WriteVtkCfdProcData(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elemes);

    void WriteVtkCfdProcData(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elemes);

    void WriteVtkCfdProcDataOnlyMesh(const char *file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elemes);

    void WriteVtkCfdProcDataOnlyMesh(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elemes);

    void WriteVtkDataFileVersion();

    void WriteVtkHeader();

    void WriteVtkAsciiKeyword();

    void WriteVtkDatasetUnstructuredGrid();

    void WriteVtkPointsHeader(const std::vector<Node *> &my_nodes);

    void WriteVtkPoints(const std::vector<Node> &nodes);

    void WriteVtkPoints(const std::vector<Node *> &my_nodes);

    void WriteVtkCellsHeader(const int &num_cells);

    void WriteVtkCellsHeader(const std::vector<ElementQuad*> &my_elems);

    void WriteVtkCells(const std::vector<ElementQuad*> &my_elems);

    void WriteVtkCellTypesHeader(const std::vector<ElementQuad*> &my_elems);

    void WriteVtkCellsTypes(const std::vector<ElementQuad*> &my_elems);

    void WriteVtkPointsVelocityHeader(const std::vector<Node*> &my_nodes);

    void WriteVtkPointsVelocity(const std::vector<Node*> &my_nodes);

    void WriteVtkPointsMassHeader(const std::vector<Node*> &my_nodes);

    void WriteVtkPointsMass(const std::vector<Node*> &my_nodes);

    void WriteBinaryCfdProcData(const char *file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems);

    void WriteBinaryCfdProcData(const std::string &file_name, const std::vector<Node *> &my_nodes, const std::vector<ElementQuad*> &my_elems);
};

#endif // _FILEWRITER_H_
