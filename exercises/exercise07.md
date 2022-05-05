# Exercise Heap

Since you should normally use standard containers for objects that require heap allocation it is hard to create a useful exercise. 


## Topological Sort Problem

Consider the problem of a student that needs to create their schedule according to the individual modules' pre-requisites. 
Each module is identified by a short string. The pre-requisites of a module are given by a line in an input file, where the first string is the module name and the following strings are the module's required modules. 
The goal is to sort the modules so that for each semester the maximum number of modules that have all their required modules fulfilled can be scheduled.

Read dependencies from a file, where the first string provides the current module name and the following strings its pre-requisites. 

The file is not sorted, so that modules might be pre-requisites, before you know what pre-requisites theses modules have. 

Create a "node" class with a string and appropriate container with `std::shared_ptr` to this class.

For example the following input.txt:
```
DB1 OO
DB2 DB1
Math
OO
AD1 OO
CPI OO Math
Thesis DB2 SE2 UI2
SE1 AD1 CPI DB1
SE2 DB1 SE1 UI1
UI1 AD1
UI2 UI1
```

might produce the following schedule as output:

```
1: Math OO
2: DB1 AD1 CPI
3: DB2 SE1 UI1
4: SE2 UI2
5: Thesis
```

Variation A):

* Model dependencies, where each node has a container of `shared_ptr` to nodes it depends on.
* Keep a dictionary of all nodes for easy check if a node with a given name was already produced, so that you won't create duplicate nodes.
* Produce an output that assigns a schedule, where each semester only modules are selected, where all pre-requisites are fulfilled. The scheduled year could be a data member in a node.
* Start with those nodes that do not have a pre-requisite. You might use a sequence of nodes and partition it by consecutive semesters scheduled, or actually build the dependency graph.
* provide a separate main() function project where you can pass the filename as a command line argument.
* Do not produce a memory leak! 
* Do not instantiate objects representing the same lecture twice! 
* Write unit tests for your functions! 

Variation B): 

* can you create a working solution without dangling, that does not use `std::shared_ptr` but `std::unique_ptr` and `std::reference_wrapper` without risking "dangling"?

Variation C):

* A more efficient algorithm is possible, if the nodes to not store the other nodes they depend on, but the the nodes that need the node, thus reversing the relationship.



Optional: 
* Test your code also with the large dependency file: LargeCatalogue.txt
  * measure timing as follows (using ``#include<chrono>``):
```C++
    auto start=std::chrono::system_clock::now();
    // do your stuff
    std::chrono::duration<double> delta=std::chrono::system_clock::now()-start;
    out << delta.count() << "s time\n";
```


## (optional - may be simpler) Social Media Followers

Take the example code for class Person from the slides and modify it to represent social media follower relationships. Each person can have multiple other persons as followers and can follow others. It might be best to keep track of all members with a data structure that holds the constructed Persons. Implement the following functionalities:

* follow (otherPerson) - ensure that one cannot follow oneself
* unfollow (otherPerson)
* listFollowers(std::ostream &)
* listFollowing(std::ostream &)
* block(otherPerson) --> ensure that otherPerson no longer follows and that this no longer follows otherPerson
* ban(Person) - as a function on the global registry. ensure that nobody can follow Person and that Person is actually deleted.

Write useful test cases for the following relationships

* (Peter <-> Fred <-> Steve ) - all follow each other and back
* (Fred <-> Amy) - follow each other
* (Amy -> Bibi) - Amy follows Bibi
* (Tom -> Bibi) - Tom follows Bibi
* (Peter -> Bibi) - Peter follows Bibi

My implementation would print out that followership as:

```
Peter
   follows    : Fred, Steve, Bibi, 
   followedBy : Fred, Steve, 

Fred
   follows    : Peter, Steve, Amy, 
   followedBy : Peter, Steve, 

Steve
   follows    : Peter, Fred, 
   followedBy : Peter, Fred, 

Amy
   follows    : Bibi, 
   followedBy : Fred, 

Tom
   follows    : Bibi, 
   followedBy : 

Bibi
   follows    : 
   followedBy : Peter, Amy, Tom, 

```


- A) Use shared_ptr and weak_ptr. How, can you ensure no cyclic shared_ptr relationships?
- B) Model that Steve blocks Fred. (neither Steve follows Fred, nor Fred follows Steve)
- C) Model that Peter unfollows Fred.
- D) Model that Bibi is banned.

For the test cases you can write a function that set ups the followers initially for each test. Start with testing A single Person, the two Persons etc.