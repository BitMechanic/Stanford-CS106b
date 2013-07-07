/*
 * File: mappriv.h
 * ---------------
 * This file contains the private section of the map.h interface.
 */

/*
 * Implementation notes:
 * ---------------------
 * The map class is represented using a binary search tree.  The
 * specific implementation used here is the classic AVL algorithm
 * developed by Georgii Adel'son-Vel'skii and Evgenii Landis in 1962.
 */

private:

/* Constant definitions */

   static const int BST_LEFT_HEAVY = -1;
   static const int BST_IN_BALANCE = 0;
   static const int BST_RIGHT_HEAVY = +1;

/* Type definition for nodes in the binary search tree */

   struct BSTNode {
      KeyType key;             /* The key stored in this node         */
      ValueType value;         /* The corresponding value             */
      BSTNode *left;           /* Subtree containing all smaller keys */
      BSTNode *right;          /* Subtree containing all larger keys  */
      int bf;                  /* AVL balance factor                  */
   };

/*
 * Implementation notes: Comparator
 * --------------------------------
 * The Comparator class encapsulates a functor that compares two values
 * of KeyType.  In contrast to the classes in the STL, all of which embed
 * the comparator in the type, the Map class and its derivatives pass an
 * optional Comparator value.  While this strategy results in a more
 * complex implementation, it has the advantage of allowing maps and sets
 * to carry their own comparators without forcing the client to include
 * the comparator in the template declaration.  This simplification is
 * particularly important for the Graph class.
 */

   class Comparator {
   public:
      virtual bool lessThan(const KeyType & k1, const KeyType & k2) = 0;
      virtual Comparator *clone() = 0;
   };

   template <typename CompareType>
   class TemplateComparator : public Comparator {
   public:
      TemplateComparator(CompareType cmp) {
         this->cmp = cmp;
      }

      virtual bool lessThan(const KeyType & k1, const KeyType & k2) {
         return cmp(k1, k2);
      }

      virtual Comparator *clone() {
         return new TemplateComparator<CompareType>(cmp);
      }

   private:
      CompareType cmp;
   };

   Comparator & getComparator() const {
      return *cmpp;
   }

/* Instance variables */

   BSTNode *root;                  /* Pointer to the root of the tree */
   int nodeCount;                  /* Number of entries in the map    */
   Comparator *cmpp;               /* Pointer to the comparator       */

   int (*cmpFn)(const KeyType &, const KeyType &);

/* Private methods */

/*
 * Implementation notes: findNode(t, key)
 * --------------------------------------
 * Searches the tree rooted at t to find the specified key, searching
 * in the left or right subtree, as approriate.  If a matching node
 * is found, findNode returns a pointer to the value cell in that node.
 * If no matching node exists in the tree, findNode returns NULL.
 */

   ValueType *findNode(BSTNode *t, const KeyType & key) const {
      if (t == NULL)  return NULL;
      int sign = compareKeys(key, t->key);
      if (sign == 0) return &t->value;
      if (sign < 0) {
         return findNode(t->left, key);
      } else {
         return findNode(t->right, key);
      }
   }

/*
 * Implementation notes: addNode(t, key, heightFlag)
 * -------------------------------------------------
 * Searches the tree rooted at t to find the specified key, searching
 * in the left or right subtree, as approriate.  If a matching node
 * is found, addNode returns a pointer to the value cell in that node,
 * just like findNode.  If no matching node exists in the tree, addNode
 * creates a new node with a default value.  The heightFlag reference
 * parameter returns a bool indicating whether the height of the tree
 * was changed by this operation.
 */

   ValueType *addNode(BSTNode * & t, const KeyType & key, bool & heightFlag) {
      heightFlag = false;
      if (t == NULL)  {
         t = new BSTNode();
         t->key = key;
         t->value = ValueType();
         t->bf = BST_IN_BALANCE;
         t->left = t->right = NULL;
         heightFlag = true;
         nodeCount++;
         return &t->value;
      }
      int sign = compareKeys(key, t->key);
      if (sign == 0) return &t->value;
      ValueType *vp = NULL;
      int bfDelta = BST_IN_BALANCE;
      if (sign < 0) {
         vp = addNode(t->left, key, heightFlag);
         if (heightFlag) bfDelta = BST_LEFT_HEAVY;
      } else {
         vp = addNode(t->right, key, heightFlag);
         if (heightFlag) bfDelta = BST_RIGHT_HEAVY;
      }
      updateBF(t, bfDelta);
      heightFlag = (bfDelta != 0 && t->bf != BST_IN_BALANCE);
      return vp;
   }

/*
 * Implementation notes: removeNode(t, key)
 * ----------------------------------------
 * Removes the node containing the specified key from the tree rooted
 * at t.  The return value is true if the height of this subtree
 * changes.  The removeTargetNode method does the actual deletion.
 */

   bool removeNode(BSTNode * & t, const KeyType & key) {
      if (t == NULL) return false;
      int sign = compareKeys(key, t->key);
      if (sign == 0) return removeTargetNode(t);
      int bfDelta = BST_IN_BALANCE;
      if (sign < 0) {
         if (removeNode(t->left, key)) bfDelta = BST_RIGHT_HEAVY;
      } else {
         if (removeNode(t->right, key)) bfDelta = BST_LEFT_HEAVY;
      }
      updateBF(t, bfDelta);
      return bfDelta != 0 && t->bf == BST_IN_BALANCE;
   }

/*
 * Implementation notes: removeTargetNode(t)
 * -----------------------------------------
 * Removes the node which is passed by reference as t.  The easy case
 * occurs when either (or both) of the children is NULL; all you need
 * to do is replace the node with its non-NULL child, if any.  If both
 * children are non-NULL, this code finds the rightmost descendent of
 * the left child; this node may not be a leaf, but will have no right
 * child.  Its left child replaces it in the tree, after which the
 * replacement data is moved to the position occupied by the target node.
 */

   bool removeTargetNode(BSTNode * & t) {
      BSTNode *toDelete = t;
      if (t->left == NULL) {
         t = t->right;
         delete toDelete;
         nodeCount--;
         return true;
      } else if (t->right == NULL) {
         t = t->left;
         delete toDelete;
         nodeCount--;
         return true;
      } else {
         BSTNode *successor = t->left;
         while (successor->right != NULL) {
            successor = successor->right;
         }
         t->key = successor->key;
         t->value = successor->value;
         if (removeNode(t->left, successor->key)) {
            updateBF(t, BST_RIGHT_HEAVY);
            return (t->bf == BST_IN_BALANCE);
         }
         return false;
      }
   }

/*
 * Implementation notes: updateBF(t, bfDelta)
 * ------------------------------------------
 * Updates the balance factor in the node and rebalances the tree
 * if necessary.
 */

   void updateBF(BSTNode * & t, int bfDelta) {
      t->bf += bfDelta;
      if (t->bf < BST_LEFT_HEAVY) {
         fixLeftImbalance(t);
      } else if (t->bf > BST_RIGHT_HEAVY) {
         fixRightImbalance(t);
      }
   }

/*
 * Implementation notes: fixLeftImbalance(t)
 * -----------------------------------------
 * This function is called when a node has been found that is out
 * of balance with the longer subtree on the left.  Depending on
 * the balance factor of the left child, the code performs a
 * single or double rotation.
 */

   void fixLeftImbalance(BSTNode * & t) {
      BSTNode *child = t->left;
      if (child->bf == BST_RIGHT_HEAVY) {
         int oldBF = child->right->bf;
         rotateLeft(t->left);
         rotateRight(t);
         t->bf = BST_IN_BALANCE;
         switch (oldBF) {
          case BST_LEFT_HEAVY:
            t->left->bf = BST_IN_BALANCE;
            t->right->bf = BST_RIGHT_HEAVY;
            break;
          case BST_IN_BALANCE:
            t->left->bf = t->right->bf = BST_IN_BALANCE;
            break;
          case BST_RIGHT_HEAVY:
            t->left->bf = BST_LEFT_HEAVY;
            t->right->bf = BST_IN_BALANCE;
            break;
         }
      } else if (child->bf == BST_IN_BALANCE) {
         rotateRight(t);
         t->bf = BST_RIGHT_HEAVY;
         t->right->bf = BST_LEFT_HEAVY;
      } else {
         rotateRight(t);
         t->right->bf = t->bf = BST_IN_BALANCE;
      }
   }

/*
 * Implementation notes: rotateLeft(t)
 * -----------------------------------
 * This function performs a single left rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

   void rotateLeft(BSTNode * & t) {
      BSTNode *child = t->right;
      t->right = child->left;
      child->left = t;
      t = child;
   }

/*
 * Implementation notes: fixRightImbalance(t)
 * ------------------------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the right.
 * Depending on the balance factor of the right child, the
 * code performs a single or double rotation.
 */

   void fixRightImbalance(BSTNode * & t) {
      BSTNode *child = t->right;
      if (child->bf == BST_LEFT_HEAVY) {
         int oldBF = child->left->bf;
         rotateRight(t->right);
         rotateLeft(t);
         t->bf = BST_IN_BALANCE;
         switch (oldBF) {
          case BST_LEFT_HEAVY:
            t->left->bf = BST_IN_BALANCE;
            t->right->bf = BST_RIGHT_HEAVY;
            break;
          case BST_IN_BALANCE:
            t->left->bf = t->right->bf = BST_IN_BALANCE;
            break;
          case BST_RIGHT_HEAVY:
            t->left->bf = BST_LEFT_HEAVY;
            t->right->bf = BST_IN_BALANCE;
            break;
         }
      } else if (child->bf == BST_IN_BALANCE) {
         rotateLeft(t);
         t->bf = BST_LEFT_HEAVY;
         t->left->bf = BST_RIGHT_HEAVY;
      } else {
         rotateLeft(t);
         t->left->bf = t->bf = BST_IN_BALANCE;
      }
   }

/*
 * Implementation notes: rotateRight(t)
 * ------------------------------------
 * This function performs a single right rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

   void rotateRight(BSTNode * & t) {

      BSTNode *child = t->left;
      t->left = child->right;
      child->right = t;
      t = child;
   }

/*
 * Implementation notes: deleteTree(t)
 * -----------------------------------
 * Deletes all the nodes in the tree.
 */

   void deleteTree(BSTNode *t) {
      if (t != NULL) {
         deleteTree(t->left);
         deleteTree(t->right);
         delete t;
      }
   }

/*
 * Implementation notes: mapAll(t, fn)
 * -----------------------------------
 * Calls fn(key, value) for every key-value pair in the tree.
 */

   void mapAll(BSTNode *t, void (*fn)(KeyType, ValueType)) const {
      if (t != NULL) {
         mapAll(t->left, fn);
         fn(t->key, t->value);
         mapAll(t->right, fn);
      }
   }

   void mapAll(BSTNode *t,
               void (*fn)(const KeyType &, const ValueType &)) const {
      if (t != NULL) {
         mapAll(t->left, fn);
         fn(t->key, t->value);
         mapAll(t->right, fn);
      }
   }

   template <typename FunctorType>
   void mapAll(BSTNode *t, FunctorType fn) const {
      if (t != NULL) {
         mapAll(t->left, fn);
         fn(t->key, t->value);
         mapAll(t->right, fn);
      }
   }

   void copyInternalData(const Map & other) {
      root = copyTree(other.root);
      nodeCount = other.nodeCount;
      cmpp = (other.cmpp == NULL) ? NULL : other.cmpp->clone();
   }

   BSTNode *copyTree(BSTNode * const t) {
      if (t == NULL) return NULL;
      BSTNode *np = new BSTNode();
      np->key = t->key;
      np->value = t->value;
      np->bf = t->bf;
      np->left = copyTree(t->left);
      np->right = copyTree(t->right);
      return np;
   }

public:

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

/* Extended constructors */

   template <typename CompareType>
   explicit Map(CompareType cmp) {
      root = NULL;
      nodeCount = 0;
      cmpp = new TemplateComparator<CompareType>(cmp);
   }

/*
 * Implementation notes: compareKeys(k1, k2)
 * -----------------------------------------
 * Compares the keys k1 and k2 and returns an integer (-1, 0, or +1)
 * depending on whether k1 < k2, k1 == k2, or k1 > k2, respectively.
 */

   int compareKeys(const KeyType & k1, const KeyType & k2) const {
      if (cmpp->lessThan(k1, k2)) return -1;
      if (cmpp->lessThan(k2, k1)) return +1;
      return 0;
   }

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return maps by value
 * and assign from one map to another.
 */

   Map & operator=(const Map & rhs) {
      if (this != &rhs) {
         clear();
         copyInternalData(rhs);
      }
      return *this;
   }

   Map(const Map & rhs) {
      copyInternalData(rhs);
   }

/*
 * Method: mapAll
 * Usage: map.mapAll(fn);
 * ----------------------
 * Iterates through the map entries and calls <code>fn(key, value)</code>
 * for each one.  The keys are processed in ascending order, as defined
 * by the comparison function.
 */

   void mapAll(void (*fn)(KeyType, ValueType)) const {
      mapAll(root, fn);
   }

   void mapAll(void (*fn)(const KeyType &, const ValueType &)) const {
      mapAll(root, fn);
   }

   template <typename FunctorType>
   void mapAll(FunctorType fn) const {
      mapAll(root, fn);
   }

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag,KeyType> {

   private:

      struct NodeMarker {
         BSTNode *np;
         bool processed;
      };

      const Map *mp;               /* Pointer to the map         */
      int index;                   /* Index of current element   */
      Stack<NodeMarker> stack;     /* Stack of unprocessed nodes */

      void findLeftmostChild() {
         BSTNode *np = stack.peek().np;
         if (np == NULL) return;
         while (np->left != NULL) {
            NodeMarker marker = { np->left,  false };
            stack.push(marker);
            np = np->left;
         }
      }

   public:

      iterator() {
        /* Empty */
      }

      iterator(const Map *mp, bool end) {
         this->mp = mp;
         if (end || mp->nodeCount == 0) {
            index = mp->nodeCount;
         } else {
            index = 0;
            NodeMarker marker = { mp->root, false };
            stack.push(marker);
            findLeftmostChild();
         }
      }

      iterator(const iterator & it) {
         mp = it.mp;
         index = it.index;
         stack = it.stack;
      }

      iterator & operator++() {
         NodeMarker marker = stack.pop();
         BSTNode *np = marker.np;
         if (np->right == NULL) {
            while (!stack.isEmpty() && stack.peek().processed) {
               stack.pop();
            }
         } else {
            marker.processed = true;
            stack.push(marker);
            marker.np = np->right;
            marker.processed = false;
            stack.push(marker);
            findLeftmostChild();
         }
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return mp == rhs.mp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      KeyType operator*() {
         return stack.peek().np->key;
      }

      KeyType *operator->() {
         return &stack.peek().np->key;
      }

      friend class Map;

   };

   iterator begin() const {
      return iterator(this, false);
   }

   iterator end() const {
      return iterator(this, true);
   }
