#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
using std::stack,std::pair, std::cout;
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    std::vector<Node *> children;
		Node(int val): key{val}
		{}

};
void printChildren(Node* node) {
	cout << "children of: " << node->key << " are\n";
	cout <<"\t[ ";
	for(auto child: node->children) {
		cout << child->key <<',';
	}
	cout << "]\n";
}
int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node*> nodes(n);

	// building up tree
	Node *root{nullptr}, *parentNode{nullptr}, *childNode{nullptr};
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
		  if (nodes[child_index] == nullptr) {
				childNode = new Node(child_index);
				nodes[child_index] = childNode;
			}
		  else childNode = nodes[child_index];
    if (parent_index == -1) {
			root = childNode;
			continue;
		} else {
			if (nodes[parent_index] == nullptr) {
				parentNode = new Node(parent_index);
				nodes[parent_index] = parentNode;
			}
			else parentNode = nodes[parent_index];
		}
		parentNode->children.push_back(childNode);
    // nodes[child_index].key = child_index;
  }
	cout << "built tree [";
	for(Node* node: nodes) {
		cout << node->key << ',';
	}
	cout << "]\n";
	printChildren(nodes[1]);
	printChildren(nodes[4]);

  // Replace this code with a faster implementation
	unsigned maxHeight{0};
	// implementing DFS using stack
	std::vector<bool> processed(n);
	stack<pair<Node*,unsigned>> st;
	st.push({root,0});
	pair<Node*,unsigned> ptr;
	while ( !st.empty() ) {
		ptr = st.top();
		st.pop();
		processed[ptr.first->key] = true;
		maxHeight = std::max( maxHeight, ptr.second );

		for (Node* node: ptr.first->children ) {
			cout<< "pushing : "<< ptr.second+1;
			st.push( {node, ptr.second+1} );
		}
	}

	maxHeight += 1;
  std::cout << "max height: " << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
