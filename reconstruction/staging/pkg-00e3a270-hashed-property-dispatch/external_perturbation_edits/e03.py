# Swap the DESTINATIONS of the four-store arm's middle pair, keeping the source
# fields in place -- i.e. the reconstruction that writes them in ascending source
# order instead of the machine's swapped order.
import sys
p=sys.argv[1]; s=open(p).read()
a="*word_at(self, 0x2ac) = *word_at(block, 0xc);"
b="*word_at(self, 0x2a8) = *word_at(block, 0x10);"
assert a in s and b in s, "no match"
open(p,"w").write(s.replace(a,b,1).replace(b.replace("0x2a8","@@"),b,1)) if False else \
     open(p,"w").write(s.replace(a,"@A@",1).replace(b,b.replace("0x2a8","0x2ac"),1).replace("@A@",a.replace("0x2ac","0x2a8"),1))
