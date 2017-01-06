Dependencies
------------

* googletest
Clone from https://github.com/google/googletest.git to qwerty directory.

cd googletest
cmake -DBUILD_SHARED_LIBS=ON .
make

Run
---

To run unit tests:

Inside waes folder:

export LD_LIBRARY_PATH=../googletest/googlemock/gtest/
bin/unit_test




