Distance computation library
----------------------------
This library provides a basic infrastructure for distance computation. A generic interface is defined as the parent class for any particular distance algorithm. Inputs for distance calculation are templatized which allows an easy use of any kind of data type. Furthermore, any derived distance method should implemented run function. As an example, Hamming distance is implemented using two approaches: bitwise and byte-to-byte comparison. A dummy distance class is included as example to show how to extend base class to any particular distance computation.

To prove code functionality unit tests are also provided. These tests depends on Google Test framework.

Compilation and execution 
-------------------------
* Insider waes folder:
~~~~
make
~~~~
* To execute, as an example:
~~~~
bin/hammingstr foo bar
3
~~~~

Generated files
---------------
Command line application for hamming distance computation between two strings will be located at bin folder, with the name **hammingstr**

Also, unit tests binary will be located in bin folder, with the name **unit_test**

**libdistance.so** is the dynamic library containing all classes related to distance computation. This file will be produced in lib folder.


Unit Test Dependencies
----------------------
As mentioned before, unit test compilation and execution depends on Google Test Framework. Follow these steps to be able to get a sucessful compilation:
* Insider waes folder:
~~~~
git clone https://github.com/google/googletest.git
cd googletest
cmake -DBUILD_SHARED_LIBS=ON .
make
~~~~
* Return to waes directory and compile unit tests binary:
~~~~
make test
~~~~
* Inside waes folder, set LD_LIBRARY_PATH variable:
~~~~
export LD_LIBRARY_PATH=../googletest/googlemock/:../googletest/googlemock/gtest/
~~~~
* Execute unit tests:
~~~~
bin/unit_test
~~~~





