# import common functions for netedit tests
import os
import sys

testRoot = os.path.join(os.environ.get('SUMO_HOME', '.'), 'tests')
neteditTestRoot = os.path.join(
    os.environ.get('TEXTTEST_HOME', testRoot), 'netedit')
sys.path.append(neteditTestRoot)
import neteditTestFunctions as netedit

# Open netedit
neteditProcess, match = netedit.setupAndStart(neteditTestRoot, False)

# go to additional mode
netedit.additionalMode()

# select invalid additional (dummy)
netedit.changeAdditional("dummyAdditional")

# try to create an dummy additional
netedit.leftClick(match, 250, 250)

# select valid additional (busStop)
netedit.changeAdditional("busStop")

# create busStop in mode "reference left"
netedit.leftClick(match, 300, 250)

# save additionals
netedit.saveAdditionals()

# save newtork
netedit.saveNetwork()

# quit netedit
netedit.quit(neteditProcess, False, False)