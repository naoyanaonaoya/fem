#include "CfdProcData.hpp"

void CfdProcData::Init(Params* params, State* state, CfdCommData* comm_data) {
    // Hold in member variables for quick reference when needed
    this->params_ = params;
    this->state_ = state;
    this->comm_data_ = comm_data;
}

void CfdProcData::InitZero() {
    std::size_t number_of_my_nodes = this->my_nodes_.size();
    std::size_t number_of_my_elements = this->my_elems_.size();

    ArrayXYZ zero(0.0, 0.0, 0.0);
    for (std::size_t i = 0; i < number_of_my_nodes; i++) {
        this->my_nodes_[i]->vel_ = zero;
        this->my_nodes_[i]->vel_d_ = zero;
    }

    for (std::size_t i = 0; i < number_of_my_elements; i++) {
        this->my_elems_[i]->p_ = 0.0;
    }
}

void CfdProcData::CalcInvariants1() {
    std::size_t n_my_nodes = my_nodes_.size();
    for (std::size_t i = 0; i < n_my_nodes; i++)
        my_nodes_[i]->m_ = 0.0;
    
    std::size_t n_my_elems = my_elems_.size();
    for (std::size_t i = 0; i < n_my_elems; i++)
        my_elems_[i]->CalcInvariants1(params_->re_);
}

void CfdProcData::CalcInvariants2() {
    std::size_t n_my_nodes = my_nodes_.size();
    for (std::size_t i = 0; i < n_my_nodes; i++)
        my_nodes_[i]->CalcMassInv(params_->delta_t_);

    std::size_t n_my_elems = my_elems_.size();
    for (std::size_t i = 0; i < n_my_elems; i++)
        my_elems_[i]->CalcInvariants2(params_->delta_t_);
}

void CfdProcData::CalcVelocityPrediction() {
    std::size_t n_my_elems = my_elems_.size();
    for (std::size_t i = 0; i < n_my_elems; i++)
        my_elems_[i]->CalcVelocityPrediction(params_->delta_t_, params_->re_);

    std::size_t n_my_nodes = my_nodes_.size();
    for (std::size_t i = 0; i < n_my_nodes; i++)
        my_nodes_[i]->GatherVelD();
}

void CfdProcData::ApplyVelocityDelta() {
    std::size_t n_my_nodes = my_nodes_.size();
    for (std::size_t i = 0; i < n_my_nodes; i++)
        my_nodes_[i]->ApplyVelD();
}

void CfdProcData::ApplyBoundaryConditions() {
    // LOG_CFDPRODCATA("applyBoundaryConditions:start");

    // IMPLEMENT ME
    // double c = state_->getT() / params_->t_ramp_;
    double c = 0.5 *  (1 - (std::cos(M_PI * state_->GetT()) / params_->t_ramp_));
    // double c = ((params_->delta_t_ * 1) * (double)state_->getRound() / params_->t_ramp_);
    if (state_->GetT() > params_->t_ramp_) {
        c = 1.0;
    }
    std::size_t n_bounds = this->boundaries_.size();
    for (std::size_t i = 0; i < n_bounds; i++) {
        boundaries_[i].Apply(c);
    }

    // Logger::out << "c: " << c << std::endl;

    // LOG_CFDPRODCATA("applyBoundaryConditions:end");
}

void CfdProcData::CalcDivergenceAndCorrect() {
    proc_max_abs_div_ = 0.0;
    std::size_t n_my_elems = my_elems_.size();
    double div_max_tmp = std::numeric_limits<double>::lowest();
    for (std::size_t i = 0; i < n_my_elems; i++) {
        double abs_div = my_elems_[i]->CalcDivergenceAndCorrect(params_->epsilon_);
        if (abs_div > div_max_tmp)
            div_max_tmp = abs_div;
    }
    proc_max_abs_div_ = div_max_tmp;

    global_max_abs_div_ = proc_max_abs_div_;
    std::size_t n_my_nodes = my_nodes_.size();
    for (std::size_t i = 0; i < n_my_nodes; i++)
        my_nodes_[i]->GatherVelD();
}

void CfdProcData::SetProcMaxDivToBuffer() {
    comm_data_->proc_max_abs_div_ = proc_max_abs_div_;
}

void CfdProcData::GetGlobalMaxDivFromBuffer() {
    global_max_abs_div_ = comm_data_->global_max_abs_div_;
}

double CfdProcData::GetGlobalMaxAbsDiv() const {
    return global_max_abs_div_;
}

double CfdProcData::GetGlobalMaxCourantNumber() const {
    return global_max_courant_number_;
}

void CfdProcData::GatherHaloNodeMass() {
    comm_data_->GatherHaloNodeMass();
}

void CfdProcData::DistributeHaloNodeMass() {
    comm_data_->DistributeHaloNodeMass();
}

void CfdProcData::GatherHaloNodeArrayXYZ() {
    comm_data_->GatherHaloNodeArrayXYZ();
}

void CfdProcData::DistributeHaloNodeArrayXYZ() {
    comm_data_->DistributeHaloNodeArrayXYZ();
}

bool CfdProcData::CorretionOccured() {
    if (global_max_abs_div_ > params_->epsilon_)
        return true;
    return false;
}

void CfdProcData::CalcCourantNumber() {
    proc_max_abs_div_ = 0.0;
    std::size_t n_my_elems = my_elems_.size();
    for (std::size_t i = 0; i < n_my_elems; i++) {
        double courant_number = my_elems_[i]->CalcCourantNumber(params_->delta_t_);
        if (courant_number > proc_max_courant_number_)
            proc_max_courant_number_ = courant_number;
    }
    global_max_courant_number_ = proc_max_courant_number_;
}

void CfdProcData::ReadMeshFile() {
    FileReader fr;

    std::size_t n_procs;
    std::size_t n_nodes;
    std::size_t n_elems;

    fr.Open(params_->mesh_file_name_);

    fr.ReadLine();
    fr.ReadSizeT(n_procs, "Number of Processors");
    fr.ReadSizeT(n_nodes, "Number of Nodes");
    fr.ReadSizeT(n_elems, "Number of Elements");

    all_nodes_.resize(n_nodes);
    all_elems_.reserve(n_elems);

    for (std::size_t i = 0; i < n_nodes; i++) {
        Node* node = &all_nodes_[i];
        node->global_index_ = i;
        fr.ReadLine();
        fr.ReadExpectedSizeT(i, "Node Index");
        fr.ReadDouble(node->pos_.x_, "X");
        fr.ReadDouble(node->pos_.y_, "Y");
        fr.ReadDouble(node->pos_.z_, "Z");
    }

    for (std::size_t i = 0; i < n_elems; i++) {
        Element* elem = &all_elems_[i];
        elem->global_index_ = i;
        // 0-index
        std::size_t n0, n1, n2, n3;
        std::size_t n_nodes;
        std::size_t rank;
        fr.ReadLine();
        fr.ReadExpectedSizeT(i, "Element Index");
        // fr.ReadSizeT(n_nodes, "Number of Nodes");
        fr.ReadSizeT(n0, "n0");
        fr.ReadSizeT(n1, "n1");
        fr.ReadSizeT(n2, "n2");
        fr.ReadSizeT(n3, "n3");
        fr.ReadSizeT(rank, "rank");

        elem->SetNodes( { &all_nodes_[n0], &all_nodes_[n1], &all_nodes_[n2], &all_nodes_[n3] } );
        if (params_->is_single_process_mode_ == true)
            rank = 0;
        elem->SetRank(rank);
    }

    fr.Close();
}

void CfdProcData::ReadBoundaryFile() {
    FileReader fr;

    fr.Open(params_->boundary_file_name_);

    fr.ReadLine();
    size_t n_boundaries;
    fr.ReadSizeT(n_boundaries, "Number of Boundaries");
    boundaries_.resize(n_boundaries);

    for (std::size_t i = 0; i < n_boundaries; i++) {
        Boundary *bound = &boundaries_[i];
        std::size_t n_nodes;
        fr.ReadLine();
        fr.ReadExpectedSizeT(i, "Boundary Index");
        fr.ReadSizeT(n_nodes, "Number of Nodes");
        fr.ReadSizeT(bound->exist_of_x_boundary_, "Exist of X Boundary");
        fr.ReadSizeT(bound->exist_of_y_boundary_, "Exist of Y Boundary");
        fr.ReadSizeT(bound->exist_of_z_boundary_, "Exist of Z Boundary");
        fr.ReadLine();
        for (std::size_t j = 0; j < n_nodes; j++) {
            std::size_t node_index;
            fr.ReadSizeT(node_index, "Node Index");

            bool is_exist = false;
            std::size_t n_nodes = my_nodes_.size();
            for (std::size_t k = 0; k < n_nodes; k++)
                if(my_nodes_[i]->global_index_ == node_index) {
                    is_exist = true;
                    break;
                }

            if (is_exist == true)
                bound->AddNode(&all_nodes_[node_index]);
        }

        fr.ReadLine();
        fr.ReadDouble(bound->a0_ , "a0");
        fr.ReadDouble(bound->a1_ , "a1");
        fr.ReadDouble(bound->a2_ , "a2");
        fr.ReadDouble(bound->a3_ , "a3");
        fr.ReadDouble(bound->a4_ , "a4");
        fr.ReadDouble(bound->a5_ , "a5");
        fr.ReadLine();
        fr.ReadDouble(bound->b0_ , "b0");
        fr.ReadDouble(bound->b1_ , "b1");
        fr.ReadDouble(bound->b2_ , "b2");
        fr.ReadDouble(bound->b3_ , "b3");
        fr.ReadDouble(bound->b4_ , "b4");
        fr.ReadDouble(bound->b5_ , "b5");
        fr.ReadLine();
        fr.ReadDouble(bound->c0_ , "c0");
        fr.ReadDouble(bound->c1_ , "c1");
        fr.ReadDouble(bound->c2_ , "c2");
        fr.ReadDouble(bound->c3_ , "c3");
        fr.ReadDouble(bound->c4_ , "c4");
        fr.ReadDouble(bound->c5_ , "c5");
    }

    fr.Close();
}

void CfdProcData::FindOwnData() {
    std::size_t n_elems = all_elems_.size();
    std::size_t n_nodes = all_nodes_.size();
    
    // search all elemesnts
    for (std::size_t i = 0; i < n_elems; i++)
        if (all_elems_[i].rank_ == params_->my_rank_)
            my_elems_.push_back(&all_elems_[i]);

    // search all nodes
    for (std::size_t i = 0; i < n_nodes; i++) {
        std::size_t n_refs = all_nodes_[i].element_ref_num_;
        std::set<std::size_t> rank_set_own;
        std::set<std::size_t> rank_set_other;
        for (int j = 0; j < n_refs; j++) {
            std::size_t elem_rank = all_nodes_[i].element_refs_[j].element_->rank_;
            if (elem_rank == params_->my_rank_)
                rank_set_own.insert(elem_rank);
            else
                rank_set_other.insert(elem_rank);
        }

        if (rank_set_own.size() == 0)
            continue;
    
        my_nodes_.push_back(&all_nodes_[i]);
        my_nodes_[my_nodes_.size() - 1]->local_index_ = my_nodes_.size() - 1;
        for (std::size_t x : rank_set_other)
            comm_data_->AddHaloNode(x, &all_nodes_[i]);
    }
}

void CfdProcData::WriteMeshFile() {
    
}

void CfdProcData::ReadRestartFile() {
    std::size_t rank = params_->my_rank_;
    std::size_t step = state_->GetRound();
    char buf[1024];
    snprintf(buf, sizeof(buf), params_->restart_file_name_pattern_.c_str(), rank);
    fr_.ReadBinaryCfdProcData(buf, my_nodes_, my_elems_, step);
    state_->ResetRestart(params_->delta_t_, step);
}

void CfdProcData::WriteRestartFile() {
    std::size_t rank = params_->my_rank_;
    std::size_t step = state_->GetRound();
    char buf[1024];
    snprintf(buf, sizeof(buf), params_->restart_file_name_pattern_.c_str(), rank);
    fw_.WriteBinaryCfdProcData(buf, my_nodes_, my_elems_, step);
}