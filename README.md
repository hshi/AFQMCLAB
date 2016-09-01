# AFQMCLIB

This is a library for AFQMC.


How to use:
<ol>
<li> git clone https://github.com/hshi/AFQMCLIB.git </li>
<li> cd AFQMCLIB </li>
<li> mkdir build </li>
<li> cd build </li>
<li> cmake ..   (More detals below) </li>
<li> make </li>
<li> make test </li>
<li> make install </li>
</ol>

More detals about cmake:
1. Set install directory:  cmake .. -DCMAKE_INSTALL_PREFIX:PATH="~/lib/gtest"
2. If defualt setting not working, change platform:  cmake .. -DPLATFORM=platform   (platform can be STORM, HURRIANCE, COMET...)
3. If not platform working, set by hand:
