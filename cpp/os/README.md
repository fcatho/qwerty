Market library
----------------------------
This library provides functions to read data from a given CPA file and instrument


Preprocessing script
-------------------------
Select the most liquid instrument. Use as:
~~~~
scripts/get_most_liquid.sh /tmp/cpa.txt /tmp/vda.txt
~~~~
The most liquid instrument will be printed. Also, two files containing only the most liquid instrument will be generated. In the previous example:
~~~~
cpa_most_liquid.txt
vda_most_liquid.txt
~~~~
These files can be used for server client communication.


Quick compilation and execution 
-------------------------
If boost-dev is not present go to 'Install boost' section first.

* From *os* folder:
~~~~
make
~~~~
* To execute any of the binaries, first declare LD_LIBRARY_PATH as follows
~~~~
export LD_LIBRARY_PATH=lib

~~~~
* Then, run the server first as in this example:
~~~~
bin/marketserver --port 1234 --cpa /tmp/cda.txt
~~~~
* Then, run as many clients you want as in this example:
~~~~
bin/marketclient --port 1234 --host localhost
~~~~

Generated files
---------------
* **lib/liboscomm.so** Dynamic library containing all classes related to server client communication.
* **bin/marketserver** Command line application to serve CPA data
* **bin/marketclient** Command line application to receive and decode CPA data

Install boost
---------------
To install boost:
~~~~
sudo apt-get install libboost-all-dev
~~~~

TODO
----------------
* Add VDA parsing
* Sort VDA/CDA
* Use std::time for dates
* Align bytes in the struct
