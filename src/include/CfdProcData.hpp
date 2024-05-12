#ifndef _CFDPROCDATA_H_
#define _CFDPROCDATA_H_

#include <vector>
#include "Params.h"
#include "State.h"
#include "Node.h"
#include "QuadElement.h"
#include "Boundary.h"
#include "FileWriter.h"
#include "FileReader.h"

class CfdProcData {

private:

    friend class TestCfdProcData;

    //! all processor Node
    std::vector<Node> nodes_;

    //! my process Node
    std::vector<Node *> my_nodes_;

    std::vector<QuadElement> elements_;

    std::vector<QuadElement *> my_elements_;

    std::vector<Boundary> boundaries_;

public:



};

#endif // _CFDPROCDATA_H_