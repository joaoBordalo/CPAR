# CPAR

A repository to Parallel Computation


##First Assignment
[Report](https://docs.google.com/document/d/1llqgH2A7tqM795S1lQKY7TlrDoL89s5Bus9skph34-M/edit)
[Excel](https://docs.google.com/spreadsheets/d/1sh6rLe-xowZTPW5AaJsls3jeUpZJwjEOjauJNuPCiyY/edit#gid=2053438186)

Setup PAPI
- Download tar.gz from http://icl.cs.utk.edu/papi/software/
- Extract the folder where you want, so choose a practical place for that
- Go to source (src) directory in PAPI folder : cd yourPath/PAPI/src
- Run the following commands:
  - ./configure
  - make
  - sudo make install
  - make test
  - sudo ldconfig

- Install PAPI tools:
  - sudo apt-get install papi-tools

- Compile matrixProd.cpp
  - g++ -o nomeDoExecutável -fopenmp "source.cpp" -lpapi 
  - run ./nomeDoExecutével.out and introduce the matrix size values

  Developers
  João Bordalo
  João Soares
