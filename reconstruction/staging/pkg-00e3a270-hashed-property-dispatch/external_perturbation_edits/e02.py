import sys
p=sys.argv[1]; s=open(p).read()
old="*word_at(self, 0x2ac) = *word_at(block, 0xc);"
new="*word_at(self, 0x2a4) = *word_at(block, 0xc);"
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
