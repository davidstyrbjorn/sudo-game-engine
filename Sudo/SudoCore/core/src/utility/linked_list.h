#pragma once

namespace sudo { namespace utility {

	template<class T>
	class LinkedList {
	private:
		struct Node {
			Node(T a_data) : m_data(a_data) { } 
			T&	  m_data;
			Node *m_next;
		};

		Node* m_head;

	public:
		/*  */
		void push_back(T a_data) {
			// Check if we have an empty list
			if (m_head == nullptr) {
				m_head = new Node(a_data);
				return;
			}

			Node *ptrNode = m_head;

			while (ptrNode != nullptr) {

				if (ptrNode->m_next == nullptr) 
				{
					ptrNode->m_next = new Node(a_data);
					return;
				}

				ptrNode = ptrNode->m_next;
			}
		}
	};

}
}