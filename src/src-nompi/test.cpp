#include <iostream>
#include <vector>
#include <chrono>

// ArrayXYZクラスの定義
class ArrayXYZ {
public:
    double x_, y_, z_;

    ArrayXYZ(double x = 0.0, double y = 0.0, double z = 0.0) : x_(x), y_(y), z_(z) {}

    ArrayXYZ& operator=(const ArrayXYZ& o) {
        if (this != &o) {
            x_ = o.x_;
            y_ = o.y_;
            z_ = o.z_;
        }
        return *this;
    }

    ArrayXYZ& operator=(ArrayXYZ&& o) noexcept {
        if (this != &o) {
            x_ = std::move(o.x_);
            y_ = std::move(o.y_);
            z_ = std::move(o.z_);
        }
        return *this;
    }
};

// ノードクラスの定義
class Node {
public:
    ArrayXYZ vel_;
    ArrayXYZ vel_d_;
};

int main() {
    const std::size_t number_of_my_nodes = 100'000'000;
    std::vector<Node*> my_nodes(number_of_my_nodes);
    for (std::size_t i = 0; i < number_of_my_nodes; ++i) {
        my_nodes.push_back(new Node());
        // my_nodes[i] = new Node();
    }

    // 方法1: 新しいオブジェクトを生成する
    auto start1 = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < number_of_my_nodes; ++i) {
        my_nodes[i]->vel_ = ArrayXYZ(0.0, 0.0, 0.0);
        my_nodes[i]->vel_d_ = ArrayXYZ(0.0, 0.0, 0.0);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Method 1 duration: " << duration1.count() << " seconds" << std::endl;

    // 方法2: 既存のオブジェクトをコピーする
    ArrayXYZ zero(0.0, 0.0, 0.0);
    auto start2 = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < number_of_my_nodes; ++i) {
        my_nodes[i]->vel_ = zero;
        my_nodes[i]->vel_d_ = zero;
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Method 2 duration: " << duration2.count() << " seconds" << std::endl;

    // メモリ解放
    for (std::size_t i = 0; i < number_of_my_nodes; ++i) {
        delete my_nodes[i];
    }

    return 0;
}
