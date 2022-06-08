## Sample PlatformIO Dynamic Code Analysis


### Dr. Memory
As part of running unit tests, it is sometimes beneficial to also execute Dr.Memory for memory analysis, you can add the following:
```
extra_scripts = 
    scripts/custom_drmemory.py
```

### Coverage
gcovr is similar to lcov, which produces reports for code coverage
```
gcovr --print-summary --html-details -o .reports/coverage.html --xml -o .reports/coverage.xml
```
and if you wish to exclude the test folder:
```
gcovr --exclude $(realpath test) --print-summary --html-details -o .reports/coverage.html --xml -o .reports/coverage.xml
```
