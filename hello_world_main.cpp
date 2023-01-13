#include <string>
#include <iostream>
#include <tbb/tbb.h>

struct BodyOne {
    int _in;
    BodyOne(const int &in) : _in(in) {}
    std::string operator()(const int &input) const {
        return std::to_string(input);
    }
};

struct BodyTwo {
    std::string my_name;
    BodyTwo(const std::string& name) : my_name(name) {}
    void operator()(const std::string& name) const {
        printf("%s\n", name.c_str());
    }
};

typedef tbb::flow::function_node<int,std::string> NodeOneType;
typedef tbb::flow::function_node<std::string> NodeTwoType;

void hello_world() {
	
	// step 1: construct the graph
	tbb::flow::graph g;

	// step 2:
	NodeOneType my_first_node(g,tbb::flow::unlimited,BodyOne(2));

	NodeTwoType my_second_node(g,tbb::flow::unlimited,BodyTwo("A"));

	// step 3: add edges
	tbb::flow::make_edge(my_first_node, my_second_node);

	// step 4: send messages
	my_first_node.try_put(42);

	// step 5: wait for graph to complete
	g.wait_for_all();
}

int main() {
	hello_world();
	return 0;
}
