Market library
----------------------------
This library provides functions to read data from a given CPA file and instrument


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
bin/marketserver --port 1234 --cpa /tmp/vda.txt
~~~~
* Then, run as many clients you want as in this example:
~~~~
bin/marketclient --port 1234 --host localhost
~~~~

Generated files
---------------
* **liboscomm.so** Dynamic library containing all classes related to server client communication.
* **marketserver** Command line application to serve CPA data
* **marketclient** Command line application to receive and decode CPA data

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
