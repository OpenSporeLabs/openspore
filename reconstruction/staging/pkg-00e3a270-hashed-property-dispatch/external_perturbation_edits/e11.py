import sys
p=sys.argv[1]; s=open(p).read()
old='extern "C" Word PKG_00E3A270_THISCALL hashed_property_dispatch_00e3a270('
new='extern "C" unsigned short PKG_00E3A270_THISCALL hashed_property_dispatch_00e3a270('
assert old in s, "no match"
open(p,"w").write(s.replace(old,new,1))
