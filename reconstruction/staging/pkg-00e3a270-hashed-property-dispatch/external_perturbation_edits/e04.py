import sys
p=sys.argv[1]; s=open(p).read()
old=("    *word_at(self, 0x328) = loaded;\n"
     "    if (primary_already_set) {\n"
     "      return loaded;  // 0x00e3a30f leaves EAX exactly as 0x00e3a306 set it\n"
     "    }\n"
     "    *word_at(self, 0x324) = loaded;")
new=("    if (primary_already_set) {\n"
     "      return loaded;\n"
     "    }\n"
     "    *word_at(self, 0x328) = loaded;\n"
     "    *word_at(self, 0x324) = loaded;")
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
