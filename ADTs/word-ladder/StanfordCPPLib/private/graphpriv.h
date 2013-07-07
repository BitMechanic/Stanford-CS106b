/*
 * File: graphpriv.h
 * -----------------
 * This file defines the private data for the Graph class.
 */

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
