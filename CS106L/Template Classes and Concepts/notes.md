# Prefer templates when:
- Runtime efficiency is most important
- No common base can be defined

# Prefer derived classes when:
- Compile-time efficiency is most important
- Want to hide implementations
- Don't want code bloat

# Casting
int a = (int)b;
int a = int(b);
int a = static_cast<int>(b);