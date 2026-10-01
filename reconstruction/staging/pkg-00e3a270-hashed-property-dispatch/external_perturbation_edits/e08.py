import sys
p=sys.argv[1]; s=open(p).read()
old=("  return reinterpret_cast<const void*>(static_cast<std::uintptr_t>(\n"
     "      *word_at(base, displacement)));")
new=("  return reinterpret_cast<const void*>(reinterpret_cast<std::uintptr_t>(\n"
     "      word_at(base, displacement)));")
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
