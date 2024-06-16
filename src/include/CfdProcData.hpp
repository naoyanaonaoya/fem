#ifndef _CFDPROCDATA_HPP_
#define _CFDPROCDATA_HPP_

#include <vector>
#include "Params.hpp"
#include "State.hpp"
#include "Node.hpp"
#include "Element.hpp"
#include "Boundary.hpp"
#include "FileWriter.hpp"
#include "FileReader.hpp"
#include "CfdCommData.hpp"

class CfdProcData {

private:

    friend class TestCfdProcData;

    //! all processor Node
    std::vector<Node> all_nodes_;

    std::set<std::size_t> all_nodes_indexes_;

    //! my process Node
    std::vector<Node*> my_nodes_;

    std::set<std::size_t> my_nodes_indexes_;

    // std::vector<std::unique_ptr<Element>> all_elems_;
    std::vector<ElementQuad> all_elems_;

    std::set<std::size_t> all_elems_indexes_;

    // std::vector<std::unique_ptr<Element>*> my_elems_;
    std::vector<ElementQuad*> my_elems_;

    std::set<std::size_t> my_elems_indexes_;

    std::vector<Boundary> boundaries_;

    Params* params_;

    State* state_;

    CfdCommData* comm_data_;

    FileReader fr_;

    FileWriter fw_;

    double proc_max_abs_div_;

    double global_max_abs_div_;

    double proc_max_courant_number_;

    double global_max_courant_number_;

public:

    /**
     * @brief initialize CfdProcData
     * 
     * @param params 
     * @param state 
     * @param comm_data 
     */
    void Init(Params* params, State* state, CfdCommData* comm_data);

    void InitZero();

    void CalcInvariants1();

    void CalcInvariants2();
    
    void CalcVelocityPrediction();

    void ApplyVelocityDelta();

    void ApplyBoundaryConditions();

    void CalcDivergenceAndCorrect();

    void SetProcMaxDivToBuffer();

    void GetGlobalMaxDivFromBuffer();

    void GatherHaloNodeMass();

    void DistributeHaloNodeMass();

    void GatherHaloNodeArrayXYZ();

    void DistributeHaloNodeArrayXYZ();

    bool CorretionOccured();

    /**
     * @brief read mesh file
     * 
     */
    void ReadMeshFile();

    /**
     * @brief read boundary file
     * 
     */
    void ReadBoundaryFile();

    void FindOwnData();

    double GetGlobalMaxAbsDiv() const;

    double GetGlobalMaxCourantNumber() const;

    void CalcCourantNumber();

    void WriteMeshFile();

    void WriteRestartFile();

    void ReadRestartFile();

};

#endif // _CFDPROCDATA_HPP_