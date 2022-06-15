# Resource Acquisition Is Initialization
e.g.,
ifstream input("hamlet.txt"); // should not call close(), because if exception throwed may not close

lock_guard<mutex>(databaseLock);

- unique_ptr: Uniquely owns its resource and delete it when obj is destroyed. cannot be copied!
std::unique_ptr<Node> n(new Node);
std::unique_ptr<Node> n = std::make_unique<Node>(); // always use this
- shared_ptr: Resources can be stored by any number of shared_ptr
{
    std::shared_ptr<int> p1(new int);
    // Use p1
    {
        std::shared_ptr<int> p2 = p1;
        // Use p1 and p2
    }
    // Use p1 
}
// Freed
# Scope Based Memory Management 

# Constructor Acquires, Destructor Realeases


In modern C++, we pretty much never use new and delete!