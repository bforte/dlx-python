#pragma once

#include <memory>
#include <vector>

class LinkedMatrix {
public:
  using VectorVector = std::vector<std::vector<unsigned>>;
  using NodeId = unsigned;

  static std::unique_ptr<LinkedMatrix>
  from_dense_matrix(const VectorVector& rows, unsigned secondary = 0);

  static std::unique_ptr<LinkedMatrix>
  from_sparse_matrix(unsigned width, const VectorVector& rows, unsigned secondary = 0);

  void cover_column(NodeId id);
  void uncover_column(NodeId id);

  NodeId root_id() const;

  unsigned X(NodeId id) const;
  unsigned Y(NodeId id) const;
  unsigned S(NodeId id) const;
  NodeId C(NodeId id) const;
  NodeId L(NodeId id) const;
  NodeId R(NodeId id) const;
  NodeId U(NodeId id) const;
  NodeId D(NodeId id) const;

private:
  LinkedMatrix();
  void initialize_from_sparse_matrix(unsigned width, const VectorVector& rows, unsigned secondary);

  struct Node;
  NodeId create_node(unsigned x, unsigned y);
  Node& operator[](NodeId id) { return nodes_[id]; }

  std::vector<NodeId> col_ids_;
  std::vector<unsigned> sizes_;
  std::vector<Node> nodes_;

  struct Node
  {
    NodeId id;
    unsigned x, y;
    NodeId l, r, u, d;
    explicit Node(NodeId id_, unsigned x_, unsigned y_)
      : id(id_), x(x_), y(y_),
      l(id), r(id), u(id), d(id)
    {
    }
  };
};

inline auto LinkedMatrix::root_id() const -> NodeId { return 0; }
inline auto LinkedMatrix::X(NodeId id) const -> unsigned { return nodes_[id].x; }
inline auto LinkedMatrix::Y(NodeId id) const -> unsigned { return nodes_[id].y; }
inline auto LinkedMatrix::S(NodeId id) const -> unsigned { return sizes_[X(id)]; }
inline auto LinkedMatrix::C(NodeId id) const -> NodeId { return col_ids_[X(id)]; }
inline auto LinkedMatrix::L(NodeId id) const -> NodeId { return nodes_[id].l; }
inline auto LinkedMatrix::R(NodeId id) const -> NodeId { return nodes_[id].r; }
inline auto LinkedMatrix::U(NodeId id) const -> NodeId { return nodes_[id].u; }
inline auto LinkedMatrix::D(NodeId id) const -> NodeId { return nodes_[id].d; }
