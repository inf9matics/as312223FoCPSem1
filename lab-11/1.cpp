#include <vector>
#include <map>
#include <string>
#include <list>
#include <iostream>

void printGraphBfsUtil(std::map<std::string, std::vector<std::string>> &graph, std::map<std::string, bool> &graphVisited, std::map<std::string, std::vector<std::string>>::iterator &graphIterator, std::map<std::string, bool>::iterator &graphVisitedIterator){
    std::list<std::string> queue;
    graphVisitedIterator->second = true;
    for(int i=0; i<graphIterator->second.size(); i++){
        queue.push_back(graphIterator->second.at(i));
    }
    while(!queue.empty()){
        std::string queueFront = queue.front();
        std::clog << queueFront << " ";
        graphVisited.at(queueFront) = true;
        queue.pop_front();
        for(int i=0; i<graph.at(queueFront).size(); i++){
            if(!graphVisited.at(graph.at(queueFront).at(i))){
                graphVisited.at(graph.at(queueFront).at(i)) = true;
                queue.push_back(graph.at(queueFront).at(i));
            }
        }
    }
}

void printGraphBfs(std::map<std::string, std::vector<std::string>> &graph){
    std::map<std::string, bool> graphVisited;
    
    std::map<std::string, std::vector<std::string>>::iterator graphIterator = graph.begin();
    while(graphIterator != graph.end()){
        graphVisited.insert_or_assign(graphIterator->first, false);
        std::advance(graphIterator, 1);
    }

    std::map<std::string, bool>::iterator graphVisitedIterator = graphVisited.begin();
    graphIterator = graph.begin();
    while(graphIterator != graph.end()){
        if(!graphVisitedIterator->second){
            printGraphBfsUtil(graph, graphVisited, graphIterator, graphVisitedIterator);
        }
        std::advance(graphIterator, 1);
        std::advance(graphVisitedIterator, 1);
    }
}

// void printGraphDfs(std::map<std::string, std::vector<std::string>> &graph){
//     if(graph.empty()){
//         return;
//     }

//     std::string firstElement = graph.begin()->first;
//     std::string firstVector = graph.begin()->second;


// }

void fillGraphPredefined(std::map<std::string, std::vector<std::string>> &graph){
    graph.insert_or_assign("A", std::vector<std::string>{"B", "C"});
    graph.insert_or_assign("B", std::vector<std::string>{"D", "E"});
    graph.insert_or_assign("C", std::vector<std::string>{"F"});
    graph.insert_or_assign("D", std::vector<std::string>{});
    graph.insert_or_assign("E", std::vector<std::string>{"G", "H"});
    graph.insert_or_assign("G", std::vector<std::string>{});
    graph.insert_or_assign("H", std::vector<std::string>{});
    graph.insert_or_assign("F", std::vector<std::string>{});
}

int main(){
    std::map<std::string, std::vector<std::string>> graph;
    fillGraphPredefined(graph);
    printGraphBfs(graph);
}