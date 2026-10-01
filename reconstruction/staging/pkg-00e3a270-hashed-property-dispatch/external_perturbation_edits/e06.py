import sys
p=sys.argv[1]; s=open(p).read()
old="simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x2c0))"
new="simulator_copy_block3_00e39420(record, 0x2, word_at(self, 0x2c0))"
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
