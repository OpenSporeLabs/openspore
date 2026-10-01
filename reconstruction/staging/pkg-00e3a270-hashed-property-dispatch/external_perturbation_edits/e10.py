import sys
p=sys.argv[1]; s=open(p).read()
old="    if (record == nullptr) {"
new="    if (false) {"
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
