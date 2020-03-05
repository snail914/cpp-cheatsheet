```bash
for f in *.cpp; do sed -i -e 's/EXPECT_TRUE(\(.*\))/EXPECT_THAT(\1, IsTrue())/' $f; done
```
