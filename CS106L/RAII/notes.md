# Resource Acquisition Is Initialization
e.g.,
ifstream input("hamlet.txt"); // should not call close(), because if exception throwed may not close

lock_guard<mutex>(databaseLock);

- unique_ptr: Uniquely owns its resource and delete it when obj is destroyed. cannot be copied!
（by deleting the copy constructor and copy assignment）

std::unique_ptr<Node> n(new Node);
std::unique_ptr<Node> n = std::make_unique<Node>(); // always use this


- shared_ptr: Resources can be stored by any number of shared_ptrs. Delete when none of them points to it
{
    std::shared_ptr<int> p1(new int);
    // Use p1
    {
        std::shared_ptr<int> p2 = p1;   // Only works if new ptrs are made through copying
        // Use p1 and p2
    }
    // Use p1 
}
// Freed

- weak_ptr: Similar to shared_ptr, but doesn't contribute to the reference count. Used to deal with circular references with shared_ptr.
# Scope Based Memory Management 
In modern C++, we pretty much never use new and delete!
# Constructor Acquires, Destructor Realeases

# PIMPL

# Auto memory management is not always a good thing

