* don't take shared pointers by value unless you want to share/take ownership!


* no need to call default constructor of a member on class construction, redendant 

* About StringRef:
  ```C++
  const StringRef& = "sss"; // wrong, dangling, "sss" is out of scope at end of this line
  
  void test(const StringRef& s)
  {
    "do with s"

  }

  test("sss"); // this is OK, because "sss" is only out of scope at next line, so everything happens inside `test` is OK
  ```
