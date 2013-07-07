/*
 * File: graph.h
 * -------------
 * This interface exports a parameterized <code>Graph</code> class used
 * to represent <i>graphs,</i> which consist of a set of <i>nodes</i>
 * and a set of <i>arcs</i>.
 */

#ifndef _graph_h
#define _graph_h

#include <string>
#include "map.h"
#include "set.h"

/*
 * Class: Graph<NodeType,ArcType>
 * ------------------------------
 * This class represents a graph with the specified node and arc types.
 * The <code>NodeType</code> and <code>ArcType</code> parameters indicate
 * the structure type or class used for nodes and arcs, respectively.
 * These types can contain any fields or methods required by the client,
 * but must contain the following fields required by the <code>Graph</code>
 * package itself:
 *
 * The <code>NodeType</code> definition must include:
 *   - A <code>string</code> field called <code>name</code>
 *   - A <code>Set&lt;ArcType *&gt;</code> field called <code>arcs</code>
 *
 * The <code>ArcType</code> definition must include:
 *   - A <code>NodeType *</code> field called <code>start</code>
 *   - A <code>NodeType *</code> field called <code>finish</code>
 */

template <typename NodeType,typename ArcType>
class Graph {

public:

/*
 * Constructor: Graph
 * Usage: Graph<NodeType,ArcType> g;
 * ---------------------------------
 * Creates an empty <code>Graph</code> object.
 */

   Graph();

/*
 * Destructor: ~Graph
 * ------------------
 * Frees the internal storage allocated to represent the graph.
 */

   ~Graph();

/*
 * Method: size
 * Usage: int size = g.size();
 * ---------------------------
 * Returns the number of nodes in the graph.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (g.isEmpty()) . . .
 * -----------------------------
 * Returns <code>true</code> if the graph is empty.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: g.clear();
 * -----------------
 * Reinitializes the graph to be empty, freeing any heap storage.
 */

   void clear();

/*
 * Method: addNode
 * Usage: NodeType *node = g.addNode(name);
 *        NodeType *node = g.addNode(node);
 * ----------------------------------------
 * Adds a node to the graph.  The first version of this method
 * creates a new node of the appropriate type and initializes its
 * fields; the second assumes that the client has already created
 * the node and simply adds it to the graph.  Both versions of this
 * method return a pointer to the node.
 */

   NodeType *addNode(std::string name);
   NodeType *addNode(NodeType *node);

/*
 * Method: removeNode
 * Usage: g.removeNode(name);
 *        g.removeNode(node);
 * --------------------------
 * Removes a node from the graph, where the node can be specified
 * either by its name or as a pointer value.  Removing a node also
 * removes all arcs that contain that node.
 */

   void removeNode(std::string name);
   void removeNode(NodeType *node);

/*
 * Method: getNode
 * Usage: NodeType *node = g.getNode(name);
 * ----------------------------------------
 * Looks up a node in the name table attached to the graph and
 * returns a pointer to that node.  If no node with the specified
 * name exists, <code>getNode</code> returns <code>NULL</code>.
 */

   NodeType *getNode(std::string name) const;

/*
 * Method: addArc
 * Usage: g.addArc(s1, s2);
 *        g.addArc(n1, n2);
 *        g.addArc(arc);
 * ---------------------
 * Adds an arc to the graph.  The endpoints of the arc can be specified
 * either as strings indicating the names of the nodes or as pointers
 * to the node structures.  Alternatively, the client can create the arc
 * structure explicitly and pass that pointer to the <code>addArc</code>
 * method.  All three of these versions return a pointer to the arc in
 * case the client needs to capture this value.
 */

   ArcType *addArc(std::string s1, std::string s2);
   ArcType *addArc(NodeType *n1, NodeType *n2);
   ArcType *addArc(ArcType *arc);

/*
 * Method: removeArc
 * Usage: g.removeArc(s1, s2);
 *        g.removeArc(n1, n2);
 *        g.removeArc(arc);
 * ------------------------
 * Removes an arc from the graph, where the arc can be specified in any
 * of three ways: by the names of its endpoints, by the node pointers
 * at its endpoints, or as an arc pointer.  If more than one arc
 * connects the specified endpoints, all of them are removed.
 */

   void removeArc(std::string s1, std::string s2);
   void removeArc(NodeType *n1, NodeType *n2);
   void removeArc(ArcType *arc);

/*
 * Method: isConnected
 * Usage: if (g.isConnected(n1, n2)) . . .
 *        if (g.isConnected(s1, s2)) . . .
 * ---------------------------------------
 * Returns <code>true</code> if the graph contains an arc from
 * <code>n1</code> to <code>n2</code>.  As in the <code>addArc</code>
 * method, nodes can be specified either as node pointers or by name.
 */

   bool isConnected(NodeType *n1, NodeType *n2) const;
   bool isConnected(std::string s1, std::string s2) const;

/*
 * Method: getNodeSet
 * Usage: foreach (NodeType *node in g.getNodeSet()) . . .
 * -------------------------------------------------------
 * Returns the set of all nodes in the graph.
 */

   Set<NodeType *> & getNodeSet();

/*
 * Method: getArcSet
 * Usage: foreach (ArcType *arc in g.getArcSet()) . . .
 *        foreach (ArcType *arc in g.getArcSet(node)) . . .
 *        foreach (ArcType *arc in g.getArcSet(name)) . . .
 * --------------------------------------------------------
 * Returns the set of all arcs in the graph or, in the second and
 * third forms, the arcs that start at the specified node, which
 * can be indicated either as a pointer or by name.
 */

   Set<ArcType *> & getArcSet();
   Set<ArcType *> & getArcSet(NodeType *node);
   Set<ArcType *> & getArcSet(std::string name);

/*
 * Method: getNeighbors
 * Usage: foreach (NodeType *node in g.getNeighbors(node)) . . .
 *        foreach (NodeType *node in g.getNeighbors(name)) . . .
 * -------------------------------------------------------------
 * Returns the set of nodes that are neighbors of the specified
 * node, which can be indicated either as a pointer or by name.
 */

   Set<NodeType *> getNeighbors(NodeType *node);
   Set<NodeType *> getNeighbors(std::string node);

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Class: GraphComparator
 * ----------------------
 * This template class establishes the ordering for nodes and arcs.
 * Nodes are processed in alphabetical order by node name; arcs are
 * compared in much the same way, looking first at the start node and
 * then continuing on to look at the finish node if the start nodes
 * match.  These functions, however, indicate equality only if the
 * arguments are identical, in the sense that they are at the same
 * address.  If two distinct arcs, for example, connect the same pair
 * of nodes (which is perfectly legal in the graph abstraction and can
 * be used, for example, to represent multiple modes of travel between
 * two nodes), those arcs are not the same.
 */

   class GraphComparator {
   public:

      bool operator()(NodeType *n1, NodeType *n2) {
         return compare(n1, n2) < 0;
      }

      bool operator()(ArcType *a1, ArcType *a2) {
         return compare(a1, a2) < 0;
      }

   };

private:

/* Instance variables */

   Set<NodeType *> nodes;                 /* The set of nodes in the graph */
   Set<ArcType *> arcs;                   /* The set of arcs in the graph  */
   Map<std::string, NodeType *> nodeMap;  /* A map from names to nodes     */
   GraphComparator comparator;            /* The comparator for this graph */

/*
 * Functions: operator=, copy constructor
 * --------------------------------------
 * These functions are part of the public interface of the class but are
 * defined here to avoid adding confusion to the Graph class.
 */

public:

   Graph & operator=(const Graph & rhs);
   Graph(const Graph & rhs);

   static int compare(NodeType *n1, NodeType *n2) {
      if (n1 == n2) return 0;
      if (n1->name < n2->name) return -1;
      if (n1->name > n2->name) return +1;
      return (n1 < n2) ? -1 : +1;
   }

   static int compare(ArcType *a1, ArcType *a2) {
      if (a1 == a2) return 0;
      NodeType *n1 = a1->start;
      NodeType *n2 = a2->start;
      if (n1 != n2) return compare(n1, n2);
      n1 = a1->finish;
      n2 = a2->finish;
      if (n1 != n2) return compare(n1, n2);
      return (a1 < a2) ? -1 : +1;
   }

private:

   void deepCopy(const Graph & src);
   NodeType *getExistingNode(std::string name) const;

};

extern void error(std::string msg);

/*
 * Implementation notes: Graph constructor
 * ---------------------------------------
 * Even though the body of the Graph constructor is empty, important
 * work is done by the initializers, which ensure that the nodes and
 * arcs set are given the correct comparison functions.
 */

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>::Graph() {
   comparator = GraphComparator();
   nodes = Set<NodeType *>(comparator);
   arcs = Set<ArcType *>(comparator);
}

/*
 * Implementation notes: Graph destructor
 * --------------------------------------
 * The destructor must free all heap storage used by this graph to
 * represent the nodes and arcs.  The clear metho must also reclaim
 * this memory, which means that the destructor can simply call
 * clear to do the work.
 */

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>::~Graph() {
   clear();
}

/*
 * Implementation notes: size, isEmpty
 * -----------------------------------
 * These methods are defined in terms of the node set, so the implementation
 * simply forwards the request there.  Note that it is impossible for a
 * graph to have arcs if it has no nodes.
 */

template <typename NodeType,typename ArcType>
int Graph<NodeType,ArcType>::size() const {
   return nodes.size();
}

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::isEmpty() const {
   return nodes.isEmpty();
}

/*
 * Implementation notes: clear
 * ---------------------------
 * The implementation of clear first frees the nodes and arcs in
 * their respective sets and then uses the Set class clear method
 * to ensure that these sets are empty.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::clear() {
   foreach (NodeType *node in nodes) {
      delete node;
   }
   foreach (ArcType *arc in arcs) {
      delete arc;
   }
   arcs.clear();
   nodes.clear();
   nodeMap.clear();
}

/*
 * Implementation notes: addNode
 * -----------------------------
 * The addNode method appears in two forms: one that creates a node
 * from its name and one that assumes that the client has created
 * the new node.  In each case, the implementation must add the node
 * the set of nodes for the graph and add the name-to-node association
 * to the node map.
 */

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::addNode(std::string name) {
   NodeType *node = new NodeType();
   node->arcs = Set<ArcType *>(comparator);
   node->name = name;
   return addNode(node);
}

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::addNode(NodeType *node) {
   if (nodeMap.containsKey(node->name)) {
      error("addNode: node " + node->name + " already exists");
   }
   nodes.add(node);
   nodeMap[node->name] = node;
   return node;
}

/*
 * Implementation notes: removeNode
 * --------------------------------
 * The removeNode method must remove the specified node but must
 * also remove any arcs in the graph containing the node.  To avoid
 * changing the node set during iteration, this implementation creates
 * a vector of arcs that require deletion.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeNode(std::string name) {
   removeNode(getExistingNode(name));
}

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeNode(NodeType *node) {
   Vector<ArcType *> toRemove;
   foreach (ArcType *arc in arcs) {
      if (arc->start == node || arc->finish == node) {
         toRemove.add(arc);
      }
   }
   foreach (ArcType *arc in toRemove) {
      removeArc(arc);
   }
   nodes.remove(node);
}

/*
 * Implementation notes: getNode, getExistingNode
 * ----------------------------------------------
 * The getNode method simply looks up the name in the map, which correctly
 * returns NULL if the name is not found.  Other methods in the
 * implementation call the private method getExistingNode instead,
 * which checks for a NULL value and signals an error.
 */

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::getNode(std::string name) const {
   return nodeMap.get(name);
}

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::getExistingNode(std::string name) const {
   NodeType *node = nodeMap.get(name);
   if (node == NULL) error("Graph class: No node named " + name);
   return node;
}

/*
 * Implementation notes: addArc
 * ----------------------------
 * The addArc method appears in three forms, as described in the
 * interface.  The code for each form of the method, however, is
 * quite straightforward.
 */

template <typename NodeType,typename ArcType>
ArcType *Graph<NodeType,ArcType>::addArc(std::string s1, std::string s2) {
   return addArc(getExistingNode(s1), getExistingNode(s2));
}

template <typename NodeType,typename ArcType>
ArcType *Graph<NodeType,ArcType>::addArc(NodeType *n1, NodeType *n2) {
   ArcType *arc = new ArcType();
   arc->start = n1;
   arc->finish = n2;
   return addArc(arc);
}

template <typename NodeType,typename ArcType>
ArcType *Graph<NodeType,ArcType>::addArc(ArcType *arc) {
   arc->start->arcs.add(arc);
   arcs.add(arc);
   return arc;
}

/*
 * Implementation notes: removeArc
 * -------------------------------
 * These methods remove arcs from the graph, which is ordinarily simply
 * a matter of removing the arc from two sets: the set of arcs in the
 * graph as a whole and the set of arcs in the starting node.  The
 * methods that remove an arc specified by its endpoints, however,
 * must take account of the fact that there might be more than one
 * such arc and delete all of them.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeArc(std::string s1, std::string s2) {
   removeArc(getExistingNode(s1), getExistingNode(s2));
}

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeArc(NodeType *n1, NodeType *n2) {
   Vector<ArcType *> toRemove;
   foreach (ArcType *arc in arcs) {
      if (arc->start == n1 && arc->finish == n2) {
         toRemove.add(arc);
      }
   }
   foreach (ArcType *arc in toRemove) {
      removeArc(arc);
   }
}

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeArc(ArcType *arc) {
   arc->start->arcs.remove(arc);
   arcs.remove(arc);
}

/*
 * Implementation notes: isConnected
 * ---------------------------------
 * Node n1 is connected to n2 if any of the arcs leaving n1 finish at n2.
 * The two versions of this method allow nodes to be specified either as
 * node pointers or by name.
 */

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::isConnected(NodeType *n1, NodeType *n2) const {
   foreach (ArcType *arc in n1->arcs) {
      if (arc->finish == n2) return true;
   }
   return false;
}

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::isConnected(std::string s1,
                                          std::string s2) const {
   return isConnected(getExistingNode(s1), getExistingNode(s2));
}

/*
 * Implementation notes: getNodeSet, getArcSet
 * -------------------------------------------
 * These methods simply return the set requested by the client.  The
 * sets are returned by reference for efficiency, because doing so
 * eliminates the need to copy the set.
 */

template <typename NodeType,typename ArcType>
Set<NodeType *> & Graph<NodeType,ArcType>::getNodeSet() {
   return nodes;
}

template <typename NodeType,typename ArcType>
Set<ArcType *> & Graph<NodeType,ArcType>::getArcSet() {
   return arcs;
}

template <typename NodeType,typename ArcType>
Set<ArcType *> & Graph<NodeType,ArcType>::getArcSet(NodeType *node) {
   return node->arcs;
}

template <typename NodeType,typename ArcType>
Set<ArcType *> & Graph<NodeType,ArcType>::getArcSet(std::string name) {
   return getArcSet(getExistingNode(name));
}

/*
 * Implementation notes: getNeighbors
 * ----------------------------------
 * This implementation recomputes the set each time, which is reasonably
 * efficient if the degree of the node is small.
 */

template <typename NodeType,typename ArcType>
Set<NodeType *> Graph<NodeType,ArcType>::getNeighbors(NodeType *node) {
   Set<NodeType *> nodes = Set<NodeType *>(comparator);
   foreach (ArcType *arc in node->arcs) {
      nodes.add(arc->finish);
   }
   return nodes;
}

template <typename NodeType,typename ArcType>
Set<NodeType *> Graph<NodeType,ArcType>::getNeighbors(std::string name) {
   return getNeighbors(getExistingNode(name));
}

/*
 * Implementation notes: operator=, copy constructor
 * -------------------------------------------------
 * These methods ensure that copying a graph creates an entirely new
 * parallel structure of nodes and arcs.
 */

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>
           & Graph<NodeType,ArcType>::operator=(const Graph & rhs) {
   if (this != &rhs) {
      clear();
      deepCopy(rhs);
   }
   return *this;
}

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>::Graph(const Graph & src) {
   nodes = Set<NodeType *>(comparator);
   arcs = Set<ArcType *>(comparator);
   deepCopy(src);
}

/*
 * Private method: deepCopy
 * ------------------------
 * Common code factored out of the copy constructor and operator= to
 * copy the contents from the other graph.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::deepCopy(const Graph & src) {
   foreach (NodeType *oldNode in src.nodes) {
      NodeType *newNode = new NodeType();
      *newNode = *oldNode;
      newNode->arcs.clear();
      addNode(newNode);
   }
   foreach (ArcType *oldArc in src.arcs) {
      ArcType *newArc = new ArcType();
      *newArc = *oldArc;
      newArc->start = getExistingNode(oldArc->start->name);
      newArc->finish = getExistingNode(oldArc->finish->name);
      addArc(newArc);
   }
}

#endif
