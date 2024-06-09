#ifndef _CFDCOMMDATA_HPP_
#define _CFDCOMMDATA_HPP_

#include "Node.hpp"
#include "Params.hpp"
#include "State.hpp"

#include "vector"

class CfdCommPeerBuffer {

private:

public:

    std::size_t rank_;

    // on Halo nodes
    std::vector<Node*> halo_nodes_;

    std::vector<double> send_buffer_;

    std::vector<double> recv_buffer_;

    void AddNode(Node* node);

    void GatherMass();
    
    void DistributeMass();

    void GatherArrayXYZ();

    void DistributeArrayXYZ();
};

class CfdCommData {

public:

    Params* params_;

    State* state_;

    double proc_max_abs_div_;

    double global_max_abs_div_;

    double elapsed_time_;

    std::vector<CfdCommPeerBuffer> peer_buffers_;

    void Init(Params* params, State* state);

    void AddHaloNode(std::size_t rank, Node* node);

    CfdCommPeerBuffer* FindOrCreatePeerBufferForRank(std::size_t rank);

    void GatherHaloNodeMass();

    void DistributeHaloNodeMass();

    void GatherHaloNodeArrayXYZ();

    void DistributeHaloNodeArrayXYZ();

};


#endif // _CFDCOMMDATA_HPP_