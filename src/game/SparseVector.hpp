#ifndef __SPARSEVECTOR_HPP__
#define __SPARSEVECTOR_HPP__

#include <cassert>

namespace jumper
{
    /**
     * @brief A sparse vector representation for integer values
     */
    class SparseVector
    {

        /// Inner struct to represent a node in the sparse vector
        struct node
        {
            /// Element number, must be smaller than the vector's size
            int index;

            /// The value of this element
            int value; // The value of this element.

            /// A pointer to the next node in the list
            node* next; // A pointer to the next node in the linked-list.

            /**
             * Constructor
             *
             * @param idx	Index of the node
             * @param val	Value of the node
             * @param nxt	Pointer to next node in list
             */
            node(int idx, int val, node* nxt) : index(idx), value(val), next(nxt)
            { }

            /**
             * Copy constructor
             */
            node(const node& c) : index(c.index), value(c.value), next(c.next)
            { }
        };

    public:
        /**
         * Constructs a sparse vector with given size
         *
         * @param s 	Size of the vector
         */
        SparseVector(int s);

        /**
         * Copy constructor
         *
         * @param c Vector to copy values from
         */
        SparseVector(const SparseVector& c);

        /**
         * Desctructor
         */
        virtual ~SparseVector();

        /**
         * Assigns the given value the the ith component.
         *
         * @param i Index at which the given value will be set
         * @param value Value which will be set
         */
        void setElem(int i, int value);

        /**
         * Returns the value of component i
         *
         * @param i Index which value will be returned
         * @return Value behind given index
         */
        int getElem(int i) const;

        /**
         * Returns the size of the vector
         *
         * @return Size of the vector
         */
        int getSize() const;

        /**
         * Assignment operator
         *
         * @param b Vector to get values from
         * @return Reference to this instance
         */
        SparseVector& operator=(const SparseVector& b);

        /**
         * Checks if two vectors are equal
         *
         * @param b Vector to compare this vector with
         * @return true, if both vectors are equal, false else
         */
        bool operator==(const SparseVector& b) const;

        /**
         * Checks for inequality
         *
         * @param b Vector to compare this vector with
         * @return false, if both vectors are equal, true else
         */
        bool operator!=(const SparseVector& b) const;

        /**
         * Returns the value of the ith component
         *
         * @param i Index which value to return
         * @return Value behind given index
         */
        int operator[](int i) const
        { return getElem(i); }

    private:

        /// List anchor
        node* m_start;

        /// Size of the vector
        int m_size;

        /// Removes all non-zero elements
        void clear();

        /// Copies the contends of the other vector
        void copy(const SparseVector& other);

        /// Sets a value of an non-zero element, i.e., inserts a new
        /// node in the list
        void setNonzeroElem(int index, int value);

        /// Removes the element at given index
        void removeElem(int index);

        /// Returns a pointer to node in the list before \ref i
        node* getPrevElem(int i) const;

    };

} // namespace jumper

#endif
