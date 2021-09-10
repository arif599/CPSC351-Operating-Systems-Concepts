all: thrice stderr foreach

clean: 
  rm -f thrice stderr foreach
  
thrice: thrice.cpp
  gcc -o thrice thrice.cpp -Wall -std=c++17 -Wextra -Wpedantic -Werror

stderr: stderr.cpp
    gcc -o stderr stderr.cpp -Wall -std=c++17 -Wextra -Wpedantic -Werror

foreach: foreach.cpp
  gcc -o foreach foreach.cpp -Wall -std=c++17 -Wextra -Wpedantic -Werror


  
