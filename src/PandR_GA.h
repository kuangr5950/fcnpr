//
// Created by rkuang on 2020/10/20.
//

#ifndef FCNPR_PANDR_GA_H
#define FCNPR_PANDR_GA_H

#include <vector>
#include <unordered_map>
#include <random>

#include "Types.h"

#define GROUP_SCALE 100
#define MAX_GEN 500
#define P_MUTATION 0.2;
#define P_CROSSOVER 0.8;


namespace fcnpr {

    using Individual = struct Individual {
        std::vector<uint64_t> placement;     ///位置编码后的布局
        std::vector<std::unordered_map<std::pair<Node, Node>, Route>> routings;   ///保存节点之间的可行路径(不用编码)
        double fitness;                 ///适应度值
        double refitness;
        double cfitness;
    };

    class PandRGA {
    public:
        PandRGA();
        bool run();
        void pr_result();



    protected:
        uint64_t  random_gen(uint64_t const& m) const;
        std::vector<uint64_t> encode(std::vector<Position> const& placement) const;
        std::vector<Position> decode(std::vector<uint64_t> const& value) const;
        Individual individual_gen();
        void initGroup();
        bool containDuplicate(std::vector<uint64_t> const& vec);

        uint64_t node_cnt();
        uint64_t area();        ///面积计算
        bool path_exist();      ///根据连接关系的两个节点之间的路径是否存在
        bool clock_sync();      ///节点的放置和路径对否满足时钟同步
        bool clock_constraint();///节点的放置是否满足时钟约束
        bool path_route();      ///存在的路径是否可以正确连接
        void fitness_cpt(Individual & indi);
        void routing();

        void crossover();
        void selection(std::vector<Individual>& popu);
        void mutation();
        void select_the_best();


    private:
        std::vector<Position> nodes_pos;     ///节点的具体位置
        double fitness;
        uint64_t N;                  ///网格大小
        uint64_t n_populaitions;     ///种群规模
        uint64_t n_generation;       ///迭代次数
        uint64_t n_nodes;            ///节点个数
        std::vector<Individual> populations;    ///种群
        std::vector<Individual> best_indi;  ///保存最优个体
    };

}

#endif //FCNPR_PANDR_GA_H
