import sys
p=sys.argv[1]; s=open(p).read()
old="return static_cast<std::int32_t>(left) > static_cast<std::int32_t>(right);"
new="return left > right;"
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
