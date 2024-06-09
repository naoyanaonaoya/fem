#include "CfdCommData.hpp"

void CfdCommPeerBuffer::AddNode(Node* nodes) {
    halo_nodes_.push_back(nodes);
}

void CfdCommData::Init(Params* params, State* state) {
    params_ = params;
    state_ = state;
}

void CfdCommData::AddHaloNode(std::size_t rank, Node* node) {
    CfdCommPeerBuffer* peer_buffer = FindOrCreatePeerBufferForRank(rank);
    peer_buffer->AddNode(node);
}

CfdCommPeerBuffer* CfdCommData::FindOrCreatePeerBufferForRank(std::size_t rank) {

    std::size_t peer_buffer_size = peer_buffers_.size();
    for (std::size_t i = 0; i < peer_buffer_size; i++)
        if (rank == peer_buffers_[i].rank_)
            return &peer_buffers_[i];

    // If not found, create a new one
    CfdCommPeerBuffer peer_buffer;
    peer_buffer.rank_ = rank;
    peer_buffers_.push_back(peer_buffer);

    // Return the last element
    return &peer_buffers_.back();
}

void CfdCommData::GatherHaloNodeMass() {

}


void CfdCommData::DistributeHaloNodeMass() {

}

void CfdCommData::GatherHaloNodeArrayXYZ() {

}

void CfdCommData::DistributeHaloNodeArrayXYZ() {
    
}
