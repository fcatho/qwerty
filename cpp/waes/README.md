Distance computation library
----------------------------
This library provides a basic infrastructure for distance computation. A generic interface is defined as the parent class for any particular distance algorithm. Inputs for distance calculation are templatized which allows an easy use of any kind of data type. Furthermore, any derived distance method should implemented run function. As an example, Hamming distance is implemented using two approaches: bitwise and byte-to-byte comparison. A dummy distance class is included as example to show how to extend base class to any particular distance computation.

To prove code functionality unit tests are also provided. These tests depends on Google Test framework.

Quick compilation and execution 
-------------------------
* From *waes* folder:
~~~~
make
~~~~
* To execute, first declare LD_LIBRARY_PATH as follows
~~~~
export LD_LIBRARY_PATH=lib

~~~~
* Then, run as this example:
~~~~
bin/hammingstr foo bar
3
~~~~

Generated files
---------------
* **libdistance.so** Dynamic library containing all classes related to distance computation. This file will be produced in *lib* folder. Use this shared object to expand for any other distance algorithm.
* **hammingstr** Command line application for hamming distance computation between two strings will be located at *bin* folder. This binary is linked with libdistance.so as an application example.

hammingstr usage
---------------
As already said, hammingstr binary shows how libdistance.so works. This binary computes hamming distance between two input strings of equal size. Use it as command line application with the following syntax:

~~~~
./hammingstr <inputA> <inputB>
~~~~
Output is an integer value representing hamming distance byte-to-byte. For example, *foo* and *oof* will result in a distance of 2 bytes.
If two strings of different size are given, hammingstr shows an error message like in this example:
~~~~
./hammingstr foo fo
Incompatible input sizes: input A size (3) != input B size (2)
~~~~
If none input is provided, a usage message is printed.

Integration tests
-----------------
To guarantee that hammingstr is functional a bash script is provided with a set of integration tests, see test/it file. To execute, run from *waes* folder:
~~~~
test/it bin/hammingstr
~~~~

Unit Test Dependencies
----------------------
Unit test compilation and execution depends on Google Test Framework. Follow these steps to be able to get a successful compilation:
* Go to *cpp* folder and run:
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
* From *waes* folder, set LD_LIBRARY_PATH variable:
~~~~
export LD_LIBRARY_PATH=lib:../googletest/googlemock/:../googletest/googlemock/gtest/
~~~~
* Execute unit tests:
~~~~
bin/unit_test
~~~~

TODO Suggestions
----------------
* Add some other algorithms as L1, L2 norms.
* Add support for file reading, instead of just strings
* Expand bitwise operation to 32/64bit words. In this case, a lookup table may be a memory limitation.
* New classes to use a configuration file to read what type of distance will be used
* Some distance algorithms that not limit equal size inputs
