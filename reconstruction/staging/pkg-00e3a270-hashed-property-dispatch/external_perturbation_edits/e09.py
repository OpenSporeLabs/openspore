import sys
p=sys.argv[1]; s=open(p).read()
old="  const Word key = selector;"
new="  if (record == nullptr) { return 0u; }\n  const Word key = selector;"
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
