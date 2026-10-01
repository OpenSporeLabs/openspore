import sys
p=sys.argv[1]; s=open(p).read()
old="if (*word_at(self, 0x32c) == kTagUnset) {"
new="if (*word_at(self, 0x32c) == 0u) {"
assert old in s, "no match"
open(p,"w").write(s.replace(old,new))
