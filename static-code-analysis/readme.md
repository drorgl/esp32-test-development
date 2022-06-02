## PlatformIO Static Code Analysis

### cppcheck and clangtidy
PlatformIO implements ```pio check``` command which can execute cppcheck and clangtidy

### Code Metrics
use [lizard](https://pypi.org/project/lizard/) to discover problematic code

install:
```
pip install lizard jinja2
```

example
```
lizard src/ lib/ -w
```

I've wrote a little script ```run_analyzer.py``` which executes lizard
```
pio run -t analysis
```
should display a list of methods containing a long or complex code

#### Installing cppcheck on ubuntu from source:
```
apt install  libpcre3-dev
wget http://downloads.sf.net/project/cppcheck/cppcheck/1.89/cppcheck-1.89.zip
unzip cppcheck-1.89.zip
sudo make -j4 MATCHCOMPILER=yes FILESDIR=/usr/share/cppcheck HAVE_RULES=yes -C cppcheck-1.89 install
```

### C++ Code Formatter
clang-format

### clang-tidy
clang-tidy --dump-config > .clang-tidy